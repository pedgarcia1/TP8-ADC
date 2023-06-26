/*
 * uart.h
 *
 *  Created on: May 30, 2018
 *      Author: jacoby
 */

#ifndef UART_H_
#define UART_H_

void uartInit(void);
void putChar(char c);
int getTXStatus(void);
char getChar(void);
int getRXStatus(void);

#endif /* UART_H_ */
