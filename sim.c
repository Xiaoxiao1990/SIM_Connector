#include "includes.h"

#define ON 		1
#define OFF		0
/* Reset Status Define */
#define POWER_OFF			0
#define POWER_ON			1
#define CLOCK_ON			2
#define RST_ON				3
#define WAIT_ATR			4
#define READ_ATR			5

#define SCLK(c) 		(c)?(CLK_CCOR = 0B00001101):(CLK_CCOR = 0x00)//2M
#define POWER				PD_ODR_0
#define RST					PD_ODR_4

_Bool SIM_Reset(void)
{
	static uchar status = 0;
	switch(status)
	{
		case POWER_OFF:
		{
			POWER = Clear;
			RST = Clear;
			SCLK(OFF);
			isRunTimer = Set;
			if(TimerCNT >= 100)//50ms wait for stable level
			{
				isRunTimer = Reset;
				TimerCNT = 0;
				status++;
			}
		}break;
		case POWER_ON:
		{
			POWER = ON;
			status++;
		}break;
		case CLOCK_ON:
		{
			SCLK(ON);
			status++;
		}break;
		case RST_ON:
		{
			isRunTimer = Set;
			if(TimerCNT > 40)//
			{
				isRunTimer = Clear;
				TimerCNT = 0;
				RST = Set;
				status++;
			}
		}break;
		case WAIT_ATR:
		{
			isRunTimer = Set;
			if(TimerCNT > 1)//
			{
				isRunTimer = Clear;
				TimerCNT = 0;
				status++;
			}
		}break;
		case READ_ATR:
		{
			if(isFrameComplete)
			{//Received
				status = 0;
				RST = Reset;
				SCLK(OFF);
				POWER = OFF;
				if(RxPoint != 0)return 1;
			}
		}break;
		default:;
	}
	return 0;
}