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

int delay = 150;

int servo_ang[12] = {148, 131, 130,	139, 113, 100, 23, 12, 66, 46, 40, 27};
int ang[12] = {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};


void step1()
{
	set_servo_angle(8, 57);
	set_servo_angle(11, 18);
	set_servo_angle(2, 129);
	set_servo_angle(5, 91);
	delay_ms(delay);

	set_servo_angle(0, 61);
	set_servo_angle(1, 51);
	set_servo_angle(2, 139);
	delay_ms(delay);
	set_servo_angle(0, 52);
	set_servo_angle(1, 17);
	set_servo_angle(2, 139);
	delay_ms(delay);
	set_servo_angle(0, 101);
	set_servo_angle(1, 17);
	set_servo_angle(2, 139);
	delay_ms(delay);
	set_servo_angle(0, 101);
	set_servo_angle(1, 50);
	set_servo_angle(2, 139);
	delay_ms(delay);

	// move body
	set_servo_angle(0, 90);
	set_servo_angle(1, 41);
	set_servo_angle(2, 139);

	set_servo_angle(3, 105);
	set_servo_angle(4, 19);
	set_servo_angle(5, 101);

	set_servo_angle(6, 84);
	set_servo_angle(7, 104);
	set_servo_angle(8, 66);

	set_servo_angle(9, 111);
	set_servo_angle(10, 134);
	set_servo_angle(11, 27);
	delay_ms(delay);
}

void step2()
{
	set_servo_angle(2, 149);
	set_servo_angle(5, 109);
	set_servo_angle(8, 76);
	set_servo_angle(11, 37);
	delay_ms(delay);

	set_servo_angle(9, 111);
	set_servo_angle(10, 134);
	set_servo_angle(11, 27);
	delay_ms(delay);
	set_servo_angle(9, 112);
	set_servo_angle(10, 152);
	set_servo_angle(11, 27);
	delay_ms(delay);
	set_servo_angle(9, 62);
	set_servo_angle(10, 152);
	set_servo_angle(11, 27);
	delay_ms(delay);
	set_servo_angle(9, 62);
	set_servo_angle(10, 123);
	set_servo_angle(11, 27);
	delay_ms(delay);

	// move body
	set_servo_angle(9, 75);
	set_servo_angle(10, 128);
	set_servo_angle(11, 27);

	set_servo_angle(0, 78);
	set_servo_angle(1, 42);
	set_servo_angle(2, 139);

	set_servo_angle(6, 90);
	set_servo_angle(7, 100);
	set_servo_angle(8, 66);

	set_servo_angle(3, 97);
	set_servo_angle(4, 18);
	set_servo_angle(5, 101);
	delay_ms(delay);
}

void step3()
{
	set_servo_angle(2, 149);
	set_servo_angle(5, 109);
	set_servo_angle(8, 76);
	set_servo_angle(11, 37);
	delay_ms(delay);

	set_servo_angle(6, 90);
	set_servo_angle(7, 100);
	set_servo_angle(8, 66);
	delay_ms(delay);
	set_servo_angle(6, 97);
	set_servo_angle(7, 138);
	set_servo_angle(8, 66);
	delay_ms(delay);
	set_servo_angle(6, 59);
	set_servo_angle(7, 138);
	set_servo_angle(8, 66);
	delay_ms(delay);
	set_servo_angle(6, 59);
	set_servo_angle(7, 102);
	set_servo_angle(8, 66);
	delay_ms(delay);

	// move body
	set_servo_angle(6, 68);
	set_servo_angle(7, 111);
	set_servo_angle(8, 66);

	set_servo_angle(9, 90);
	set_servo_angle(10, 134);
	set_servo_angle(11, 27);

	set_servo_angle(0, 69);
	set_servo_angle(1, 48);
	set_servo_angle(2, 139);

	set_servo_angle(3, 89);
	set_servo_angle(4, 19);
	set_servo_angle(5, 101);
	delay_ms(delay);
}

void step4()
{
	set_servo_angle(8, 57);
	set_servo_angle(11, 18);
	set_servo_angle(2, 129);
	set_servo_angle(5, 91);
	delay_ms(delay);

	set_servo_angle(3, 89);
	set_servo_angle(4, 19);
	set_servo_angle(5, 101);
	delay_ms(delay);
	set_servo_angle(3, 88);
	set_servo_angle(4, 1);
	set_servo_angle(5, 101);
	delay_ms(delay);
	set_servo_angle(3, 127);
	set_servo_angle(4, 1);
	set_servo_angle(5, 101);
	delay_ms(delay);
	set_servo_angle(3, 127);
	set_servo_angle(4, 30);
	set_servo_angle(5, 101);
	delay_ms(delay);

	// move body
	set_servo_angle(3, 117);
	set_servo_angle(4, 25);
	set_servo_angle(5, 101);

	set_servo_angle(6, 77);
	set_servo_angle(7, 110);
	set_servo_angle(8, 66);

	set_servo_angle(9, 101);
	set_servo_angle(10, 135);
	set_servo_angle(11, 27);

	set_servo_angle(0, 61);
	set_servo_angle(1, 51);
	set_servo_angle(2, 139);
	delay_ms(delay);

}

