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

void buzzer_gpio_init()
{
    // Turn on GPIO module
    CMU_ClockEnable(cmuClock_GPIO, true);
    
    // Set buzzer pin to push-pull mode
    GPIO_PinModeSet(gpioPortA, 0, gpioModePushPull, 0);
}

/**
 * @brief Init TIMER0 to regulate PWM dutycycle. 
 */
uint32_t timer0_init(void)
{
	// Enable clocks.
    CMU_ClockEnable(cmuClock_TIMER0, true);

    // Init compare mode init and configuring.
    TIMER_InitCC_TypeDef ccInit = TIMER_INITCC_DEFAULT;
    ccInit.cofoa = timerOutputActionToggle;
    ccInit.mode = timerCCModeCompare;
    
    TIMER_InitCC(TIMER0, 0, &ccInit);
    
    TIMER_TopSet(TIMER0, 100);
    
    TIMER0->ROUTEPEN = 1; // TIMER_ROUTEPEN_CC0PEN
    TIMER0->ROUTELOC0 = TIMER_ROUTELOC0_CC0LOC_LOC0; // = 0
    
    // Timer general init and config.
    TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
    timerInit.prescale = timerPrescale1024;
    timerInit.enable = true;
    
    TIMER_Init(TIMER0, &timerInit);
    
    return (uint32_t) (CMU_ClockFreqGet(cmuClock_TIMER0) / (uint32_t) (0x01 << timerPrescale1024));
}






