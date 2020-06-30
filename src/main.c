/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "main.h"
#include "general.h"
#include "pwm_expander.h"
#include "uart.h"
#include "h_bridge.h"
#include "ADC.h"

int servo_ang[12] = {148, 131, 130,	139, 113, 100, 23, 12, 66, 46, 40, 27};
int ang[12] = {0, 0, 0,	0, 0, 0, 0,	0, 0, 0, 0,	0};
int sequence[3][7] = {
		{-60, -50, -10, 0, -15, -30, -45},
		{0, 0, 0, 0, 0, 0, 0},
		{180, 140, 140, 180, 180, 180, 180,}
};
int sequence_side[3][7] = {
		{-30, -30, -30, -30, -30, -30, -30},
		{-30, -20, 20, 30, 15, 0, -15},
		{180, 140, 140, 180, 180, 180, 180,}
};
int sequence_reverse[3][7] = {
		{0, -10, -50, -60, -45, -30, -15},
		{0, 0, 0, 0, 0, 0, 0},
		{180, 140, 140, 180, 180, 180, 180,}
};

//void spot_rotation() //TODO change sequences
//{
//	while(!flag);
//	printf("1\n");
//	for(int i = 0; i < 4; i++)
//	{
//		inverse_kin(sequence[0][i], sequence[1][i], sequence[2][i], 1);
//		delay_ms(100);
//	}
//	inverse_kin(sequence[0][4], 0, sequence[2][4], 1);
//	inverse_kin(sequence[0][0], 20, sequence[2][0], 2);
//	inverse_kin(sequence[0][6], 20, sequence[2][6], 3);
//	inverse_kin(sequence[0][5], 0, sequence[2][5], 4);
//	flag = 0;
//	delay_ms(100);
//
//	while(!flag);
//	printf("2\n");
//	for(int i = 0; i < 4; i++)
//	{
//		inverse_kin(sequence[0][i], sequence[1][i], sequence[2][i], 2);
//		delay_ms(100);
//	}
//	inverse_kin(sequence[0][5], 0, sequence[2][5]+10, 1);
//	inverse_kin(sequence[0][4], 20, sequence[2][4]+10, 2);
//	inverse_kin(sequence[0][0], 20, sequence[2][0], 3);
//	inverse_kin(sequence[0][6], 0, sequence[2][6], 4);
//	flag = 0;
//	delay_ms(100);
//
//	while(!flag);
//	printf("3\n");
//	for(int i = 0; i < 4; i++)
//	{
//		inverse_kin(sequence[0][i], sequence[1][i], sequence[2][i], 3);
//		delay_ms(100);
//	}
//	inverse_kin(sequence[0][6], 0, sequence[2][6]+10, 1);
//	inverse_kin(sequence[0][5], 20, sequence[2][5]+10, 2);
//	inverse_kin(sequence[0][4], 20, 170, 3);
//	inverse_kin(sequence[0][0], 0, sequence[2][0], 4);
//	flag = 0;
//	delay_ms(100);
//
//	while(!flag);
//	printf("4\n");
//	for(int i = 0; i < 4; i++)
//	{
//		inverse_kin(sequence[0][i], sequence[1][i], sequence[2][i], 4);
//		delay_ms(100);
//	}
//	inverse_kin(sequence[0][0], 0, sequence[2][0], 1);
//	inverse_kin(sequence[0][6], 20, sequence[2][6], 2);
//	inverse_kin(sequence[0][5], 20, sequence[2][5], 3);
//	inverse_kin(sequence[0][4], 0, sequence[2][4], 4);
//	flag = 0;
//	delay_ms(100);
//}


int main(void)
{
	init_pca9685();
	init_uart2();
    //	init_adc();
	init_h_bridge();
	init_hardware_timer_version();
	init_encoder();

	TIM1->CNT = 32768;
	TIM2->CNT = 32768;
	pos1_cnt = 32768;
	pos4_cnt = 32768;

	iteration_time = 20;
	servo_angle[0] = 50;
	servo_angle[1] = 50;
	set_servo_rolling();
	while(1)
	{
//		side_walk();
//		walk_straightforward();
		set_servo_rolling();
		wheel_robot_control();

		servo_test();
		delay_ms(iteration_time);

	}
}

void servo_test()
{
	set_servo_angle(0, servo_angle[0]);
	set_servo_angle(1, servo_angle[1]);
	set_servo_angle(2, servo_angle[2]);
	set_servo_angle(3, servo_angle[3]);
	set_servo_angle(4, servo_angle[4]);
	set_servo_angle(5, servo_angle[5]);
	set_servo_angle(6, servo_angle[6]);
	set_servo_angle(7, servo_angle[7]);
	set_servo_angle(8, servo_angle[8]);
	set_servo_angle(9, servo_angle[9]);
	set_servo_angle(10, servo_angle[10]);
	set_servo_angle(11, servo_angle[11]);
	delay_ms(iteration_time);
}

