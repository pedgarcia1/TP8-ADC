/*
 * uart.c
 *
 *  Created on: May 30, 2018
 *      Author: jacoby
 */
#include <msp430.h>
#include "cqueue.h"
#include "gpio.h"

void uartInit(void)
{
    QueueInit();

    // Configure UART pins - CAMBIAR POR USB!!
    P1SEL0 |= BIT4 | BIT5;                    // set 2-UART pin as second function. CAMBIAR, NECESITO USB

    // Configure UART - AJUSTAR VALORES PARA NUESTRO BRCLCK Y ASEGURAR 9600 baud rate

    UCA0CTL1 |=  UCSSEL_2 + UCSWRST;  // USCI Clock = SMCLK,USCI_A0 disabled
    UCA0BR0   =  104;                 // 104 From datasheet table- JACOBY PONE 52
    UCA0BR1   =  0;                   // -selects baudrate =9600,clk = SMCLK
    UCA0MCTL  =  UCBRS_1;             // Modulation value = 1 from datasheet
    UCA0STAT |=  UCLISTEN;            // loop back mode enabled
    UCA0CTL1 &= ~UCSWRST;             // Clear UCSWRST to enable USCI_A0

    //Enabling the interrupts
    IE2 |= UCA0TXIE;                  // Enable the Transmit interrupt
    IE2 |= UCA0RXIE;                  // Enable the Receive  interrupt

    // Baud Rate calculation
    // 8000000/(16*9600) = 52.083
    // Fractional portion = (8000000/9600)= 0.333
    // User's Guide Table 21-4: UCBRSx = 0x49
    // UCBRFx = int ( (52.083-52)*16) = 1
}


void putChar(char c)
    {
        UCA0TXBUF = c;
    }

int getTXStatus(void)
{
    return (IFG2 & UCA0TXIFG);
}

// No entiendo que hace en queue, NUNCA USA LOS REGISTROS DE RECEIVER
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



// Revisar lo que hace jacoby, los registros seguro estan mal
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

//Robados
#pragma vector = USCIAB0TX_VECTOR
__interrupt void TransmitInterrupt(void)
{
  P1OUT  ^= BIT0;//light up P1.0 Led on Tx
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void ReceiveInterrupt(void)
{
  P1OUT  ^= BIT6;     // light up P1.6 LED on RX
  IFG2 &= ~UCA0RXIFG; // Clear RX flag
}












