/*
 * uart.c
 *
 *  Created on: May 30, 2018
 *      Author: jacoby
 */
#include <msp430.h>
#include "cqueue.h"

void Init_uart(void)
{
    QueueInit();
    // Configure UART pins
    P1SEL0 |= BIT4 | BIT5;                    // set 2-UART pin as second function

    // Configure UART
    UCA0CTLW0 |= UCSWRST;                     // hold UART in reset state and configure
    UCA0CTLW0 |= UCSSEL__SMCLK;               // Select BRCLK == SMCLK

    // Baud Rate calculation
    // 8000000/(16*9600) = 52.083
    // Fractional portion = (8000000/9600)= 0.333
    // User's Guide Table 21-4: UCBRSx = 0x49
    // UCBRFx = int ( (52.083-52)*16) = 1

    UCA0BR0 = 52;                             // 8000000/16/9600
    UCA0BR1 = 0x00;
    UCA0MCTLW = 0x4900 | UCOS16 | UCBRF_1;



    UCA0CTLW0 &= ~UCSWRST;                    // Initialize eUSCI

    UCA0IE=UCRXIE;                            // Enable rx int

   //===========================================


}




void putChar(char c)
    {
        UCA0TXBUF = c;
    }

int getTXStatus(void)
{
    return (UCA0IFG & UCTXIFG);
}



char getChar(void)
{
    unsigned char rxdata;
    PullQueue(&rxdata);
    return rxdata;
}

int getRXStatus(void)
{
    return(QueueStatus());

}




#pragma vector=USCI_A0_VECTOR
__interrupt void UART_A0_ISR(void)

{   volatile static int j=10;
    volatile int dummy;
                 dummy=(UCA0IV);            // Clear Interrupt all interrupt flags but ADCIFG0

    switch(dummy)
    {

      case USCI_NONE:
      break;
      case USCI_UART_UCRXIFG:          /* UART Receive Interrupt Flag */

      PushQueue(UCA0RXBUF);



     // if(j)
     // str[j--]=rxdata;

      break;
      case USCI_UART_UCTXIFG:          /* UART Transmit Interrupt Flag */
      break;
      case USCI_UART_UCSTTIFG:         /* UART Start Bit Interrupt Flag */
      break;
      case USCI_UART_UCTXCPTIFG:       /* UART Transmit Complete Interrupt Flag */
      break;

      default:
      break;
    }

}










