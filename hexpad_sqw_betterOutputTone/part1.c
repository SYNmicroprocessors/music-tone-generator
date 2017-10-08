#include <at89c5131.h>
#include <stdio.h>
#include <math.h>
//-----------------------Keypad Connections
sbit R1 = P1^0;
sbit R2 = P1^1;
sbit R3 = P1^2;
sbit R4 = P1^3;
sbit C1 = P1^4;
sbit C2 = P1^5;
sbit C3 = P1^6;
sbit C4 = P1^7;
//------------------------End Keypad Connections
sbit output = P0^0;
float freq_multiplier=1.0;
float octave=1.0,base_freq,freq,table_i;
int i=0,ix=0;
int press=0;
void Delay(int delay);
//----------------------function for reading keypad
void Read_Keypad()
{
  C1=1;
  C2=1;
  C3=1;
  C4=1;
  R1=0;
  R2=1;
  R3=1;
  R4=1;
  if(C1==0){Delay(10);while(C1==0);freq_multiplier=1.0;press=1;}
  if(C2==0){Delay(10);while(C2==0);freq_multiplier=1.0667;press=1;}
  if(C3==0){Delay(10);while(C3==0);freq_multiplier=1.125;press=1;}
  if(C4==0){Delay(10);while(C4==0);freq_multiplier=1.1852;press=1;}
  R1=1;
  R2=0;
  R3=1;
  R4=1;
  if(C1==0){Delay(10);while(C1==0);freq_multiplier=1.25;press=1;}
  if(C2==0){Delay(10);while(C2==0);freq_multiplier=1.3333;press=1;}
  if(C3==0){Delay(10);while(C3==0);freq_multiplier=1.422;press=1;}
  if(C4==0){Delay(10);while(C4==0);freq_multiplier= 1.5;press=1;}
  R1=1;
  R2=1;
  R3=0;
  R4=1;
  if(C1==0){Delay(10);while(C1==0);freq_multiplier=1.6;press=1;}
  if(C2==0){Delay(10);while(C2==0);freq_multiplier=1.6875;press=1;}
  if(C3==0){Delay(10);while(C3==0);freq_multiplier=1.7778;press=1;}
  if(C4==0){Delay(10);while(C4==0);freq_multiplier=1.875;press=1;}
  R1=1;
  R2=1;
  R3=1;
  R4=0;
  if(C1==0){Delay(10);while(C1==0);octave=1.0;press=1;}
  if(C2==0){Delay(10);while(C2==0);octave=2.0;press=1;}
  if(C3==0){Delay(10);while(C3==0);octave=4.0;press=1;}
  if(C4==0){Delay(10);while(C4==0);octave=8.0;press=1;}
 
}
//---------------------------funtion for signal output
void OutputTone(float freq)
{
	int delay =0;
	ix=10;
	while(ix>0){
		delay = (100000.0/freq);
		output =1;
		Delay(delay);
		output =0;
		Delay(delay);
		ix--;
		table_i = sin(2.0*3.1415927*(float)i/24.0);
	}
}
//-------------------------------------------------------
void main(void)
{
	P0=0x00;
	P1=0xf0;
	//fillTable();
	output=0;
	base_freq = 1000.0;
	press=0;
	while(1)
	{	
		Read_Keypad();
		while(press==1)
		{
			Read_Keypad();
			freq= octave*base_freq*freq_multiplier;
			OutputTone(freq);
		}
	}
	
}

//---------------------------------delay function
void Delay(int delay)
{
	int d=0;
	while(delay>0)
	{
		for(d=0;d<20;d++);
		delay--;
	}
}