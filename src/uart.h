/*
 * uart.h
 *
 *  Created on: May 9, 2020
 *      Author: yaroslavantonchyk
 */

#ifndef UART_H_
#define UART_H_

volatile uint8_t incoming_byte;
volatile uint16_t buff;

void send_char(char c);
char read_char(void);
int __io_putchar(int c);
void USART2_IRQHandler();
void init_uart2();


#endif /* UART_H_ */
