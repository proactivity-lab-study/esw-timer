/**
 * @file timer_handler.c
 *
 * @brief Init TIMER0 to control buzzer with PWM signal.
 * 
 * @author Johannes Ehala, ProLab.
 * @license MIT
 *
 * Copyright ProLab, TTÜ. 15 January 2022
 */

#include "em_cmu.h"
#include "em_timer.h"

#include "timer_handler.h"

void buzzer_gpio_init(void)
{
    CMU_ClockEnable(cmuClock_GPIO, true);

    // Configure buzzer pin as push-pull output pin.
    GPIO_PinModeSet(ESWGPIO_BUZZER_PORT, ESWGPIO_BUZZER_PIN, gpioModePushPull, 0);
}

/**
 * @brief Init TIMER0 to regulate PWM dutycycle. 
 */
void timer0_init(void)
{
	// Enable Timer and GPIO clocks.
    CMU_ClockEnable(cmuClock_TIMER0, true);

	// Init CompareCapture for PWM. 
	// https://docs.silabs.com/mcu/latest/efr32mg12/structTIMER-InitCC-TypeDef
	TIMER_InitCC_TypeDef ccInit = TIMER_INITCC_DEFAULT;
	ccInit.mode = timerCCModePWM;
	ccInit.cmoa = timerOutputActionToggle;
	
	TIMER_InitCC(TIMER0, BUZZER_CC_CHANNEL, &ccInit);

	// Enable GPIO toggling by TIMER and set location of pins to be toggled.
	TIMER0->ROUTEPEN = (TIMER_ROUTEPEN_CC0PEN); //Definition at line 589 of file efr32mg12p_timer.h.
	TIMER0->ROUTELOC0 = (BUZZER_LOCATION);

	// Set TIMER0 top value and initial PWM duty cycle.
	TIMER_TopSet(TIMER0, BUZ_TIMER0_TOP_VAL);
	TIMER_CompareBufSet(TIMER0, BUZZER_CC_CHANNEL, 0); // Initial duty cycle = 0

	// TIMER general init
	TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
	timerInit.prescale = BUZ_TIMER0_CLOCK_DIV;
	timerInit.enable = true; // Start timer after init.

	TIMER_Init(TIMER0, &timerInit);
}

void timer0_set_pwm_dc(uint32_t dc)
{
    TIMER_CompareBufSet(TIMER0, BUZZER_CC_CHANNEL, dc);
}
