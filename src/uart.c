/*
 * uart.c
 *
 *  Created on: May 9, 2020
 *      Author: yaroslavantonchyk
 */

#include "stm32f10x.h"
#include "uart.h"
#include "pwm_expander.h"
#include "general.h"
#include <stdio.h>

void init_uart2()
{
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;
	NVIC_InitTypeDef nvic;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	//  configure pins for UART
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_2;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);

	USART_StructInit(&uart);
	uart.USART_BaudRate = 115200;
	USART_Init(USART2, &uart);

	USART_Cmd(USART2, ENABLE);

	//  configure interruption for UART
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	nvic.NVIC_IRQChannel = USART2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}

void send_char(char c)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, c);
}

char read_char(void)
{
	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE))
	{
	    return USART_ReceiveData(USART2);
	}
	return 0;
}

int __io_putchar(int c)
{
	if(c == '\n')
		send_char('\r');
	send_char(c);
	return c;
}

void USART2_IRQHandler()
{
	incoming_byte = read_char();

	if ((incoming_byte >= 48) && (incoming_byte <= 57))
	{
		incoming_byte -= 48;
		buff = buff*10 + incoming_byte;
	}
	else if ((incoming_byte >= 97) && (incoming_byte <= 108))
	{
		servo_angle[incoming_byte-97] = constraint(buff, 0, 180);
		printf("Servo%d - %d\n", incoming_byte-97, buff);
		buff = 0;
	}
	else if (incoming_byte == 'm')
	{
		flag = 1;
		printf("Sequence\n");
		buff = 0;
	}
	else
		printf("Incorrect input\n");
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}


