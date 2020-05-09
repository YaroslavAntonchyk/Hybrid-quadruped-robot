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
#include "uart.h"
#include <stdio.h>

void sequence_frleg()
{
	int delay = 300;

	set_servo_angle(SERVO5_CHANNEL, 30, PCA9685_ADDR1);
	set_servo_angle(SERVO4_CHANNEL, 108, PCA9685_ADDR1);
	delay_ms(delay);

	set_servo_angle(SERVO5_CHANNEL, 11, PCA9685_ADDR1);
	set_servo_angle(SERVO4_CHANNEL, 88, PCA9685_ADDR1);
	delay_ms(delay);

	set_servo_angle(SERVO5_CHANNEL, 0, PCA9685_ADDR1);
	set_servo_angle(SERVO4_CHANNEL, 142, PCA9685_ADDR1);
	delay_ms(delay);

	set_servo_angle(SERVO5_CHANNEL, 45, PCA9685_ADDR1);
	set_servo_angle(SERVO4_CHANNEL, 142, PCA9685_ADDR1);
	delay_ms(delay);

	set_servo_angle(SERVO2_CHANNEL, 30+SERVO2_OFFSET, PCA9685_ADDR1);
	set_servo_angle(SERVO1_CHANNEL, 108+SERVO1_OFFSET, PCA9685_ADDR1);


}

void sequence_brleg()
{
	int delay = 300;

	set_servo_angle(SERVO2_CHANNEL, 30+SERVO2_OFFSET, PCA9685_ADDR1);
	set_servo_angle(SERVO1_CHANNEL, 108+SERVO1_OFFSET, PCA9685_ADDR1);
	delay_ms(delay);

	set_servo_angle(SERVO2_CHANNEL, 11+SERVO2_OFFSET, PCA9685_ADDR1);
	set_servo_angle(SERVO1_CHANNEL, 88+SERVO1_OFFSET, PCA9685_ADDR1);
	delay_ms(delay);

	set_servo_angle(SERVO2_CHANNEL, 0+SERVO2_OFFSET, PCA9685_ADDR1);
	set_servo_angle(SERVO1_CHANNEL, 142+SERVO1_OFFSET, PCA9685_ADDR1);
	delay_ms(delay);

	set_servo_angle(SERVO2_CHANNEL, 45+SERVO2_OFFSET, PCA9685_ADDR1);
	set_servo_angle(SERVO1_CHANNEL, 142+SERVO1_OFFSET, PCA9685_ADDR1);
	delay_ms(delay);

	set_servo_angle(SERVO5_CHANNEL, 30, PCA9685_ADDR1);
	set_servo_angle(SERVO4_CHANNEL, 108, PCA9685_ADDR1);


}

int main(void)
{
	init_pca9685();
	init_uart2();

	servo1 = 90;
	servo2 = 90;
	servo3 = 90;
	servo4 = 90;
	servo5 = 90;
	servo6 = 90;

	set_servo_angle(SERVO3_CHANNEL, 101+SERVO3_OFFSET, PCA9685_ADDR1);
	set_servo_angle(SERVO6_CHANNEL, 101, PCA9685_ADDR1);
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

		delay_ms(10);

	}
}
