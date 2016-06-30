#ifndef _UART_H_
#define _UART_H_

extern void _uartInit(void);
extern void _sendStrings(unsigned char *data);
extern void _messageProcess(void);

#endif