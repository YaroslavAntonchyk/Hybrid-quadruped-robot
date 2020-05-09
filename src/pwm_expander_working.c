/*
 * pwm_expander_working.c
 *
 *  Created on: May 9, 2020
 *      Author: yaroslavantonchyk
 */


/*
 * I2C_pwm_expander.c
 *
 *  Created on: Apr 30, 2020
 *      Author: yaroslavantonchyk
 */


#include "stm32f10x.h"
#include "stdio.h"
#define PCA9685_ADDR 0x82
#define SERVO1_TERM 'a'
#define SERVO2_TERM 'b'
#define SERVO3_TERM 'c'
#define SERVO4_TERM 'd'
#define SERVO5_TERM 'e'
#define SERVO6_TERM 'f'

volatile uint32_t timer_ms = 0;
volatile uint8_t incoming_byte = 0;
volatile uint16_t buff = 0;
volatile uint8_t servo1 = 90;
volatile uint8_t servo2 = 90;
volatile uint8_t servo3 = 90;
volatile uint8_t servo4 = 90;
volatile uint8_t servo5 = 90;
volatile uint8_t servo6 = 90;
volatile uint8_t flag = 0;

void i2c_set_addr(uint32_t addr)
{
	I2C_GenerateSTART(I2C1, ENABLE);
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	I2C_Send7bitAddress(I2C1, PCA9685_ADDR, I2C_Direction_Transmitter);
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);

	I2C_SendData(I2C1, addr);
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
}

void i2c_write(uint32_t addr, const void* data, int size)
{
	int i;
	const uint8_t* buffer = (uint8_t*)data;

	i2c_set_addr(addr);
	for (i = 0; i < size; i++)
	{
		I2C_SendData(I2C1, buffer[i]);
		while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
	}
	I2C_GenerateSTOP(I2C1, ENABLE);
}


void pca9685_config(void)
{
	uint8_t config = 0b00110001;  //enable auto increment, low power mode, all call
	uint8_t PWM_freq = 124;  //25MHz/(4096*freq)-1 124 - perfect
	i2c_write(0, &config, sizeof(config));
	i2c_write(254, &PWM_freq, sizeof(PWM_freq));
	config = 0b00100001;  //set normal mode
	i2c_write(0, &config, sizeof(config));
}

void set_servo_angle(uint8_t channel, uint8_t angle)
{
	uint8_t addr = 6 + 4*channel;
	uint16_t pwm_duty = 0;
	uint8_t time_off[4] = {0, 0, 0, 0};
	if(angle > 180) angle = 180;
	else if(angle < 0) angle = 0;
	pwm_duty = 110 + 2.116*angle;
	time_off[2] = (unsigned)pwm_duty & 0xff;
	time_off[3] = (unsigned)pwm_duty >> 8;
	i2c_write(addr, time_off, 4);
}

void SysTick_Handler()
{
	if (timer_ms)
	{
		timer_ms--;
	}
}

void delay_ms(int time)
{
	timer_ms = time;
	while(timer_ms > 0){};
}

void send_char(char c)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, c);
}


char read_char(void)
{
	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE))
	{
	    return USART_ReceiveData(USART2);
	}
	return 0;
}

int __io_putchar(int c)
{
	if(c == '\n')
		send_char('\r');
	send_char(c);
	return c;
}

int constraint(int var, int bottom_lim, int upper_lim)
{
	if(var > upper_lim)
		return upper_lim;
	else if(var < bottom_lim)
		return bottom_lim;
	else
		return var;
}

void USART2_IRQHandler()
{
	incoming_byte = read_char();
	if ((incoming_byte >= 48) && (incoming_byte <= 57))
	{
		incoming_byte -= 48;
		buff = buff*10 + incoming_byte;
	}
	else if (incoming_byte == SERVO1_TERM)
	{
		servo1 = constraint(buff, 0, 180);
		printf("Servo1: %d\n", servo1);
		buff = 0;
	}
	else if (incoming_byte == SERVO2_TERM)
	{
		servo2 = constraint(buff, 0, 180);
		printf("Servo2: %d\n", servo2);
		buff = 0;
	}
	else if (incoming_byte == SERVO3_TERM)
	{
		servo3 = constraint(buff, 0, 180);
		printf("Servo3: %d\n", servo3);
		buff = 0;
	}
	else if (incoming_byte == SERVO4_TERM)
	{
		servo4 = constraint(buff, 0, 180);
		printf("Servo4: %d\n", servo4);
		buff = 0;
	}
	else if (incoming_byte == SERVO5_TERM)
	{
		servo5 = constraint(buff, 0, 180);
		printf("Servo5: %d\n", servo5);
		buff = 0;
	}
	else if (incoming_byte == SERVO6_TERM)
	{
		servo6 = constraint(buff, 0, 180);
		printf("Servo6: %d\n", servo6);
		buff = 0;
	}
	else if (incoming_byte == 'g')
	{
		flag = 1;
		printf("Sequence\n");
		buff = 0;
	}
	else
		printf("Incorrect input\n");
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}

void sequence()
{
	int delay = 300;
	set_servo_angle(11, 30);
	set_servo_angle(9, 108);
	delay_ms(delay);

	set_servo_angle(11, 11);
	set_servo_angle(9, 88);
	delay_ms(delay);

	set_servo_angle(11, 0);
	set_servo_angle(9, 142);
	delay_ms(delay);

	set_servo_angle(11, 45);
	set_servo_angle(9, 142);
	delay_ms(delay);
}


int main()
{
	GPIO_InitTypeDef gpio;
	I2C_InitTypeDef i2c;
	USART_InitTypeDef uart;
	NVIC_InitTypeDef nvic;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	//  configure pins for UART
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_2;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);

	USART_StructInit(&uart);
	uart.USART_BaudRate = 115200;
	USART_Init(USART2, &uart);

	USART_Cmd(USART2, ENABLE);
	//  configure interruption for UART
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	nvic.NVIC_IRQChannel = USART2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

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

	pca9685_config();

	set_servo_angle(0, servo1);
	set_servo_angle(1, servo2);
	set_servo_angle(2, servo3);
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
		set_servo_angle(0, servo1);
		set_servo_angle(1, servo2);
		set_servo_angle(2, servo3);
		set_servo_angle(9, servo4);
		set_servo_angle(11, servo5);
		set_servo_angle(10, servo6);

		delay_ms(10);

	}
}
