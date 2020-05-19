/*
 * h_bridge.c
 *
 *  Created on: May 12, 2020
 *      Author: yaroslavantonchyk
 */

#include "stm32f10x.h"
#include "general.h"

void init_h_bridge()
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef tim;
	TIM_OCInitTypeDef  channel;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &gpio);

	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Prescaler = 64000 - 1;
	tim.TIM_Period = 1000 - 1;
	TIM_TimeBaseInit(TIM4, &tim);

	TIM_OCStructInit(&channel);
	channel.TIM_OCMode = TIM_OCMode_PWM1;
	channel.TIM_OutputState = TIM_OutputState_Enable;
	channel.TIM_Pulse = 100;
	TIM_OC1Init(TIM4, &channel);
	channel.TIM_Pulse = 200;
	TIM_OC2Init(TIM4, &channel);
	channel.TIM_Pulse = 500;
	TIM_OC3Init(TIM4, &channel);
	channel.TIM_Pulse = 900;
	TIM_OC4Init(TIM4, &channel);

	TIM_Cmd(TIM4, ENABLE);
}

void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5))
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		else
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
	}
}
