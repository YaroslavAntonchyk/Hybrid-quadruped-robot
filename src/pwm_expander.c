/*
 * pwm_expander.c
 *
 *  Created on: May 9, 2020
 *      Author: yaroslavantonchyk
 */

#include "stm32f10x.h"
#include "stdio.h"
#include "pwm_expander.h"
#include "general.h"

void i2c_set_addr(uint32_t addr, uint8_t device_addr)
{
	I2C_GenerateSTART(I2C1, ENABLE);
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	I2C_Send7bitAddress(I2C1, device_addr, I2C_Direction_Transmitter);
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);

	I2C_SendData(I2C1, addr);
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
}

void i2c_write(uint32_t addr, const void* data, int size, uint8_t device_addr)
{
	int i;
	const uint8_t* buffer = (uint8_t*)data;

	i2c_set_addr(addr, device_addr);
	for (i = 0; i < size; i++)
	{
		I2C_SendData(I2C1, buffer[i]);
		while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	}
	I2C_GenerateSTOP(I2C1, ENABLE);
}

void pca9685_config(uint8_t device_addr)
{
	uint8_t config = 0b00110001;  //enable auto increment, low power mode, all call
	uint8_t PWM_freq = 124;  //25MHz/(4096*freq)-1 124 - perfect
	i2c_write(0, &config, sizeof(config), device_addr);
	i2c_write(254, &PWM_freq, sizeof(PWM_freq), device_addr);
	config = 0b00100001;  //set normal mode
	i2c_write(0, &config, sizeof(config), device_addr);
}

void set_servo_angle(uint8_t channel, uint8_t angle, uint8_t device_addr)
{
	uint8_t addr = 6 + 4*channel;
	uint16_t pwm_duty = 0;
	uint8_t time_off[4] = {0, 0, 0, 0};
	constraint(angle, 0, 180);
	pwm_duty = 110 + 2.116*angle;
	time_off[2] = (unsigned)pwm_duty & 0xff;
	time_off[3] = (unsigned)pwm_duty >> 8;
	i2c_write(addr, time_off, 4, device_addr);
}





void init_pca9685()
{
	GPIO_InitTypeDef gpio;
	I2C_InitTypeDef i2c;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);


	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; // SCL, SDA
	gpio.GPIO_Mode = GPIO_Mode_AF_OD;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);

	I2C_StructInit(&i2c);
	i2c.I2C_Mode = I2C_Mode_I2C;
	i2c.I2C_ClockSpeed = 100000;
	I2C_Init(I2C1, &i2c);
	I2C_Cmd(I2C1, ENABLE);
	// configure timer interrupt frequency, SystemCoreClock is a CPU frequency
	SysTick_Config(SystemCoreClock/1000);

	pca9685_config(PCA9685_ADDR1);
	// pca9685_config(PCA9685_ADDR2);
}
