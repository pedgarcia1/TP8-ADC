#include <msp430.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "rtc.h"
#include "uart.h"
#include "dco.h"
/* Uart3 Example
 *
 * Echo program with RX Interrupts AND QUEUE
 *
 *
 *
 */
// MSP-EXP430FR2433 Board definitions

// On Board User Leds
#define RED_LED    0x01       //P1.0
#define GREEN_LED  0x02       //P1.1


#define NWAITS_x 1

#define RX_FULL  UCRXIFG
#define TX_EMPTY UCTXIFG


char c;
//int temp;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    // Para MSP430FR2433 agregar 1 wait state para la FRAM si la frecuencia de MCLK > 8MHz
    // Descomentar la siguiente linea si operamos mas alla de 8MHZ (MCLK)
    // FRCTL0 = FWPW | NWAITS_x; // Change the NACCESS_x value to add the right amount of waitstates, FWPW is the FRAM write password

//=======================================================================================
    P1DIR |= GREEN_LED;             // configure P1.0 as output

//=====================================================================================================
    PM5CTL0 &= ~LOCKLPM5;                     // Disable the GPIO power-on default high-impedance mode
                                              // to activate previously configured port settings
     Init_DCO();
     Init_uart();
     Init_RTC();
    _BIS_SR(GIE);                                            // Enable General interrupts

    while(1)
    {
            if (getRXStatus())
            {
                c=getChar();

                while(getTXStatus()!=TX_EMPTY);
                putChar(c);
            }

            if( Get_timer_status())
            {
                Set_timer(100);             // 100 mseg
                P1OUT ^= GREEN_LED;         // toggle P1.0
            }

    }
}