void walking()
{
	while(!flag);
	step1();
	flag = 0;
	while(!flag);
	step2();
	flag = 0;
	while(!flag);
	step3();
	flag = 0;
	while(!flag);
	step4();
	flag = 0;
}

void set_servo_rolling()
{
	set_servo_angle(0, 60);
	set_servo_angle(1, 15);
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


int main(void)
{
	init_pca9685();
	init_uart2();
    //	init_adc();
	init_h_bridge();
	init_hardware_timer_version();
	init_encoder();

	servo_angle[0] = 50;
	servo_angle[1] = 50;
	servo_angle[2] = 0;
//	servo_angle[3] = 50;
	TIM1->CNT = 32768;
	TIM2->CNT = 32768;
	pos1_cnt = 32768;
	pos4_cnt = 32768;

	set_servo_angle(6, 20);
	set_servo_angle(7, 12);
	set_servo_angle(8, 66);
	while(1)
	{
		inverse_kin();
//		set_servo_rolling();
//		wheel_robot_control();

//		walking();
//		set_servo_angle(0, servo_angle[0]);
//		set_servo_angle(1, servo_angle[1]);
//		set_servo_angle(2, servo_angle[2]);
//		set_servo_angle(3, servo_angle[3]);
//		set_servo_angle(4, servo_angle[4]);
//		set_servo_angle(5, servo_angle[5]);
//		set_servo_angle(6, servo_angle[6]);
//		set_servo_angle(7, servo_angle[7]);
//		set_servo_angle(8, servo_angle[8]);
//		set_servo_angle(9, servo_angle[9]);
//		set_servo_angle(10, servo_angle[10]);
//		set_servo_angle(11, servo_angle[11]);
		delay_ms(20);

	}


}

void inverse_kin()
{
	x = constraint(servo_angle[0]-70, -70, 50);
	y = constraint(servo_angle[1]-50, -50, 50);
	z = constraint(servo_angle[2]+100, 130, 235);

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
	// left back leg
	servo_ang[6] = 23 + 0.858974359*theta2;
	servo_ang[7] = 12 + 1.037037037*theta3; // 180-servo_angle[1]
	servo_ang[8] = 66 + 1.02962963*theta1; // servo_angle[2] +-
	set_servo_angle(6, (uint8_t)constraint(servo_ang[6], 5, 100));
	set_servo_angle(7, (uint8_t)constraint(servo_ang[7], 0, 120));
	set_servo_angle(8, (uint8_t)constraint(servo_ang[8], 46, 86));
	// left forward leg
	servo_ang[9] = 47 + 1.115384615*theta2;
	servo_ang[10] = 40 + 0.914814815*theta3; // 180-servo_angle[1]
	servo_ang[11] = 27 + 1.049074074*theta1; // servo_angle[2] +-
	set_servo_angle(9, (uint8_t)constraint(servo_ang[9], 23, 147));
	set_servo_angle(10, (uint8_t)constraint(servo_ang[10], 30, 136));
	set_servo_angle(11, (uint8_t)constraint(servo_ang[11], 7, 47));

	// right back leg
	servo_ang[0] = 148 - 1.115384615*theta2;
	servo_ang[1] = 131 - 0.940740741*theta3; // 180-servo_angle[1]
	servo_ang[2] = 130 + 1.074074074*theta1; // servo_angle[2] +-
	set_servo_angle(0, (uint8_t)constraint(servo_ang[0], 60, 165));
	set_servo_angle(1, (uint8_t)constraint(servo_ang[1], 33, 142));
	set_servo_angle(2, (uint8_t)constraint(servo_ang[2], 110, 150));

	// right forward leg
	servo_ang[3] = 140 - 0.884615385*theta2;
	servo_ang[4] = 113 - 0.918518519*theta3; // 180-servo_angle[1]
	servo_ang[5] = 101 + 0.959259259*theta1; // servo_angle[2] +-
	set_servo_angle(3, (uint8_t)constraint(servo_ang[3], 70, 150));
	set_servo_angle(4, (uint8_t)constraint(servo_ang[4], 17, 124));
	set_servo_angle(5, (uint8_t)constraint(servo_ang[5], 81, 121));
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
