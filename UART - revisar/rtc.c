#include <msp430.h>

/*
 * rtc.c
 *
 *  Created on: May 30, 2018
 *      Author: jacoby
 */
// On Board User Leds
#define RED_LED    0      //P1.0
#define GREEN_LED  1       //P1.1
#define LED_PORT P1OUT

static int count;

void Init_RTC(void)
{

        RTCMOD = 8000-1;   // Modulus 8000

        /* Enable SMCLK as source , Prescaler divide by 1
           Enable RTC Interrupts.
        */

        RTCCTL = (RTCSS__SMCLK | RTCPS__1 | RTCIE );


}

void Set_timer(int delay)
{

    count=delay;
}


int Get_timer_status(void)
{

    return(!count);

}



#pragma vector=RTC_VECTOR           //Interrupt Service Routine (ISR) for RTC
__interrupt void isr_myrtc(void)    // 8MHz/ 8000 => T=1 mseg
{
 volatile int dummy;
           dummy=(RTCIV);           // Clear RTC interrupt Flag
//           P1OUT ^= 0x02;         // Test Period
           if(count)
               count--;

}
