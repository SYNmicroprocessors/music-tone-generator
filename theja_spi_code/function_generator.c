#include "at89c5131.h"
#include "stdio.h"
#include "math.h"

int mode=0,flag_t=0,flag_r=0,k=0;
unsigned int freq; off; amp; duty; dacval;
//code int sin[500];
unsigned char serial; //dac1; dac2;
unsigned char message1[]="TYPE OF WAVEFORM\n";
unsigned char message2[]="AMPLITUDE\n";
unsigned char message3[]="FREQUENCY\n";
unsigned char message4[]="OFFSET\n";
unsigned char message5[]="DUTY CYCLE in %\n";

sbit CS_BAR = P1^4;									
sbit LDAC_BAR = P1^3;
bit transmit_completed= 0;					

void delay(int delay)             
{
	int d=0;
	while(delay>0)
	{
		for(d=0;d<3;d++);
		delay--;
	}
}

void init_serial()					//Initialize serial communication and interrupts
{
	SCON = 0xD0;
	EA = 1;
	ES = 1;
}

void Timer_Init()
{    
	TH1 = -52;
	TL1 = -52;
	TMOD = 0x20;                  //Configure TMOD 
	TR1 = 1;
}

void SPI_Init()
{
	CS_BAR = 1;	                  	// DISABLE ADC SLAVE SELECT-CS 
	SPCON |= 0x20;               	 	// P1.1(SSBAR) is available as standard I/O pin 
	SPCON |= 0x01;                	// Fclk Periph/4 AND Fclk Periph=12MHz ,HENCE SCK IE. BAUD RATE=3000KHz 
	SPCON |= 0x10;               	 	// Master mode 
	//SPCON &= ~0x08;               	// CPOL=0; transmit mode example|| SCK is 0 at idle state
	SPCON |= 0x08;
	SPCON |= 0x04;                	// CPHA=1; transmit mode example 
	IEN1 |= 0x04;                	 	// enable spi interrupt 
	SPCON |= 0x40;                	// run spi;ENABLE SPI INTERFACE SPEN= 1 
}

void it_SPI(void) interrupt 9 /* interrupt address is 0x004B, (Address -3)/8 = interrupt no.*/
{
	switch	( SPSTA )         /* read and clear spi status register */
	{
		case 0x80:
			serial=SPDAT;	
      transmit_completed=1;/* set software flag */
 		break;

		case 0x10:
         /* put here for mode fault tasking */	
		break;
	
		case 0x40:
         /* put here for overrun tasking */	
		break;
	}
}

void ISR_Serial(void) interrupt 4
{
 //ISR for serial interrupt
	if(TI == 1)
	{
		TI = 0;
	  flag_t = 1;
		return;
  }
	else if(RI == 1) 
	{
		RI = 0;
		if(SBUF == 'n')
		{
			mode = 0;
			return;
		}
		flag_r = 1;
		return;
	}	
}
	
void transmit_message(char* str, n)
{
	int i;
	for(i=0;i<n;i++)
	{
		ACC = str[i];
		ACC = ACC+0;
		TB8 = PSW^0;
		SBUF = str[i];
		while(!flag_t);
		flag_t = 0;
	}
	return;
}

void receive_type(char *c)
{
	while(!flag_r);
	*c = SBUF;
	flag_r = 0;
	return;
}
	
int receive_data(int r)
{
	int i;
	int num;
	int a[4];
	for(i=0;i<r;i++)
	{
		while(!flag_r);
		a[i] = SBUF - '0';
		flag_r = 0;
	}
	if(r == 4)
	{
		num = a[0]*1000 + a[1]*100 + a[2]*10 + a[3];
	}
	else
	{
		num = a[0]*10 + a[1];
	}
	return num;
}

//void send_voltage(int dac)
//{
//	dac1 = dac/256;
//	dac1 = dac1 | 0x70;
//	dac2 = dac%256;

//	LDAC_BAR = 0;
//	CS_BAR = 0;                 // enable ADC as slave		   
//	SPDAT = dac1;				// 80H written to start ADC CH0 single ended sampling,refer ADC datasheet
//	while(!transmit_completed);	// wait end of transmition  
//	transmit_completed = 0;    	// clear software transfer flag 
//		
//	SPDAT = dac2;								// 
//	while(!transmit_completed);	// wait end of transmition 
//	transmit_completed = 0;    	// clear software transfer flag 
//	CS_BAR = 1;                	// disable ADC as slave
//		
//	delay(2000/freq);
//}

void send_dac(unsigned int dacval)
{
	unsigned char sendval = 0;
	sendval = (dacval >> 8) | 0x70;
	CS_BAR = 0;                 // enable ADC as slave		   
	SPDAT = sendval;				// 80H written to start ADC CH0 single ended sampling,refer ADC datasheet
	while(!transmit_completed);	// wait end of transmition	
	transmit_completed = 0;    	// clear software transfer flag 
	sendval = dacval;
	SPDAT = sendval;				// 80H written to start ADC CH0 single ended sampling,refer ADC datasheet
	while(!transmit_completed);	// wait end of transmition	
	transmit_completed = 0;    	// clear software transfer flag 
	CS_BAR = 1;
}

/////////////////////// MAIN PROGRAM///////////////////////////////

void main()
{
	//P3 = 0X00;											// Make Port 3 output 
	P2 = 0x00;											// Make Port 2 output 
	//P1 &= 0xEF;											// Make P1 Pin4-7 output
	P0 &= 0xF0;											// Make Port 0 Pins 0,1,2 output
	P1 |= 0xF0;
	
	init_serial();
	Timer_Init();
	SPI_Init();
	
	while(mode == 0)
	{
		char *type;
		transmit_message(message1,17);
		receive_type(type);
		if(*type == 's') {mode = 1; k = 0;}
		else
		{
			if(*type == 'p') {mode = 2; k = 0;}
			else
			if(*type == 't') {mode = 3; k = 0;}
			else continue;
		}
		transmit_message(message2,10);
		amp = receive_data(4);
		transmit_message(message3,10);
		freq = receive_data(4);
		transmit_message(message4,7);
		off = receive_data(4);
		
		if(mode==2)
		{
			transmit_message(message5,15);
			duty=receive_data(2);
		}
	}
	
	while(mode == 1)
	{
		if(k == 500)
			k = 0;
		
		dacval = 4095*sin(k*6.283/500);
		k++;
		
		send_dac(dacval);
		delay(2000/freq);
	}
	
	while(mode == 2)
	{
		if(k == 10)
			k = 0;
		
		if(k<duty/10)
			dacval = 4095;
		else
			dacval = 0;
		k++;
		
		send_dac(dacval);
		//delay(200/freq);
	}
		
	while(mode == 3)
	{
		if(k == 20)
			k = 0;
		
		if(k<10)
			dacval = 409*k;
		else
			dacval = 409*(20-k);
		k++;
		
		send_dac(dacval);
		//delay(2000/freq);
	}
}