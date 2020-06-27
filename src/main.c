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
#include "main.h"
#include "general.h"
#include "pwm_expander.h"
#include "uart.h"
#include "h_bridge.h"
#include "ADC.h"

int delay = 150;

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

int main(void)
{
	init_pca9685();
	init_uart2();
    //	init_adc();
	init_h_bridge();
	init_hardware_timer_version();
	init_encoder();

	iteration_time = 1000;
	servo_angle[0] = 50;
	servo_angle[1] = 50;
	servo_angle[2] = 50;
	servo_angle[3] = 50;
	TIM1->CNT = 32768;
	TIM2->CNT = 32768;
	pos1 = 32768;
	pos4 = 32768;
	while(1)
	{
//		printf("pos1 %d, pos2 %d, pos3 %d, pos4 %d\n", pos1_cnt, TIM1->CNT, TIM2->CNT, pos4_cnt);
		pos2 = TIM1->CNT;
		pos3 = TIM2->CNT;
		pos1 = pos1_cnt;
		pos4 = pos4_cnt;

//		speed_control(servo_angle[0]-50, pos1-32768, 1); //left forward
//		speed_control(servo_angle[1]-50, pos2-32768, 2); //left back
//		speed_control(servo_angle[2]-50, pos3-32768, 3); //right forward
		speed_control(servo_angle[3]-50, pos4-32768, 4); //right back

		TIM1->CNT = 32768;
		TIM2->CNT = 32768;
		pos1_cnt = 32768;
		pos4_cnt = 32768;

//		TIM_SetCompare1(TIM3, constraint(servo_angle[0]*10, 0, 1000));
//		TIM_SetCompare2(TIM3, constraint(servo_angle[1]*10, 0, 1000));
//		TIM_SetCompare3(TIM3, constraint(servo_angle[2]*10, 0, 1000));
//		TIM_SetCompare4(TIM3, constraint(servo_angle[3]*10, 0, 1000));
//		wheel_brake(2, servo_angle[0], PCA9685_ADDR2);
//		wheel_brake(12, servo_angle[1], PCA9685_ADDR1);
//		wheel_brake(13, servo_angle[2], PCA9685_ADDR1);

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
				printf("forward ");
			}
			else if (desire_speed < 0)
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_11);
				GPIO_ResetBits(GPIOA, GPIO_Pin_12);
				printf("backward ");
			}
			else
				output = 0;

			TIM_SetCompare2(TIM3, constraint(output, 0, 1000));
			error_prior1 = error;
			integral_prior1 = integral;
			printf("output %d, speed %d, goal %d\n", output, actual_speed, desire_speed);
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
				printf("forward ");
			}
			else if (desire_speed < 0)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_8);
				GPIO_ResetBits(GPIOC, GPIO_Pin_6);
				output = -Kp*error + Ki*integral - Kd*derivative + 200;
				printf("backward ");
			}
			else
				output = 0;
			TIM_SetCompare1(TIM3, constraint(output, 0, 1000));
			error_prior2 = error;
			integral_prior2 = integral;
			printf("output %d, speed %d, goal %d\n", output, actual_speed, desire_speed);
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
				printf("forward ");
			}
			else if (desire_speed < 0)
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_14);
				GPIO_ResetBits(GPIOB, GPIO_Pin_15);
				output = -Kp*error + Ki*integral - Kd*derivative + 200;
				printf("backward ");
			}
			else
				output = 0;
			TIM_SetCompare4(TIM3, constraint(output, 0, 1000));
			error_prior3 = error;
			integral_prior3 = integral;
			printf("output %d, speed %d, goal %d\n", output, actual_speed, desire_speed);
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
				printf("forward ");
			}
			else if (desire_speed < 0)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_2);
				GPIO_ResetBits(GPIOC, GPIO_Pin_3);
				printf("backward ");
			}
			else
				output = 0;

			TIM_SetCompare3(TIM3, constraint(output, 0, 1000));
			error_prior4 = error;
			integral_prior4 = integral;
			printf("output %d, speed %d, goal %d\n", output, actual_speed, desire_speed);
			break;

		default:
			break;
	}
}
