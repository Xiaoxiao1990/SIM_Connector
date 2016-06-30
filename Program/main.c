/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "includes.h"
#define SCLK(c) 		(c)?(CLK_CCOR = 0B00001101):(CLK_CCOR = 0x00)//2M
#define POWER				PD_ODR_0
#define RST					PD_ODR_4
main()
{
	uchar status;
	_configSet();
	POWER = 1;
//	_timer2_Initial();
	_timerBaseInitial();
//	_IOInitial();
//	_LCD_Init();
	_uartInit();
	//_EEPROM_Initial();
	/*Watch Dog*/
	//IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	//IWDG_SetPrescaler(IWDG_Prescaler_64);
	//IWDG_SetReload(0xff);
	//IWDG_ReloadCounter();
	//IWDG_Enable();
	//IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
	while(1)
	{
		//_displayAndKeyscan();
		_timerBase();
		//IWDG_ReloadCounter();//clear counter.
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
		if(isTimeProcess)//about 4ms
		{
			isTimeProcess = No;
			//_LCD_BackLight(1);
		//	_LCD_Init();
			//_output();
			//_timerWheel();
			//_displayDecode();
			//_keysProcess();
			//_LCD_Update();
		}
		//_messageProcess();
	}
}