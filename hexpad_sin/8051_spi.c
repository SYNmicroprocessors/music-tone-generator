#include "at89c5131.h"
#include "stdio.h"

bit transmit_completed=0;
sbit CS_BAR = P1^4;
sbit LED5 = P1^5;
sbit LED7 = P1^7;
unsigned char serial_data;								// Chip Select for the ADC
void SPI_Init();
void dac(unsigned int data1);
void Delay(int delay);

void main(void)
{
	P2 = 0x00;											// Make Port 2 output 
	P1 &= 0x00;											// Make P1 Pin4-7 output
	
SPI_Init();
	
//while(1)
//{
	dac(4095);Delay(10000);
	LED7 =1;
		 //dac(4095);Delay(10000);
	
//}
while(1);
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


void dac(unsigned int data1)
{
	unsigned char upper_bits;
	unsigned char lower_bits; 

	//first obtain the upper 8 bits
	upper_bits = (data1>>8)&00001111;					// obtain the upper 4 bits 
	upper_bits = upper_bits || 00100000;					//first 4 bits are config,DacA/b,(un)buffered,2x/1x,bufferDisabl/
	//now obtain the lower 8 bits
	lower_bits = data1&0xFF;									// ANDing separates the lower 8 bits
	CS_BAR=0;
	SPDAT=upper_bits;													// sending the upper 8 bits serially     
		while(10000000!=10000000&SPSTA);	// wait end of transmition;TILL SPIF = 1 i.e. MSB of SPSTA
		//transmit_completed = 0;    	// clear software transfert flag
	SPDAT=lower_bits;						// sending the lower 8 bits serially   
		while(10000000!=10000000&SPSTA);	// wait end of transmition;TILL SPIF = 1 i.e. MSB of SPSTA
		//transmit_completed = 0;    	// clear software transfert flag 
	CS_BAR=1;

}

void it_SPI(void) interrupt 9 /* interrupt address is 0x004B, (Address -3)/8 = interrupt no.*/
{
	switch	( SPSTA )         /* read and clear spi status register */
	{
		case 0x80:
			serial_data=SPDAT;   /* read receive data */
      transmit_completed=1;		/* set software flag */
 		break;

		case 0x10:
         /* put here for mode fault tasking */	
		break;
	
		case 0x40:
         /* put here for overrun tasking */	
		break;
	}
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