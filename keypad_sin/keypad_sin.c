#include "at89c5131.h"
#include "stdio.h"
#include "math.h"

sbit op = P0^0;
int input=0,x = 0;

void delay_5us(int delay);
void transmit_data(unsigned char str);
void transmit_string(char* str,unsigned int  n);
void init_serial();
void outputTone(void);

void main()
{
P1 = 0x00;	//JUST TO SAVE POWER :P
P0 = 0x00;	// making P0^1 AS OUTPUT is enough though
init_serial();
transmit_string("Tone Generator",14);

while(1)
{
	////////////////////////////////////////first
	if(input=='z') 
	{
		//transmit_string("z ",2);
		outputTone();		//1818
		//input =0;
		transmit_string("done ",4);
	}
}

}
//-----------------------------------------outputTone-----------------------------
void outputTone(void)
{
	
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