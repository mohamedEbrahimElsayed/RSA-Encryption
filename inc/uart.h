
#ifndef __UART_H_
#define __UART_H_

#include "std_types.h"
#include "REG52.H"
#include <CTYPE.H>

void UART_Init();
void UART_TxChar(const char ch);
const char UART_RxChar();
void UART_sendInt(uint32_t num);
void UART_sendString(const char* str);
uint32_t UART_receiveInt();
void UART_sendHex(uint32_t num);
uint32_t UART_reseiveHex();
#endif
