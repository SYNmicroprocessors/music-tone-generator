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
unsigned int table[24];

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
	//SPCON |= 0x82; 
	SPCON |= 0x10;               	 	// Master mode 
	//SPCON &= ~0x08;               	// CPOL=0; transmit mode example|| SCK is 0 at idle state
	SPCON |= 0x08;
	SPCON |= 0x04;                	// CPHA=1; transmit mode example 
	IEN1 |= 0x04;                	 	// enable spi interrupt 
	SPCON |= 0x40;                	// run spi;ENABLE SPI INTERFACE SPEN= 1 
	//EA = 1;
}
void init_table(void)
{
if(i==0){table[i]=2047;}if(i==1){table[i]=2577;}if(i==2){table[i]=3070;}if(i==3){table[i]=3494;}if(i==4){table[i]=3820;}if(i==5){table[i]=4024;}
if(i==6){table[i]=4094;}if(i==7){table[i]=4024;}if(i==8){table[i]=3820;}if(i==9){table[i]=3494;}if(i==10){table[i]=3070;}if(i==11){table[i]=2577;}
if(i==12){table[i]=2047;}if(i==13){table[i]=1517;}if(i==14){table[i]=1023;}if(i==15){table[i]=599;}if(i==16){table[i]=274;}if(i==17){table[i]=70;}
if(i==18){table[i]=0;}if(i==19){table[i]=70;}if(i==20){table[i]=274;}if(i==21){table[i]=600;}if(i==22){table[i]=1023;}if(i==23){table[i]=1517;}
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
{int z= 0;
	for(z=0;z<2;z++)
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
	}
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
	init_table();
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
}

}
//-----------------------------------------outputTone-----------------------------
void outputTone(unsigned int inputInt)
{
	//x=10000/(inputInt*delayMul);
	//while(x>0)
	//{
		/*for(i=0;i<24;i++)
		{
		//spi_out= fillTable(i);
		//spi_out = 2047*(1+spi_out);	
			if(i==0){dac(2047);}if(i==1){dac(2577);}if(i==2){dac(3070);}if(i==3){dac(3494);}if(i==4){dac(3820);}if(i==5){dac(4024);}
if(i==6){dac(4094);}if(i==7){dac(4024);}if(i==8){dac(3820);}if(i==9){dac(3494);}if(i==10){dac(3070);}if(i==11){dac(2577);}
if(i==12){dac(2047);}if(i==13){dac(1517);}if(i==14){dac(1023);}if(i==15){dac(599);}if(i==16){dac(274);}if(i==17){dac(70);}
if(i==18){dac(0);}if(i==19){dac(70);}if(i==20){dac(274);}if(i==21){dac(600);}if(i==22){dac(1023);}if(i==23){dac(1517);}
		//dac(dacval);
		delay_5us(inputInt*delayMul*0.0416667);
		}*/
	for(k=0;k<24;k++)
		{
		dac(table[k]);
		delay_5us(inputInt*delayMul*0.0416667);
		}
		//x--;
	//}
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
	