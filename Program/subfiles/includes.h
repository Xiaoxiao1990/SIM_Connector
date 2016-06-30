#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#include "stm8s103K.h"					/*Register map*/
#include "stm8s_bitsdefine.h"
#include "time.h"
#include "config.h"
#include "uart.h"

#define Yes 1
#define No  0

#define Set 	1
#define Reset 0

#define RX_BUF_LEN 32

#define Clear Reset

typedef unsigned char uchar;
typedef unsigned int uint;

extern _Bool isRunTimer;
extern uint  TimerCNT;

#endif
