/*
 * general.c
 *
 *  Created on: May 10, 2020
 *      Author: yaroslavantonchyk
 */

#include "stm32f10x.h"
#include "general.h"

int constraint(int var, int bottom_lim, int upper_lim)
{
	if(var > upper_lim)
		return upper_lim;
	else if(var < bottom_lim)
		return bottom_lim;
	else
		return var;
}

void SysTick_Handler()
{
	if (timer_ms)
	{
		timer_ms--;
	}
}

void delay_ms(int time)
{
	timer_ms = time;
	while(timer_ms > 0);
}

