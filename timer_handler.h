/**
 * @file timer_handler.h
 *
 * @author Johannes Ehala, ProLab.
 * @license MIT
 *
 * Copyright ProLab, TTÜ. 15 January 2022
 */

#ifndef TIMER_HANDLER_H_
#define TIMER_HANDLER_H_

#include "em_gpio.h"

#define ESWGPIO_MOTOR_PORT      gpioPortA
#define ESWGPIO_MOTOR_PIN       0
#define MOTOR_CC_CHANNEL        0
#define MOTOR_LOCATION          TIMER_ROUTELOC0_CC0LOC_LOC0 // PA0 route location for CC channel 0
#define MOT_TIMER0_CLOCK_DIV    timerPrescale256 // Timer0 clock divider

#define MOT_TIMER0_TOP_VAL      100
#define MOT_PWM_DUTY_CYCLE      50

// Public functions
void motor_gpio_init();
uint32_t timer0_init();
void timer0_set_pwm_dc(uint32_t dc);

#endif // TIMER_HANDLER_H_ */