void walk_straightforward()
{
	while(!flag);
	printf("1\n");
	for(int i = 0; i < 4; i++)
	{
		inverse_kin(sequence[0][i], sequence[1][i], sequence[2][i], 1);
		delay_ms(100);
	}
	inverse_kin(sequence[0][4], 0, sequence[2][4], 1);
	inverse_kin(sequence[0][0], 20, sequence[2][0], 2);
	inverse_kin(sequence[0][6], 20, sequence[2][6], 3);
	inverse_kin(sequence[0][5], 0, sequence[2][5], 4);
	flag = 0;
	delay_ms(100);

	while(!flag);
	printf("2\n");
	for(int i = 0; i < 4; i++)
	{
		inverse_kin(sequence[0][i], sequence[1][i], sequence[2][i], 2);
		delay_ms(100);
	}
	inverse_kin(sequence[0][5], 0, sequence[2][5]+10, 1);
	inverse_kin(sequence[0][4], 20, sequence[2][4]+10, 2);
	inverse_kin(sequence[0][0], 20, sequence[2][0], 3);
	inverse_kin(sequence[0][6], 0, sequence[2][6], 4);
	flag = 0;
	delay_ms(100);

	while(!flag);
	printf("3\n");
	for(int i = 0; i < 4; i++)
	{
		inverse_kin(sequence[0][i], sequence[1][i], sequence[2][i], 3);
		delay_ms(100);
	}
	inverse_kin(sequence[0][6], 0, sequence[2][6]+10, 1);
	inverse_kin(sequence[0][5], 20, sequence[2][5]+10, 2);
	inverse_kin(sequence[0][4], 20, 170, 3);
	inverse_kin(sequence[0][0], 0, sequence[2][0], 4);
	flag = 0;
	delay_ms(100);

	while(!flag);
	printf("4\n");
	for(int i = 0; i < 4; i++)
	{
		inverse_kin(sequence[0][i], sequence[1][i], sequence[2][i], 4);
		delay_ms(100);
	}
	inverse_kin(sequence[0][0], 0, sequence[2][0], 1);
	inverse_kin(sequence[0][6], 20, sequence[2][6], 2);
	inverse_kin(sequence[0][5], 20, sequence[2][5], 3);
	inverse_kin(sequence[0][4], 0, sequence[2][4], 4);
	flag = 0;
	delay_ms(100);
}

void side_walk()
{
	while(!flag);
	printf("1\n");
	for(int i = 0; i < 4; i++)
	{
		inverse_kin(sequence_side[0][i], sequence_side[1][i], sequence_side[2][i], 1);
		delay_ms(100);
	}
	inverse_kin(sequence_side[0][4], sequence_side[1][4], sequence_side[2][4], 1);
	inverse_kin(sequence_side[0][0], sequence_side[1][0]+10, sequence_side[2][0], 2);
	inverse_kin(sequence_side[0][6], sequence_side[1][6]+10, sequence_side[2][6], 3);
	inverse_kin(sequence_side[0][5], sequence_side[1][5], sequence_side[2][5], 4);
	flag = 0;
	delay_ms(100);

	while(!flag);
	printf("2\n");
	for(int i = 0; i < 4; i++)
	{
		inverse_kin(sequence_side[0][i], sequence_side[1][i], sequence_side[2][i], 2);
		delay_ms(100);
	}
	inverse_kin(sequence_side[0][5], sequence_side[1][5], sequence_side[2][5]+10, 1);
	inverse_kin(sequence_side[0][4], sequence_side[1][4]+10, sequence_side[2][4]+10, 2);
	inverse_kin(sequence_side[0][0], sequence_side[1][0]+10, sequence_side[2][0], 3);
	inverse_kin(sequence_side[0][6], sequence_side[1][6], sequence_side[2][6], 4);
	flag = 0;
	delay_ms(100);

	while(!flag);
	printf("3\n");
	for(int i = 0; i < 4; i++)
	{
		inverse_kin(sequence_side[0][i], sequence_side[1][i], sequence_side[2][i], 3);
		delay_ms(100);
	}
	inverse_kin(sequence_side[0][6], sequence_side[1][6], sequence_side[2][6]+10, 1);
	inverse_kin(sequence_side[0][5], sequence_side[1][5]+10, sequence_side[2][5]+10, 2);
	inverse_kin(sequence_side[0][4], sequence_side[1][4]+10, 170, 3);
	inverse_kin(sequence_side[0][0], sequence_side[1][0], sequence_side[2][0], 4);
	flag = 0;
	delay_ms(100);

	while(!flag);
	printf("4\n");
	for(int i = 0; i < 4; i++)
	{
		inverse_kin(sequence_side[0][i], sequence_side[1][i], sequence_side[2][i], 4);
		delay_ms(100);
	}
	inverse_kin(sequence_side[0][0], sequence_side[1][0], sequence_side[2][0], 1);
	inverse_kin(sequence_side[0][6], sequence_side[1][6]+10, sequence_side[2][6], 2);
	inverse_kin(sequence_side[0][5], sequence_side[1][5]+10, sequence_side[2][5], 3);
	inverse_kin(sequence_side[0][4], sequence_side[1][4], sequence_side[2][4], 4);
	flag = 0;
	delay_ms(100);
}

