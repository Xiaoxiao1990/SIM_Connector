#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#include "stm8s103K.h"					/*Register map*/
#include "stm8s_bitsdefine.h"
#include "io_devices.h"
#include "time.h"
#include "config.h"
#include "uart.h"
#include "lcd.h"
#include "eeprom.h"

#define Yes 1
#define No  0

#define Set 	1
#define Reset 0

#define RX_BUF_LEN 32

#define Clear Reset

typedef unsigned char uchar;
typedef unsigned int uint;
typedef struct{
	uchar hh;
	uchar mm;
	uchar ss;
}Time_TypeDef;
/*
typedef struct{
	long *total_v;
	long *total_v_last;
	long *addition_v;
	long *addition_v_last;
	Time_TypeDef *emission_t;
	Time_TypeDef *emission_t_last;
	Time_TypeDef *emissionstart_t;
	Time_TypeDef *emissionstart_t_last;
	uint *pulsenumber;
	uchar *outputstatus;
	uint *tds;
	Time_TypeDef *now;
}Menu_Data_TypeDef;//Menu_Data;
*/
extern _Bool isUpdateDisplay;
extern _Bool isUpdateData;
extern _Bool isGetData;
extern uchar isSetting;
extern uchar MenuBar;
extern uchar CDRAM[4][16];
extern _Bool isTimeProcess;
extern _Bool isOneSecond;
/*
extern _Bool isValve;
extern _Bool isNormal;
extern _Bool isEmission;
extern _Bool isCanEmission;
*/
extern Time_TypeDef Now;
extern uchar RxBuffer[RX_BUF_LEN];
extern uchar RxPoint;
extern _Bool isReceiveComplete;
extern _Bool isInRx;
extern uchar RxTimer;
extern uint PulseNumber1;
extern uint PulseNumber2;
extern uint FlowMeter;
extern long Total_V;
extern long Total_V_last;
extern long Addition_V;
extern long Addition_V_last;
extern long Continue_V;
extern long Continue_V_Bkp;
extern Time_TypeDef Emission_T;
extern Time_TypeDef Emission_T_last;
extern Time_TypeDef EmissionStart_T;
extern Time_TypeDef EmissionStart_T_last;
extern uchar OutputStatus;//输出状态控制，常开或常闭
extern _Bool Valve_Status;
extern _Bool isShowMessage;
extern uchar MessageNo;
extern _Bool isLogin;
extern uchar LoGinPage;
extern uint TDS;
extern uint TDS_SET;
//for reverse display
extern uchar From;
extern uchar To;
extern uchar Line;
extern uint Origin_Password;
extern uint User_Password;
extern uint Origin_Password1;
extern uint User_Password1;
extern _Bool isLowVoltage;

extern _Bool isRunTimer;
extern uint  TimerCNT;
//extern Menu_Data_TypeDef Menu_Data;
#endif