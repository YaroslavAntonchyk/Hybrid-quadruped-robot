/*
 * pwm_expander.h
 *
 *  Created on: May 9, 2020
 *      Author: yaroslavantonchyk
 */

#ifndef PWM_EXPANDER_H_
#define PWM_EXPANDER_H_

#define PCA9685_ADDR1 0x80 //right side
#define PCA9685_ADDR2 0x82 //left side

#define SERVO1_OFFSET 11
#define SERVO2_OFFSET 18
#define SERVO3_OFFSET 43

extern uint8_t servo_angle[12];
extern const uint8_t channel[12];

void init_pca9685();
void i2c_set_addr(uint32_t addr, uint8_t device_addr);
void i2c_write(uint32_t addr, const void* data, int size, uint8_t device_addr);
void pca9685_config(uint8_t device_addr);
void set_servo_angle(uint8_t channel, uint8_t angle);
void wheel_brake(uint8_t channel, uint8_t angle, uint8_t device_addr);

#endif /* PWM_EXPANDER_H_ */
