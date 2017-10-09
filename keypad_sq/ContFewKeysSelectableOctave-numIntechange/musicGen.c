#include "at89c5131.h"
#include "stdio.h"

sbit op = P0^0;
int input=0,x = 0,delayMul=1;

void delay_5us(int delay);
void transmit_data(unsigned char str);
void transmit_string(char* str,unsigned int  n);
void init_serial();
void outputTone(unsigned int inputInt);
//void ISR_Serial(void);
//-----------------------------------------outputTone-----------------------------
void outputTone(unsigned int inputInt)
{
	x=10000/(inputInt*delayMul);
	while(x>0)
	{
		op = 1;
		delay_5us(inputInt*delayMul);
		op = 0;
		delay_5us(inputInt*delayMul);
		x--;
	}
}
//-------------------------------------------------MAIN--------------------------
void main()
{
P1 = 0x00;	//JUST TO SAVE POWER :P
P0 = 0x00;	// making P0^1 AS OUTPUT is enough though
init_serial();
transmit_string("Welcome to Music Tone Generator!",32);

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
	while(input=='q') 
	{
		//transmit_string("q ",2);
		outputTone(286);
		//input =0;
	}
	while(input=='w') 
	{
		//transmit_string("w ",2);
		outputTone(255);
		//input =0;
	}
	/////////////////////////////////////////fourth
	while(input=='e') 
	{
		//transmit_string("e ",2);
		outputTone(227);
		////input =0;
		//transmit_string("done ",4);
	}
	while(input=='r') 
	{
		//transmit_string("r ",2);
		outputTone(202);
		////input =0;
	}
	while(input=='t') 
	{
		//transmit_string("t ",2);
		outputTone(191);
		////input =0;
	}
	while(input=='y') 
	{
		//transmit_string("y ",2);
		outputTone(170);
		////input =0;
	}
	while(input=='u') 
	{
		//transmit_string("u ",2);
		outputTone(151);
		//input =0;
	}
	while(input=='i') 
	{
		//transmit_string("i ",2);
		outputTone(143);
		//input =0;
	}
	while(input=='o') 
	{
		//transmit_string("o ",2);
		outputTone(127);
		//input =0;
	}
	//////////////////////////////////////////////////////// only p
	while(input=='p') 
	{
		//transmit_string("p ",2);
		outputTone(114);
		//input =0;
	}
	///////////////////////////////////////    middle black ones part-1 of 2
	while(input=='!') 
	{
		//transmit_string("1 ",2);
		outputTone(1716);
		//input =0;
		//transmit_string("done ",4);
	}
	while(input=='@') 
	{
		//transmit_string("2 ",2);
		outputTone(1443);
		//input =0;
	}
	while(input=='#') 
	{
		//transmit_string("3 ",2);
		outputTone(1286);
		//input =0;
	}
	while(input=='$') 
	{
		//transmit_string("4 ",2);
		outputTone(1081);
		//input =0;
	}
	while(input=='%') 
	{
		//transmit_string("5 ",2);
		outputTone(963);
		//input =0;
	}
	while(input=='^') 
	{
		//transmit_string("6 ",2);
		outputTone(858);
		//input =0;
	}
	while(input=='&') 
	{
		//transmit_string("7 ",2);
		outputTone(722);
		//input =0;
	}
	while(input=='*') 
	{
		//transmit_string("8 ",2);
		outputTone(643);
		//input =0;
	}
	while(input=='(') 
	{
		//transmit_string("9 ",2);
		outputTone(540);
		//input =0;
	}
	while(input==')') 
	{
		//transmit_string("0 ",2);
		outputTone(482);
		//input =0;
	}
	//////////////////////////////////////////// middle black ones part2 of 2
	while(input=='1') 
	{
		//transmit_string("! ",2);
		outputTone(429);
		//input =0;
		//transmit_string("done ",4);
	}
	while(input=='2') 
	{
		//transmit_string("@ ",2);
		outputTone(361);
		//input =0;
	}
	while(input=='3') 
	{
		//transmit_string("# ",2);
		outputTone(321);
		//input =0;
	}
	while(input=='4') 
	{
		//transmit_string("$ ",2);
		outputTone(270);
		//input =0;
	}
	while(input=='5') 
	{
		//transmit_string("% ",2);
		outputTone(241);
		//input =0;
	}
	while(input=='6') 
	{
		//transmit_string("^ ",2);
		outputTone(214);
		//input =0;
	}
	while(input=='7') 
	{
		//transmit_string("& ",2);
		outputTone(180);
		//input =0;
	}
	while(input=='8') 
	{
		//transmit_string("* ",2);
		outputTone(161);
		//input =0;
	}
	while(input=='9') 
	{
		//transmit_string("( ",2);
		outputTone(135);
		//input =0;
	}
	while(input=='0') 
	{
		//transmit_string(") ",2);
		outputTone(120);
		//input =0;
	}
	
	////////////////////////////////////////////       END

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