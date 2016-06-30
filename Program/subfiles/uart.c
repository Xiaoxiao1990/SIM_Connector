#include "includes.h"

extern char *n2s(long Num);
extern char *t2s(Time_TypeDef *time);
extern void strcat(uchar *dest,uchar *s1,uchar *s2);
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
/*This function for Master MCU*/
/*void sendOneLine(uchar *a,uchar *b,uchar *c,uchar *d)
{
	_sendStrings(a);
	_sendStrings(b);
	_sendStrings(c);
	_sendStrings("£º");
	_sendStrings(d);
	_sendStrings("\n");
}
*/
uchar RxlongData(long *data)
{//0~9999999
	uchar i;
	long temp = 0;
	for(i = 0;i < 8;i++)
	{
		if((RxBuffer[i+4] <= '9')&&((RxBuffer[i+4] >= '0')))
		{
			temp *= 10;
			temp += (RxBuffer[i+4] - 0x30);
		}
		else if((RxBuffer[i+4] == ' ')||(RxBuffer[i+4] == '-'))
		{
			;
		}
		else 
		{
			return 0;
		}
	}
	if((temp <= 9999999)&&(temp >= 0))
	{
		*data = temp;
		return 1;
	}
	else
	{
		return 0;
	}
}
uchar RxintData(uint *data)
{
	uchar i;
	uint temp = 0;
	for(i = 3;i < 8;i++)
	{
		if((RxBuffer[i+4] <= '9')&&((RxBuffer[i+4] >= '0')))
		{
			temp *= 10;
			temp += (RxBuffer[i+4] - 0x30);
		}
		else if((RxBuffer[i+4] == ' ')||(RxBuffer[i+4] == '-'))
		{
			;
		}
		else 
		{
			return 0;
		}
	}
	if((temp <= 59999)&&(temp >= 0))
	{
		*data = temp;
		return 1;
	}
	else
	{
		return 0;
	}
}
uchar RxtimeData(Time_TypeDef *time)
{
	uchar i;
	for(i = 0;i < 8;i++)
	{
		//Data check
		if((i == 2)||(i == 5))
		{
			if(RxBuffer[i+4] != ':')
			{
				return 0;
			}
		}
		else if((RxBuffer[i+4] > '9')||((RxBuffer[i+4] < '0')))
		{
			return 0;
		}
		else
		{
			RxBuffer[i+4] -= 0x30;
		}
	}
	time->hh = RxBuffer[4]*10 + RxBuffer[5];
	time->mm = RxBuffer[7]*10 + RxBuffer[8];
	time->ss = RxBuffer[10]*10 + RxBuffer[11];
	return 1;
}

void ReceiveData(uchar OpCode)
{
	uchar flag;
	long temp = 0;
	switch(OpCode)
	{
		case 0://Read total
		{
			flag = RxlongData(&Total_V);
		}break;
		case 1://Read total last
		{
			flag = RxlongData(&Total_V_last);
		}break;
		case 2://Read addition
		{
			flag = RxlongData(&Addition_V);
		}break;
		case 3://Read addition last
		{
			flag = RxlongData(&Addition_V_last);
		}break;
		case 4://Read emission
		{
			flag = RxtimeData(&Emission_T);
		}break;
		case 5://Read emission last
		{
			flag = RxtimeData(&Emission_T_last);
		}break;
		case 6://Read emission start time
		{
			flag = RxtimeData(&EmissionStart_T);
		}break;
		case 7://pulseNumber2
		{
			flag = RxintData(&PulseNumber2);
		}break;
		case 8://Normal Output
		{
			flag = RxintData(&PulseNumber1);
		}break;
		case 9://Emission Output
		{
			if(RxBuffer[11] == '1')OutputStatus = 1;
			else if(RxBuffer[11] == '0')OutputStatus = 0;
		}break;
		case 10://TDS 
		{
			flag = RxintData(&TDS);
		}break;
		case 11:
		{
			flag = RxlongData(&Continue_V_Bkp);
		}break;
		case 12:// TDS set value
		{
			flag = RxintData(&TDS_SET);
		}break;
		case 13:
		{
			flag = RxintData(&PulseNumber1);
		}break;
		case 14:
		{
			flag = RxlongData(&Continue_V);
		}break;
		case 15:
		{
			flag = RxintData(&PulseNumber2);
		}break;
		default:;
	}
}


void frameDecode(void)
{
	uchar i = 0;
	if(isReceiveComplete)
	{
		if((RxBuffer[0] == 'S')||(RxBuffer[0] == 's'))
		{
			if((RxBuffer[1] == 'C')||(RxBuffer[1] == 'c'))
			{
				if((RxBuffer[2] == 'D')||(RxBuffer[2] == 'd'))//data
				{
					ReceiveData(RxBuffer[3]);
				}
				else if((RxBuffer[2] == 'A')||(RxBuffer[2] == 'a'))//acknowledge
				{
					if(RxBuffer[3] == '1')
					{
						MessageNo = 1;
					}
					else if(RxBuffer[3] == 'L')//Low Voltage
					{
						MessageNo = 2;
						isLowVoltage = 1;
						_LCD_BackLight(0);
					}
					else if(RxBuffer[3] == 'O')//Use times Overflow.
					{
						MessageNo = 3;
					}
					else
					{
						MessageNo = 0;
					}
					isShowMessage = 1;
				}
				else
				{
					//_sendStrings("Error 0:Opereat Type Error!\n");
				}
			}
		}
		for(;RxPoint > 0;RxPoint--)RxBuffer[RxPoint] = 0;//Flush Rx buffer
		isReceiveComplete = Clear;//Process complete.
		isUpdateData = Yes;
	}
}

void _messageProcess(void)
{
	frameDecode();
}