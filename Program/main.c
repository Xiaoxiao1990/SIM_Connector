/* MAIN.C file
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "includes.h"
#define SCLK(c) 		(c)?(CLK_CCOR = 0B00001101):(CLK_CCOR = 0x00)//2M
#define POWER				PD_ODR_0
#define RST					PD_ODR_4
void main(void)
{
	uchar status;
	_configSet();
	POWER = 1;
	_timerBaseInitial();
	_uartInit();
	while(1)
	{
		_timerBase();
		switch(status)
		{
			case 0:
			{
				POWER = 1;
				RST = 0;
				SCLK(0);
				isRunTimer = 1;
				if(TimerCNT >= 10000)//5s
				{
					isRunTimer = 0;
					POWER = 0;
					SCLK(1);
					status++;
				}
			}break;
			case 1:SCLK(1);status++;break;
			case 2://wait for Tb
			{
				isRunTimer = 1;
				if(TimerCNT > 2)
				{//Tb >= 200us
					isRunTimer = 0;
					RST = 1;
					status++;
				}
			}break;
			case 3:
			{
				//Read ATR
				isRunTimer = 1;
				if(TimerCNT >= 20000)
				{//Time out
					isRunTimer = 0;
					RxPoint = 0;
					//status = 0;
					//SCLK(0);
				}
			}break;
			default:;
		}
		if(isTimeProcess)//about 500us
		{
			isTimeProcess = No;
		}
	}
}