void inverse_kin(int x, int y, int z, uint8_t leg)
{
	x = constraint(x, -70, 50);
	y = constraint(y, -50, 50);
	z = constraint(z, 130, 235);

	z1 = z;
	theta1 = atan2(y, z1);
	z2 = (z1 - a1)/cos(theta1);
	theta22 = atan2(x, z2);
	z3 = (z2)/cos(theta22);
	theta3 = acos((pow(a2, 2) + pow(a3, 2) - pow(z3, 2))/(2*a2*a3));
	theta2 = acos((pow(a2, 2) + pow(z3, 2) - pow(a3, 2))/(2*a2*z3)) - theta22;

	theta1 = theta1 * (180/pi);
	theta2 = theta2 * (180/pi);
	theta3 = (pi - theta3) * (180/pi);
	printf("a %d, b %d, c %d\n", (int)theta2, (int)theta3, (int)theta1);

	switch(leg)
	{
		case 1:
			// right forward leg
			servo_ang[3] = 140 - 0.884615385*theta2;
			servo_ang[4] = 113 - 0.918518519*theta3;
			servo_ang[5] = 101 + 0.959259259*theta1; // servo_angle[2] +-
			set_servo_angle(3, (uint8_t)constraint(servo_ang[3], 70, 150));
			set_servo_angle(4, (uint8_t)constraint(servo_ang[4], 17, 124));
			set_servo_angle(5, (uint8_t)constraint(servo_ang[5], 81, 121));
			break;

		case 2:
			// left back leg
			servo_ang[6] = 23 + 0.858974359*theta2;
			servo_ang[7] = 12 + 1.037037037*theta3;
			servo_ang[8] = 66 + 1.02962963*theta1; // servo_angle[2] +-
			set_servo_angle(6, (uint8_t)constraint(servo_ang[6], 5, 100));
			set_servo_angle(7, (uint8_t)constraint(servo_ang[7], 0, 120));
			set_servo_angle(8, (uint8_t)constraint(servo_ang[8], 46, 86));
			break;

		case 3:
			// left forward leg
			servo_ang[9] = 47 + 1.115384615*theta2;
			servo_ang[10] = 40 + 0.914814815*theta3;
			servo_ang[11] = 27 + 1.049074074*theta1; // servo_angle[2] +-
			set_servo_angle(9, (uint8_t)constraint(servo_ang[9], 23, 147));
			set_servo_angle(10, (uint8_t)constraint(servo_ang[10], 30, 136));
			set_servo_angle(11, (uint8_t)constraint(servo_ang[11], 7, 47));
			break;
		case 4:
			// right back leg
			servo_ang[0] = 148 - 1.115384615*theta2;
			servo_ang[1] = 113 - 0.966666667*theta3;
			servo_ang[2] = 130 + 1.074074074*theta1; // servo_angle[2] +-
			set_servo_angle(0, (uint8_t)constraint(servo_ang[0], 60, 165));
			set_servo_angle(1, (uint8_t)constraint(servo_ang[1], 0, 124));
			set_servo_angle(2, (uint8_t)constraint(servo_ang[2], 110, 150));
			break;

		default:
			break;
	}
}

void set_servo_rolling()
{
	set_servo_angle(0, 60);
	set_servo_angle(1, 0);
	set_servo_angle(2, 130);
	set_servo_angle(3, 70);
	set_servo_angle(4, 0);
	set_servo_angle(5, 101);
	set_servo_angle(6, 91);
	set_servo_angle(7, 140);
	set_servo_angle(8, 66);
	set_servo_angle(9, 135);
	set_servo_angle(10, 153);
	set_servo_angle(11, 27);
}

