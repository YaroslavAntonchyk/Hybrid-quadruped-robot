/*
 * h_bridge.c
 *
 *  Created on: May 12, 2020
 *      Author: yaroslavantonchyk
 */

#include "stm32f10x.h"
#include "general.h"
#include "h_bridge.h"
#include "main.h"

void init_encoder();

void init_h_bridge()
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef tim;
	TIM_OCInitTypeDef channel;


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	// PWM output pin tim2 channel1 and channel2
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio);
	// PWM output pin tim2 channel3 and channel4
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &gpio);
	// Left back motor output
	gpio.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_8;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &gpio);
//	GPIO_SetBits(GPIOC, GPIO_Pin_6);
//	GPIO_ResetBits(GPIOC, GPIO_Pin_8);
	// Left forward motor output
	gpio.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &gpio);
//	GPIO_SetBits(GPIOA, GPIO_Pin_12);
//	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
	// Right back motor output
	gpio.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &gpio);
//	GPIO_SetBits(GPIOC, GPIO_Pin_3);
//	GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	// Right left motor output
	gpio.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &gpio);
//	GPIO_SetBits(GPIOB, GPIO_Pin_15);
//	GPIO_ResetBits(GPIOB, GPIO_Pin_14);

	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Prescaler = 64 - 1;
	tim.TIM_Period = 1000 - 1;
	TIM_TimeBaseInit(TIM3, &tim);

	TIM_OCStructInit(&channel);
	channel.TIM_OCMode = TIM_OCMode_PWM1;
	channel.TIM_OutputState = TIM_OutputState_Enable;
	channel.TIM_Pulse = 0;
	TIM_OC1Init(TIM3, &channel);
	channel.TIM_Pulse = 0;
	TIM_OC2Init(TIM3, &channel);
	channel.TIM_Pulse = 0;
	TIM_OC3Init(TIM3, &channel);
	channel.TIM_Pulse = 0;
	TIM_OC4Init(TIM3, &channel);

	TIM_Cmd(TIM3, ENABLE);
}

void init_encoder()
{
	EXTI_InitTypeDef exti;
	GPIO_InitTypeDef gpio;
	NVIC_InitTypeDef nvic;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	// input
	gpio.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &gpio);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);
	// configure external interrupt
	EXTI_StructInit(&exti);
	exti.EXTI_Line = EXTI_Line10;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
	// enable pin interrupt
	nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
	// configure external interrupt
	EXTI_StructInit(&exti);
	exti.EXTI_Line = EXTI_Line11;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
	// enable pin interrupt
	nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
	// configure external interrupt
	EXTI_StructInit(&exti);
	exti.EXTI_Line = EXTI_Line12;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
	// enable pin interrupt
	nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
	// configure external interrupt
	EXTI_StructInit(&exti);
	exti.EXTI_Line = EXTI_Line13;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
	// enable pin interrupt
	nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}

void EXTI15_10_IRQHandler()
{
	if (EXTI_GetITStatus(EXTI_Line10) || EXTI_GetITStatus(EXTI_Line11))
	{
		pos1_cnt++;
		EXTI_ClearITPendingBit(EXTI_Line10);
		EXTI_ClearITPendingBit(EXTI_Line11);
	}

	if (EXTI_GetITStatus(EXTI_Line12) || EXTI_GetITStatus(EXTI_Line13))
	{
		pos4_cnt++;
		EXTI_ClearITPendingBit(EXTI_Line12);
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
}

void init_hardware_timer_version(void)
{
	GPIO_InitTypeDef gpio;

	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPBEN;

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //AFIO might not even be needed?
	//GPIO must be input floating which is default so no code to write for that

	// value to count up to : 16 bit so max is 0xFFFF = 65535
	TIM2->ARR = 0xFFFF;

	//per datasheet instructions
	TIM2->CCMR1 |= (TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0 );  //step 1 and 2
	TIM2->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);  // step 3 and 4
	TIM2->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;   //step 5
	TIM2->CR1 |= TIM_CR1_CEN ;     //step 6

	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	TIM1->ARR = 0xFFFF;

	gpio.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);

	TIM1->CCMR1 |= (TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0 );  //step 1 and 2
	TIM1->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);  // step 3 and 4
	TIM1->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;   //step 5
	TIM1->CR1 |= TIM_CR1_CEN ;     //step 6
}



