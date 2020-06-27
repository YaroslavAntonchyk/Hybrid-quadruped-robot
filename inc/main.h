/*
 * main.h
 *
 *  Created on: Jun 26, 2020
 *      Author: yaroslavantonchyk
 */

#ifndef MAIN_H_
#define MAIN_H_

#define Kp 80
#define Ki 2
#define Kd 20

uint16_t iteration_time;
int error, integral, derivative, output;
int error_prior1, integral_prior1;
int error_prior2, integral_prior2;
int error_prior3, integral_prior3;
int error_prior4, integral_prior4;
volatile uint16_t pos1_cnt, pos4_cnt;
volatile uint16_t pos1, pos2, pos3, pos4;
int v1, v2, v3, v4;

void speed_control(int desire_speed, int actual_speed, uint8_t wheel);

#endif /* MAIN_H_ */