void wheel_robot_control()
{
//	printf("pos1 %d, pos2 %d, pos3 %d, pos4 %d\n", pos1_cnt, TIM1->CNT, TIM2->CNT, pos4_cnt);
	pos2 = TIM1->CNT - 32768;
	pos3 = TIM2->CNT - 32768;
	pos1 = pos1_cnt - 32768;
	pos4 = pos4_cnt - 32768;

	TIM1->CNT = 32768;
	TIM2->CNT = 32768;
	pos1_cnt = 32768;
	pos4_cnt = 32768;

	lin_vel = servo_angle[0] - 50;
	ang_vel = servo_angle[1] - 50;
	v1 = (2*lin_vel + ang_vel*L)/(2*R);
	v2 = v1;
	v3 = (2*lin_vel - ang_vel*L)/(2*R);
	v4 = v3;
	printf("left_vel %d, right_vel %d\n", v1, v3);
	speed_control(v1, pos1, 1); //left forward
	speed_control(v2, pos2, 2); //left back
	speed_control(v3, pos3, 3); //right forward
	speed_control(v4, pos4, 4); //right back
}

void speed_control(int desire_speed, int actual_speed, uint8_t wheel)
{
	switch(wheel)
	{
		case 1:
			error = abs(desire_speed) - actual_speed;
			integral = constraint(integral_prior1 + error, -100, 100);
			derivative = (error - error_prior1);
			output = Kp*error + Ki*integral - Kd*derivative + 200;
			if (desire_speed > 0)
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_12);
				GPIO_ResetBits(GPIOA, GPIO_Pin_11);
				//printf("forward ");
			}
			else if (desire_speed < 0)
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_11);
				GPIO_ResetBits(GPIOA, GPIO_Pin_12);
				//printf("backward ");
			}
			else
				output = 0;

			TIM_SetCompare2(TIM3, constraint(output, 0, 1000));
			error_prior1 = error;
			integral_prior1 = integral;
			//printf("output %d, speed %d, goal %d\n", output, actual_speed, desire_speed);
			break;

		case 2:
			error = desire_speed - actual_speed;
			integral = constraint(integral_prior2 + error, -100, 100);
			derivative = (error - error_prior2);
			if (desire_speed > 0)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_6);
				GPIO_ResetBits(GPIOC, GPIO_Pin_8);
				output = Kp*error + Ki*integral - Kd*derivative + 200;
				//printf("forward ");
			}
			else if (desire_speed < 0)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_8);
				GPIO_ResetBits(GPIOC, GPIO_Pin_6);
				output = -Kp*error + Ki*integral - Kd*derivative + 200;
				//printf("backward ");
			}
			else
				output = 0;
			TIM_SetCompare1(TIM3, constraint(output, 0, 1000));
			error_prior2 = error;
			integral_prior2 = integral;
			//printf("output %d, speed %d, goal %d\n", output, actual_speed, desire_speed);
			break;

		case 3:
			error = desire_speed - actual_speed;
			integral = constraint(integral_prior3 + error, -100, 100);
			derivative = (error - error_prior3);
			if (desire_speed > 0)
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_15);
				GPIO_ResetBits(GPIOB, GPIO_Pin_14);
				output = Kp*error + Ki*integral - Kd*derivative + 200;
				//printf("forward ");
			}
			else if (desire_speed < 0)
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_14);
				GPIO_ResetBits(GPIOB, GPIO_Pin_15);
				output = -Kp*error + Ki*integral - Kd*derivative + 200;
				//printf("backward ");
			}
			else
				output = 0;
			TIM_SetCompare4(TIM3, constraint(output, 0, 1000));
			error_prior3 = error;
			integral_prior3 = integral;
			//printf("output %d, speed %d, goal %d\n", output, actual_speed, desire_speed);
			break;

		case 4:
			error = abs(desire_speed) - actual_speed;
			integral = constraint(integral_prior4 + error, -100, 100);
			derivative = (error - error_prior4);
			output = Kp*error + Ki*integral - Kd*derivative + 200;
			if (desire_speed > 0)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_3);
				GPIO_ResetBits(GPIOC, GPIO_Pin_2);
				//printf("forward ");
			}
			else if (desire_speed < 0)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_2);
				GPIO_ResetBits(GPIOC, GPIO_Pin_3);
				//printf("backward ");
			}
			else
				output = 0;

			TIM_SetCompare3(TIM3, constraint(output, 0, 1000));
			error_prior4 = error;
			integral_prior4 = integral;
			//printf("output %d, speed %d, goal %d\n", output, actual_speed, desire_speed);
			break;

		default:
			break;
	}
}
