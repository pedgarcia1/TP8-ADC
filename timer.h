#ifndef _TIMER_H_
#define _TIMER_H_

#include <msp430.h>
#include <stdint.h>

/*Timer Useful definitions*/

/* Timer Counter Modes */
#define TIMER_STOP       MC_0   // Stop
#define TIMER_UP         MC_1   // Up to CCR0
#define TIMER_CONTINUOUS MC_2   // Up to 0xFFFF
#define TIMER_UPDOWM     MC_3   // Up to CCR0 Down to 0

void timerInitialization(uint16_t period);

void timerStart(void);

void timerStop(void);

void timerFlagClear(void);


#endif // _TIMER_H_
