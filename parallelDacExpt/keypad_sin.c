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

float spi_out=0;
int k=0;
unsigned int dacval;i=0;
unsigned char serial;
//code int sin[500];

sbit CS_BAR = P1^4;									
sbit LDAC_BAR = P1^3;
bit transmit_completed= 0;					


void main()
{

	P2 = 0x00;											// Make Port 2 output 
	//P1 &= 0xEF;											// Make P1 Pin4-7 output
	P0 = 0xF0;											// Make Port 0 Pins 0,1,2 output
	P1 |= 0xF0;

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
		for(i=0;i<8;i++)
		{
		//spi_out= fillTable(i);
		//spi_out = 2047*(1+spi_out);	
/*if(i==0){P0 = 00;}
if(i==1){P0 = 64;}
if(i==2){P0 = 128;}
if(i==3){P0 = 255;}
if(i==4){P0 = 128;}
if(i==5){P0 = 34;}
if(i==6){P0 = 128;}
if(i==7){P0 = 128;}
*/
			P0 = 0xff;
	//	delay_5us(inputInt*delayMul*0.0416667);
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