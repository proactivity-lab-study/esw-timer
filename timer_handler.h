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

#define ESWGPIO_BUZZER_PORT     gpioPortA
#define ESWGPIO_BUZZER_PIN      0
#define BUZZER_CC_CHANNEL       0
#define BUZZER_LOCATION         TIMER_ROUTELOC0_CC0LOC_LOC0 // PA0 route location for CC channel 0
#define BUZ_TIMER0_CLOCK_DIV    timerPrescale256 // Timer0 clock divider

#define BUZ_TIMER0_TOP_VAL      100
#define BUZ_PWM_DUTY_CYCLE      50

// Public functions
void buzzer_gpio_init();
void timer0_init();
void timer0_set_pwm_dc(uint32_t dc);

#endif // TIMER_HANDLER_H_ */
