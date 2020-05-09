/*
 * pwm_expander.h
 *
 *  Created on: May 9, 2020
 *      Author: yaroslavantonchyk
 */

#ifndef PWM_EXPANDER_H_
#define PWM_EXPANDER_H_

#define PCA9685_ADDR1 0x80
#define PCA9685_ADDR2 0x82
#define SERVO1_TERM 'a'
#define SERVO2_TERM 'b'
#define SERVO3_TERM 'c'
#define SERVO4_TERM 'd'
#define SERVO5_TERM 'e'
#define SERVO6_TERM 'f'

volatile uint32_t timer_ms;
volatile uint8_t incoming_byte;
volatile uint16_t buff;
volatile uint8_t servo1;
volatile uint8_t servo2;
volatile uint8_t servo3;
volatile uint8_t servo4;
volatile uint8_t servo5;
volatile uint8_t servo6;
volatile uint8_t flag;

void i2c_set_addr(uint32_t addr, uint8_t device_addr);
void i2c_write(uint32_t addr, const void* data, int size, uint8_t device_addr);
void pca9685_config(uint8_t device_addr);
void set_servo_angle(uint8_t channel, uint8_t angle, uint8_t device_addr);
void SysTick_Handler();
void delay_ms(int time);
void send_char(char c);
char read_char(void);
int __io_putchar(int c);
int constraint(int var, int bottom_lim, int upper_lim);
void USART2_IRQHandler();
void sequence();
void init_all();




#endif /* PWM_EXPANDER_H_ */
