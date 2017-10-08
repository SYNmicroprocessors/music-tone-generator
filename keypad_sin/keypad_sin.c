#include "at89c5131.h"
#include "stdio.h"
#include "math.h"

sbit op = P0^0;
int input=0,x = 0,delayMul=1;

void delay_5us(int delay);
void transmit_data(unsigned char str);
void transmit_string(char* str,unsigned int  n);
void init_serial();
void outputTone(unsigned int inputInt);
float fillTable(int z);

float spi_out=0;
int k=0;
unsigned int dacval;i=0;
unsigned char serial;
//code int sin[500];

sbit CS_BAR = P1^4;									
sbit LDAC_BAR = P1^3;
bit transmit_completed= 0;					

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
	//EA = 1;
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


void dac(unsigned int dacval)
{
	unsigned char sendval = 0;
		//LDAC_BAR = 0;
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
	//LDAC_BAR=1;
}
void main()
{

	P2 = 0x00;											// Make Port 2 output 
	//P1 &= 0xEF;											// Make P1 Pin4-7 output
	P0 &= 0xF0;											// Make Port 0 Pins 0,1,2 output
	P1 |= 0xF0;
	
	SPI_Init();
init_serial();
transmit_string("Tone Generator",14);

while(1)
{
	////////////////////////////////////////first
	if(input=='z'){delayMul = 4;}
	if(input=='x'){delayMul = 2;}
	if(input=='c'){delayMul = 1;}
	///////////////////////////////////////////////third
	while(input=='g') 
	{
		//transmit_string("g ",2);
		outputTone(454);
		//input =0;
		////transmit_string("done ",4);
	}
	while(input=='h') 
	{
		//transmit_string("h ",2);
		outputTone(405);
		//input =0;
	}
	while(input=='j') 
	{
		//transmit_string("j ",2);
		outputTone(382);
		//input =0;
	}
	while(input=='k') 
	{
		//transmit_string("k ",2);
		outputTone(340);
		//input =0;
	}
	while(input=='l') 
	{
		//transmit_string("l ",2);
		outputTone(303);
		//input =0;
	}
}

}
//-----------------------------------------outputTone-----------------------------
void outputTone(unsigned int inputInt)
{
	x=10000/(inputInt*delayMul);
	while(x>0)
	{
		for(i=0;i<24;i++)
		{
		spi_out= fillTable(i);
		spi_out = 1047*(1+spi_out);	
		dacval = (unsigned int)spi_out;
		dac(dacval);
		delay_5us(inputInt*delayMul/24);
		}
		x--;
	}
}
//-----------------------------------------receive_data---------------------------
void receive_data(void) interrupt 4
{
if(RI==1)
{
	RI=0;
	input = SBUF;

}
else if(TI==1)
{
	TI=0;
}
}
//////////////////////////////////////////////////////////////////////////////////
void transmit_string(char* str,unsigned char  n)
{
//function to transmit string of size n over TxD pin.
while(n>0)
	{
		transmit_data(*str);
		str++;
		n--;
		TI=0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////
void transmit_data(unsigned char str)
{
//function to transmit data over TxD pin.
	EA = 0;	
	ACC = str;
	ACC = ACC+0;
	TB8 = PSW^0;
	SBUF = str;
	while(TI==0);
	EA =1;
}
//////////////////////////////////////////////////////////////////////////////////////////
void init_serial()
{
//Initialize serial communication and interrupts
	SCON |= 0xD0;
	EA = 1;
	ES =1;
	TMOD |= 0x20;
	TH1 = 0xcc;
	TR1 = 1;
}
////////////////////////////////////////////////////////////////////////////////////////////
void delay_5us(int delay)
{
	int d=0;
	while(delay>0)
	{
		for(d=0;d<2;d++);
		delay--;
	}
}
		float fillTable(int z)
{
	   return sin(2.0*3.1415927*(float)z/24.0);
}