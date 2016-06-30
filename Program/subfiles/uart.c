#include "includes.h"
// Setup the UART to run at 115200 baud, no parity, one stop bit, 8 data bits.// Important: This relies upon the system clock being set to run at 16 MHz.
void _uartInit(void){
	//Clear the Idle Line Detected bit in the status register by a read to the UART1_SR register followed by a Read to the UART1_DR register. 
	uchar temp = UART1_SR; temp = UART1_DR;
	//Reset the UART register to the reset values.
	//UART1_CR1 = 0;
	//UART1_CR2 = 0;
	//UART1_CR3 = 0;
	UART1_CR4 = 0;
	UART1_CR5 = 0;
	UART1_GTR = 0;
	UART1_PSCR = 0;
	//Now setup the port to 115200,n,8,1.5
	//UART1_CR1_M = 1;// 8 Data bits 
	//UART1_CR1_PCEN = 1; // Enable parity.
	//UART1_CR1_PS = 1;//Even
	UART1_CR1 = 0x16; 
	//UART1_CR3_STOP = 0; // 1 stop bit.
	UART1_CR3 = 0x00; 
	UART1_BRR2 = 0x10; // Set the baud rate registers to 5376 baud based upon a 8 MHz system clock 
	UART1_BRR1 = 0x50; // Disable the transmitter and receiver 
	//UART1_CR2_TEN = 0; 
	//UART1_CR2_REN = 0; 
	
	//UART1_CR2 = 0; // Set the clock polarity, lock phase and last bit clock pulse. 
	
	//UART1_CR3_CPOL = 1;
	//UART1_CR3_CPHA = 1;
	//UART1_CR3_LBCL = 1;
	UART1_CR3 |= 0x07; // Turn on the UART transmit, receive and turn off the UART clock. 
	//UART1_CR2_TEN = 1; 
	//UART1_CR2_REN = 1;
	//UART1_CR3_CKEN = 0;
	UART1_CR2 = 0x2c;
	_asm("rim");
}
void sendByte(uchar data)
{
	while(!(UART1_SR&0x80));//while Tx_DR is not empty
	UART1_DR = data;
	while(!(UART1_SR&0x40));//while is not complete
}

void _sendStrings(uchar *data)
{
	uchar *ch = data;
	while(*ch)
	{
		sendByte(*ch);
		ch++;
	}
}
