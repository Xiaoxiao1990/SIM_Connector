#include "includes.h"

void _configSet(void)
{
	/***************************************************************
	========================== IO setting ==========================
	DDR CR1 CR2 Function
	0	   0   0   Floating without interrupt input 
	0    0   1   Floating with interrupt input
	0    1   0   Pull-up without interrupt input
	0    1   1   Pull-up with interrupt input
	1    0   0   Open drain output
	1		 0	 1	 Open drain output,fast mode
	1    1   0   Push-pull output
	1    1   1	 Push-pull output,fast mode  
STM8S103K3
  ***************************************************************/
	PA_DDR = 0B00000000; 
	PA_CR1 = 0B00000000; 
	PA_CR2 = 0B00000000;
	PA_ODR = 0B00000000;	
	
	PB_DDR = 0B11111111;//Data
	PB_CR1 = 0B11111111;	
	PB_CR2 = 0B00000000;
	PB_ODR = 0B00110000;

	PC_DDR = 0B00000000;
	PC_CR1 = 0B00111110; 
	PC_CR2 = 0B00000000;
	PC_ODR = 0B00000000;
	 
	PD_DDR = 0B00011101;
	PD_CR1 = 0B00011101;
	PD_CR2 = 0B00000000;
	PD_ODR = 0B00000000;
	/***************************************************************
	======================== system clock ==========================
	internal clock: 8MHz
  ***************************************************************/
	
	// ---------------high internal oscilator--------------------
	//CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV2);
	//CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);	//system clk 8M
	
	CLK_SWR = 0xE1; 		//internal clock 16M as main clock
	CLK_CKDIVR = 0x08;  //fcpu = fmaster = fHSI/2 = 8MHz
}