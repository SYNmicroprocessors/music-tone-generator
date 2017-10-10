#include "at89c5131.h"
#include "stdio.h"

bit transmit_completed=0;
sbit CS_BAR = P1^4;
unsigned char serial_data;								// Chip Select for the ADC
void SPI_Init();
void dac(unsigned int data1);
unsigned int k=0;
void Delay(int delay);
code unsigned int table[24]= {2047,2577,3070,3494,3820,4024,4094,4024,3820,3494,3070,2577,2047,1517,1023,599,274,70,0,70,274,600,1023,1517};
void outputTone(unsigned int inputInt)
{

	for(k=0;k<24;k++)
		{
		dac(table[k]);
		//delay_5us(100*inputInt*delayMul*0.041667);
		}
		//x--;
	//}
}
void main(void)
{
	P2 = 0x00;											// Make Port 2 output 
	//P1 &= 0xEF;											// Make P1 Pin4-7 output
	P0 &= 0xF0;											// Make Port 0 Pins 0,1,2 output
	P1 |= 0xF0;
	
	SPI_Init();
	
while(1)
{
	outputTone(454);
		 //dac(4095);Delay(10000);
	
}
//while(1);
}



void SPI_Init()
{
	CS_BAR = 1;	                  	// DISABLE ADC SLAVE SELECT-CS 
	SPCON |= 0x20;               	 	// P1.1(SSBAR) is available as standard I/O pin 
	SPCON |= 0x01;                	// Fclk Periph/4 AND Fclk Periph=12MHz ,HENCE SCK IE. BAUD RATE=3000KHz 
	SPCON |= 0x10;               	 	// Master mode 
	SPCON &= ~0x08;               	// CPOL=0; transmit mode example|| SCK is 0 at idle state
	SPCON |= 0x04;                	// CPHA=1; transmit mode example 
	IEN1 |= 0x04;                	 	// enable spi interrupt 
	EA=1;                         	// enable interrupts 
	SPCON |= 0x40;                	// run spi;ENABLE SPI INTERFACE SPEN= 1 
}


void dac(unsigned int dacval)
{
	unsigned char sendval = 0;
	sendval = (dacval >> 8 | 0x70);
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

void it_SPI(void) interrupt 9 /* interrupt address is 0x004B, (Address -3)/8 = interrupt no.*/
{	LED5 =1;
	switch	( SPSTA )         /* read and clear spi status register */
	{
		case 0x80:
			//serial_data=SPDAT;   /* read receive data */
      transmit_completed=1;		/* set software flag */
 		break;

		case 0x10:
         /* put here for mode fault tasking */	
		break;
	
		case 0x40:
         /* put here for overrun tasking */	
		break;
		
	}
	//Delay(10000);
	LED5=0;
}
void Delay(int delay)
{
	int d=0;
	while(delay>0)
	{
		for(d=0;d<20;d++);
		delay--;
	}
}