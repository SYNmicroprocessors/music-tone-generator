#include "at89c5131.h"
#include "stdio.h"
#include "math.h"

int k=0;
unsigned int freq; off; amp; duty; dacval;i=0;
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
	EA = 1;
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
void delay(int delay)             
{
	int d=0;
	while(delay>0)
	{
		for(d=0;d<3;d++);
		delay--;
	}
}

/////////////////////// MAIN PROGRAM///////////////////////////////

void main()
{
		P2 = 0x00;											// Make Port 2 output 
	//P1 &= 0xEF;											// Make P1 Pin4-7 output
	P0 &= 0xF0;											// Make Port 0 Pins 0,1,2 output
	P1 |= 0xF0;
	
	SPI_Init();
	dacval  =  95;
	
	i=5;

		while(1)
			dac(dacval);
		
		
	


}