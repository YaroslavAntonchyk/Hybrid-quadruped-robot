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
#include "pwm_expander.h"
#include <stdio.h>

int main(void)
{
	init_all();
	// printf("hello\n");
	while(1)
	{
//		while(!flag);
//		sequence();
//		flag = 0;
//
//		while(!flag);
//		set_servo_angle(11, 30);
//		set_servo_angle(9, 108);
//		delay_ms(500);
//		flag = 0;
		set_servo_angle(0, servo1, PCA9685_ADDR2);
		set_servo_angle(1, servo2, PCA9685_ADDR2);
		set_servo_angle(2, servo3, PCA9685_ADDR2);
		set_servo_angle(9, servo4, PCA9685_ADDR2);
		set_servo_angle(11, servo5, PCA9685_ADDR2);
		set_servo_angle(10, servo6, PCA9685_ADDR2);

		delay_ms(10);

	}
}
