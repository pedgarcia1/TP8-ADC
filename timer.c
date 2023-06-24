#include "timer.h"

void timerInitialization(uint16_t period, uint16_t cycleTime)
{
    // Configure Timer_A0.
    TA0CTL = TASSEL__SMCLK  | TIMER_UP | TAIE | ID__8 ; // 1Mhz para el timer
    TA0CCTL0 = CCIE;          // CCR0 interrupt enable


    TA0CCR0 = period; // PWM Period.
    TA0CCTL0 = 0; 
 
    TA0CCR1 = cycleTime; // Time ON
    // TA0CCTL1 = OUTMOD_7; // Reset/set mode
}

void timerStop(void)
{
    TA0CTL = TASSEL_2; // Stop timer.
}

void timerStart(void)
{
    TA0CTL = TASSEL_2 | MC_1; // Start timer.
}