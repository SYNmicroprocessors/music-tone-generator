void send_dac(unsigned int dacval)
{
	unsigned char sendval = 0;
	sendval = (dacval >> 8 | 0x70;
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
