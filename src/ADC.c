/*
 * ADC.c
 *
 *  Created on: May 19, 2020
 *      Author: yaroslavantonchyk
 */


#include "stm32f10x.h"
#include "general.h"
#include <stdio.h>
#include "uart.h"

void init_adc()
{
	ADC_InitTypeDef adc;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	ADC_StructInit(&adc);
	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_NbrOfChannel = 1;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_Init(ADC1, &adc);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_17, 1, ADC_SampleTime_71Cycles5);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1));

	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1));

	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void send_adc_measurement()
{
	uint16_t adc = ADC_GetConversionValue(ADC1);
	printf("Adc = %d (%.3fV)\n", adc, adc * 3.3f / 4096.0f);
}
