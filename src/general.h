/*
 * general.h
 *
 *  Created on: May 10, 2020
 *      Author: yaroslavantonchyk
 */

#ifndef GENERAL_H_
#define GENERAL_H_

volatile uint32_t timer_ms;

void SysTick_Handler();
void delay_ms(int time);
int constraint(int var, int bottom_lim, int upper_lim);

#endif /* GENERAL_H_ */
