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

#define L 3
#define R 1

#define a1 10
#define a2 121.5
#define a3 110.5
#define pi 3.14

uint16_t iteration_time;
int error, integral, derivative, output;
int error_prior1, integral_prior1;
int error_prior2, integral_prior2;
int error_prior3, integral_prior3;
int error_prior4, integral_prior4;
volatile uint16_t pos1_cnt, pos4_cnt;
volatile int32_t pos1, pos2, pos3, pos4;
int v1, v2, v3, v4;
int lin_vel, ang_vel;

int ang[12];
int servo_ang[12];
float x, y, z, z1, z2, z3;
float theta1, theta2, theta3, theta22;

void speed_control(int desire_speed, int actual_speed, uint8_t wheel);
void wheel_robot_control();
void inverse_kin();

#endif /* MAIN_H_ */
