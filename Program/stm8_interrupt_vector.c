/*	BASIC INTERRUPT VECTOR TABLE FOR STM8 devices
 *	Copyright (c) 2007 STMicroelectronics
 */
#include "includes.h"

typedef void @far (*interrupt_handler_t)(void);

struct interrupt_vector {
	unsigned char interrupt_instruction;
	interrupt_handler_t interrupt_handler;
};

@far @interrupt void NonHandledInterrupt (void)
{
	/* in order to detect unexpected events during development, 
	   it is recommended to set a breakpoint on the following instruction
	*/
	return;
}

extern void _stext();     /* startup routine */

@far @interrupt void TIM2_UPD_IRQHandler (void)
{
	/* in order to detect unexpected events during development, 
	   it is recommended to set a breakpoint on the following instruction
	*/
	static uchar basicTimeCNT = 0,showmessage_CNT = 0;
	TIM2_SR1 = 0x00;          			// 清除更新标志
	if(++basicTimeCNT > 19)					//20*50ms = 1s
	{
		basicTimeCNT = 0;
		isOneSecond = Yes;
		
		if(isShowMessage)
		{
			if(++showmessage_CNT > 4)
			{
				showmessage_CNT = 0;
				isShowMessage = 0;
			}
		}
		else
		{
			showmessage_CNT = 0;
		}
	}
	if((basicTimeCNT%4) == 0)
	{
		isUpdateData = Yes;
		isGetData = 1;
	}
}

@far @interrupt void UART1_RX_IRQHandler (void)
{
	uchar temp;
	isInRx = Yes;
	RxTimer = 0;//Rx Timer
	//UART1_SR &= 0x28;
	temp = UART1_SR;
	temp = UART1_DR;
//	if(isReceiveComplete)return;//Wait for process
//	else
	{
		if(RxPoint > RX_BUF_LEN - 2)RxPoint = 0;
		RxBuffer[RxPoint++] = temp; //Store the received byte in RxBuffer
//		RxBuffer[0] = temp;
	}
}

struct interrupt_vector const _vectab[] = {
	{0x82, (interrupt_handler_t)_stext}, /* RESET */
	{0x82, NonHandledInterrupt}, /* TRAP  */
	{0x82, NonHandledInterrupt}, /* TLI  */
	{0x82, NonHandledInterrupt}, /* AWU  */
	{0x82, NonHandledInterrupt}, /* CLK Clock Controller */
	{0x82, NonHandledInterrupt}, /* EXTI0 Port A  */
	{0x82, NonHandledInterrupt}, /* EXTI1 Port B  */
	{0x82, NonHandledInterrupt}, /* EXTI2 Port C  */
	{0x82, NonHandledInterrupt}, /* EXTI3 Port D  */
	{0x82, NonHandledInterrupt}, /* EXTI4 Port E  */
	{0x82, NonHandledInterrupt}, /* CAN Rx  */
	{0x82, NonHandledInterrupt}, /* CAN Tx/ER/SC  */
	{0x82, NonHandledInterrupt}, /* SPI complete */
	{0x82, NonHandledInterrupt}, /* TIM1 Update/Over Flow/Trigger/Brake */
	{0x82, NonHandledInterrupt}, /* TIM1 Compare/Capture */
	{0x82, TIM2_UPD_IRQHandler}, /* TIM2 Update/Over High */
	{0x82, NonHandledInterrupt}, /* TIM2 Compare/Capture */
	{0x82, NonHandledInterrupt}, /* TIM3 Update/Over High */
	{0x82, NonHandledInterrupt}, /* TIM3 Compare/Capture */
	{0x82, NonHandledInterrupt}, /* UART1 Send Complete */
	{0x82, UART1_RX_IRQHandler}, /* UART1 Receive Register Full */
	{0x82, NonHandledInterrupt}, /* I2C */
	{0x82, NonHandledInterrupt}, /* UART2/3 Send Complete */
	{0x82, NonHandledInterrupt}, /* UART2/3 Receive Register Full */
	{0x82, NonHandledInterrupt}, /* ADC Convert Complete */
	{0x82, NonHandledInterrupt}, /* TIM4 Update/Over High */
	{0x82, NonHandledInterrupt}, /* Flash Program complete/Program Forbidden */
	{0x82, NonHandledInterrupt}, /* Reseve */
	{0x82, NonHandledInterrupt}, /* Reseve */
	{0x82, NonHandledInterrupt}, /* Reseve */
	{0x82, NonHandledInterrupt}, /* Reseve */
	{0x82, NonHandledInterrupt}, /* Reseve */
};
