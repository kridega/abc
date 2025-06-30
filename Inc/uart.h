/*
 * uart.h
 *
 *  Created on: Jun 26, 2025
 *      Author: singh
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

char inputBuffer[64] = "";  // Buffer size of 64 chars, adjust as needed

void UART2_Init(uint32_t baud); //115200
void UART2_SendChar(char c);
void UART2_SendString(const char* str);



#endif /* UART_H_ */
