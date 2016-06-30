#include "includes.h"

/*Global*/
_Bool isTimeProcess;
_Bool isOneSecond;
_Bool isUpdateDisplay;
uchar isSetting;
uchar MenuBar;
uchar CDRAM[4][16];
/*
_Bool isValve;
_Bool isNormal;
_Bool isEmission;
_Bool isCanEmission;
*/
_Bool isRunTimer;
uint  TimerCNT;
uchar RxBuffer[RX_BUF_LEN];
uchar RxPoint;
_Bool isReceiveComplete;
Time_TypeDef Now;
uchar ConnectionState;
//uchar SettingTimeCNT;
_Bool isUpdateData;
_Bool isGetData;
_Bool isInRx;
uchar RxTimer;
uint PulseNumber1;
uint PulseNumber2;
uint FlowMeter;
long Total_V;
long Total_V_last;
long Addition_V;
long Addition_V_last;
long Continue_V;
long Continue_V_Bkp;
Time_TypeDef Emission_T;
Time_TypeDef Emission_T_last;
Time_TypeDef EmissionStart_T;
Time_TypeDef EmissionStart_T_last;
uchar OutputStatus;
_Bool Valve_Status;
_Bool isShowMessage;
uchar MessageNo;
_Bool isLogin;
uchar LoGinPage;
uint TDS;
uint TDS_SET;
//for reverse display
uchar From = 15;
uchar To = 15;
uchar Line = 0;
uint Origin_Password;
uint User_Password;
uint Origin_Password1;
uint User_Password1;
_Bool isLowVoltage;
/*
Menu_Data_TypeDef Menu_Data = {
	&Total_V,
	&Total_V_last,
	&Addition_V,
	&Addition_V_last,
	&Emission_T,
	&Emission_T_last,
	&EmissionStart_T,
	&EmissionStart_T_last,
	&PulseNumber,
	&OutputStatus,
	&TDS,
	&Now
};*/