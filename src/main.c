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
#include "general.h"
#include "pwm_expander.h"
#include "uart.h"
#include <stdio.h>
int delay = 300;

void sequence_frleg()
{
	set_servo_angle(4, 30);
	set_servo_angle(3, 108);
	delay_ms(delay);

	set_servo_angle(4, 11);
	set_servo_angle(3, 88);
	delay_ms(delay);

	set_servo_angle(4, 0);
	set_servo_angle(3, 142);
	delay_ms(delay);

	set_servo_angle(4, 45);
	set_servo_angle(3, 142);
	delay_ms(delay);

	set_servo_angle(1, 30+SERVO2_OFFSET);
	set_servo_angle(0, 108+SERVO1_OFFSET);
}

void sequence_brleg()
{

	set_servo_angle(1, 30+SERVO2_OFFSET);
	set_servo_angle(0, 108+SERVO1_OFFSET);
	delay_ms(delay);

	set_servo_angle(1, 11+SERVO2_OFFSET);
	set_servo_angle(0, 88+SERVO1_OFFSET);
	delay_ms(delay);

	set_servo_angle(1, 0+SERVO2_OFFSET);
	set_servo_angle(0, 142+SERVO1_OFFSET);
	delay_ms(delay);

	set_servo_angle(1, 45+SERVO2_OFFSET);
	set_servo_angle(0, 142+SERVO1_OFFSET);
	delay_ms(delay);

	set_servo_angle(4, 30);
	set_servo_angle(3, 108);
}

int main(void)
{
	init_pca9685();
	init_uart2();

	set_servo_angle(2, 101+SERVO3_OFFSET);
	set_servo_angle(5, 101);
	delay_ms(500);

	while(1)
	{
		while(!flag);
		sequence_frleg();
		flag = 0;

		while(!flag);
		sequence_brleg();
		flag = 0;


//		set_servo_angle(0, servo1, PCA9685_ADDR1);
//		set_servo_angle(2, servo2, PCA9685_ADDR1);
//		set_servo_angle(1, servo3, PCA9685_ADDR1);
//		set_servo_angle(9, servo4, PCA9685_ADDR1);
//		set_servo_angle(11, servo5, PCA9685_ADDR1);
//		set_servo_angle(10, servo6, PCA9685_ADDR1);
//		set_servo_angle(channel[0], servo_angle[0]);
//		delay_ms(10);

	}
}
