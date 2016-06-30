#include "includes.h"

#define IN_SET_TIME 5		//5 seconds
#define pinRelay 	PD_ODR_1
#define pinYellow PB_ODR_5
#define pinBuzzer PD_ODR_4
#define BUZZER_TIME 150

void _timerBaseInitial(void)
{//500us
	TIM4_IER = 0x00; // disable interrup
	TIM4_EGR = 0x01; // enable update
	TIM4_PSCR = 4; // timerclock=manclock/64=8MHZ/128=16us
	TIM4_ARR = 250; // set reload resister  timer 16us*125*2 = 4ms
	TIM4_CNTR = 250; // set conter initial,cycle time=(ARR+1)*16=2.048ms
	TIM4_CR1 = 0x01; // b0 = 1,enable timer 4,b1 = 0, enable update
}

void _timer2_Initial(void)
{
	//初始化定时器2                               
  TIM2_IER = 0x00;            // 禁止中断
  TIM2_EGR = 0x01;            // 允许产生更新事件
  TIM2_PSCR = 0x03;           // 计数器时钟=fmaster/prescaler = 8M/(2^3) = 1Mhz
															// 相当于计数器周期为1uS
														  // 设定重装载时的寄存器值
															// 注意必须保证先写入高8位，再写入低8位
  TIM2_ARRH = 0xc3;           // 设定重装载时的寄存器的高8位
  TIM2_ARRL = 0x50;  
  
  TIM2_CNTRH = 0xc3;          // 设定计数器的初值
  TIM2_CNTRL = 0x50;             
                              // 定时周期=1*50000=50000uS=50ms

  TIM2_CR1 = 0x01;            // b0 = 1,允许计数器工作
                              // b1 = 0,允许更新
                              // 设置控制器，启动定时器
  TIM2_IER = 0x01;            // 允许更新中断
  _asm("rim");                // 允许CPU全局中断
}

void _timerBase(void)		//4.080ms
{											
	if (bitTIM4_SR1_UIF) // 
	{
		bitTIM4_SR1_UIF = 0; 
		if(isRunTimer)TimerCNT++;
		else TimerCNT = 0;
	}
}

void _timerWheel(void)
{
	static uchar time_CNT = 0;
	
	if(isInRx)//Rx time out counter
	{
		if(++RxTimer > 4)
		{
			RxTimer = 0;
			isInRx = 0;
			isReceiveComplete = Yes;
		}
	}
	else
	{
		RxTimer = 0;
	}
	
	if(isOneSecond)
	{
		isOneSecond = 0;
		if(isLowVoltage)
		{
			if(++time_CNT > 10)
			{
				time_CNT = 0;
				isLowVoltage = 0;
				_LCD_BackLight(1);
			}
		}
		else
		{
			time_CNT = 0;
		}
	}
}