#include "at89c5131.h"
#include "stdio.h"

sbit op = P0^0;
int input=0,x = 0;

void delay_5us(int delay);
void transmit_data(unsigned char str);
void transmit_string(char* str,unsigned int  n);
void init_serial();
void outputTone(unsigned int inputInt);
//void ISR_Serial(void);
//-------------------------------------------------MAIN--------------------------
void main()
{
P1 = 0x00;	//JUST TO SAVE POWER :P
P0 = 0x00;	// making P0^1 AS OUTPUT is enough though
init_serial();
transmit_string("F - Fur Elise by Beethovan ",27);
transmit_string("B - Birthday song ",18);
//transmit_string("H - Harry Potter ",17);
while(1){

while(input == 'F')
{
	outputTone(191);	//t 
	outputTone(180);	//&
	outputTone(191);	//t
	outputTone(180);	//&
	outputTone(191);	//t
	outputTone(255);	//w
	outputTone(202);	//r
	outputTone(227);	//e
	outputTone(286);	//q
	if(input != 'F'){break;}
	delay_5us(5000);
	
	outputTone(454);	//g
	outputTone(382);	//j
	outputTone(286);	//q
	outputTone(255);	//w
	if(input != 'F'){break;}
	delay_5us(5000);
	
	outputTone(382);	//j
	outputTone(270);	//$
	outputTone(255);	//w
	outputTone(227);	//e
	if(input != 'F'){break;}
	delay_5us(5000);
	
	outputTone(191);	//t
	outputTone(180);	//&
	outputTone(191);	//t
	outputTone(180);	//&
	outputTone(191);	//t
	outputTone(255);	//w
	outputTone(202);	//r
	outputTone(227);	//e
	outputTone(286);	//q
	if(input != 'F'){break;}
	delay_5us(5000);
	
	outputTone(454);	//g
	outputTone(382);	//j
	outputTone(286);	//q
	outputTone(255);	//w
	if(input != 'F'){break;}
	delay_5us(5000);
	
	outputTone(382);	//j
	outputTone(227);	//e
	outputTone(255);	//w
	outputTone(286);	//q
	if(input != 'F'){break;}
	delay_5us(2000);	
	
	outputTone(255);	//w
	outputTone(227);	//e
	outputTone(202);	//r
	outputTone(191);	//t
	if(input != 'F'){break;}
	delay_5us(5000);
	
	outputTone(303);	//L
	outputTone(170);	//y
	outputTone(191);	//t
	outputTone(202);	//r
	if(input != 'F'){break;}
	delay_5us(5000);
	
	outputTone(340);	//k
	outputTone(191);	//t
	outputTone(202);	//r
	outputTone(227);	//e
	if(input != 'F'){break;}
	delay_5us(5000);
	
	outputTone(382);	//j
	outputTone(202);	//r
	outputTone(227);	//e
	outputTone(255);	//w
	if(input != 'F'){break;}
	delay_5us(5000);
	
	outputTone(382);	//j
	delay_5us(2000);
	outputTone(382);	//j
	delay_5us(2000);
	outputTone(191);	//t
	delay_5us(2000);
	outputTone(191);	//t
	delay_5us(2000);
	outputTone(382);	//j
	delay_5us(2000);
	outputTone(382);	//j
	
	delay_5us(10000);
}
/*	//Harry Potter - timing btwn tones is not good
while(input == 'H')
{	
	outputTone(255);	delay_5us(1000);	//w
	outputTone(191); 	delay_5us(1000);  //t
	outputTone(151);	//u
	outputTone(161);	delay_5us(1000);//*
	outputTone(191);	delay_5us(1000);delay_5us(1000);//t
	outputTone(127);	//o
	outputTone(143);	delay_5us(1000);delay_5us(1000);//i
	outputTone(161);	delay_5us(1000);//*
	outputTone(191);	delay_5us(1000);delay_5us(1000);//t
	outputTone(151);	delay_5us(1000);delay_5us(1000);//u
	outputTone(161);	//*
	outputTone(202);	delay_5us(1000);delay_5us(1000);//r
	outputTone(170);	delay_5us(1000);//y
	outputTone(255);	delay_5us(1000);//w
	
	delay_5us(5000);
}
*/
while(input == 'B')
{	
	outputTone(454);	delay_5us(2000);//g
	outputTone(454);	//g
	outputTone(405);	delay_5us(5000);//h
	outputTone(454);	delay_5us(5000);//g
	outputTone(340);	delay_5us(5000);//k
	outputTone(382);	delay_5us(5000);//j
	delay_5us(5000);
	outputTone(454);	delay_5us(2000);//g
	outputTone(454);	//g
	outputTone(405);	delay_5us(5000);//h
	outputTone(454);	delay_5us(5000);//g
	outputTone(303);	delay_5us(5000);//l
	outputTone(340);	delay_5us(5000);//k
	delay_5us(5000);
	outputTone(454);	delay_5us(2000);//g
	outputTone(454);	//g
	outputTone(227);	delay_5us(5000);//e
	outputTone(286);	delay_5us(5000);//q
	outputTone(340);	delay_5us(5000);//k
	outputTone(382);	delay_5us(5000);//j
	delay_5us(5000);
	outputTone(241);	delay_5us(2000);//%
	outputTone(241);	//%
	outputTone(286);	delay_5us(5000);//q
	outputTone(340);	delay_5us(5000);//k
	outputTone(303);	delay_5us(5000);//l
	outputTone(340);	delay_5us(5000);//k

delay_5us(10000);
}

}
}
//-----------------------------------------outputTone-----------------------------
void outputTone(unsigned int inputInt)
{
	x=15000/inputInt;
	while(x>0)
	{
		op = 1;
		delay_5us(inputInt*0.5);
		op = 0;
		delay_5us(inputInt*0.5);
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