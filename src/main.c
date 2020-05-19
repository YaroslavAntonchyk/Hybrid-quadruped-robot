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
#include "h_bridge.h"
#include <stdio.h>
int delay = 150;


void diag1()
{
	// step 1
	// rb
	set_servo_angle(0, 108);
	set_servo_angle(1, 46);
	set_servo_angle(2, 139);
	// lf
	set_servo_angle(9, 87);
	set_servo_angle(10, 123);
	set_servo_angle(11, 27);
	// step 2
	delay_ms(delay);
	// rb
	set_servo_angle(0, 83);
	set_servo_angle(1, 27);
	set_servo_angle(2, 139);
	// lf
	set_servo_angle(9, 112);
	set_servo_angle(10, 142);
	set_servo_angle(11, 27);
	// step 3
	delay_ms(delay);
	// rb
	set_servo_angle(0, 151);
	set_servo_angle(1, 15);
	set_servo_angle(2, 139);
	// lf
	set_servo_angle(9, 44);
	set_servo_angle(10, 153);
	set_servo_angle(11, 27);
	// step 4
	delay_ms(delay);
	// rb
	set_servo_angle(0, 151);
	set_servo_angle(1, 61);
	set_servo_angle(2, 139);
	// lf
	set_servo_angle(9, 44);
	set_servo_angle(10, 108);
	set_servo_angle(11, 27);

	// step 1
	// rf
	set_servo_angle(3, 108);
	set_servo_angle(4, 30);
	set_servo_angle(5, 101);
	// lb
	set_servo_angle(6, 54);
	set_servo_angle(7, 43);
	set_servo_angle(8, 66);
}

void diag2()
{

	// step 1
	// rf
	set_servo_angle(3, 108);
	set_servo_angle(4, 30);
	set_servo_angle(5, 101);
	// lb
	set_servo_angle(6, 54);
	set_servo_angle(7, 43);
	set_servo_angle(8, 66);
	// step 2
	delay_ms(delay);
	// rf
	set_servo_angle(3, 88);
	set_servo_angle(4, 11);
	set_servo_angle(5, 101);
	// lb
	set_servo_angle(6, 73);
	set_servo_angle(7, 24);
	set_servo_angle(8, 66);
	// step 3
	delay_ms(delay);
	// rf
	set_servo_angle(3, 142);
	set_servo_angle(4, 0);
	set_servo_angle(5, 101);
	// lb
	set_servo_angle(6, 21);
	set_servo_angle(7, 14);
	set_servo_angle(8, 66);
	// step 4
	delay_ms(delay);
	// rf
	set_servo_angle(3, 142);
	set_servo_angle(4, 45);
	set_servo_angle(5, 101);
	// lb
	set_servo_angle(6, 21);
	set_servo_angle(7, 57);
	set_servo_angle(8, 66);
	// step 1
	// rb
	set_servo_angle(0, 108);
	set_servo_angle(1, 46);
	set_servo_angle(2, 139);
	// lf
	set_servo_angle(9, 87);
	set_servo_angle(10, 123);
	set_servo_angle(11, 27);
}

void step1()
{
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

int main(void)
{
	init_pca9685();
	init_uart2();
	// init_h_bridge();

	while(1)
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
		delay_ms(10);

	}
}
