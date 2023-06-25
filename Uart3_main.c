#include <msp430.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Uart3 Example
 *
 * Echo program with RX Interrupts
 *
 *
 *
 */
// MSP-EXP430FR2433 Board definitions

// On Board User Leds
#define RED_LED    0x01       //P1.0
#define GREEN_LED  0x02       //P1.1

// On Board User Switches

#define SW1  0x08       //P2.3
#define SW2  0x80       //P2.7

#define b3   0b00001000
#define NWAITS_x 1

#define RX_FULL  UCRXIFG
#define TX_EMPTY UCTXIFG


void putChar_nb(char);
int getTXStatus(void);

char getChar_int(void);
int getRXStatus_int(void);

#define NO_DATA_AVAILABLE 0
#define DATA_AVAILABLE 1

int rxdata;
int rxsts=NO_DATA_AVAILABLE;


char c;
int temp;

char str[20];

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    // Para MSP430FR2433 agregar 1 wait state para la FRAM si la frecuencia de MCLK > 8MHz
    // Descomentar la siguiente linea si operamos mas alla de 8MHZ (MCLK)
    // FRCTL0 = FWPW | NWAITS_x; // Change the NACCESS_x value to add the right amount of waitstates, FWPW is the FRAM write password

//=======================================================================================
    P1DIR |= GREEN_LED;             // configure P1.0 as output

    P2DIR &= (~SW1);
    P2REN= SW1;
    P2OUT=SW1;

//=====================================================================================================
    PM5CTL0 &= ~LOCKLPM5;                     // Disable the GPIO power-on default high-impedance mode
                                              // to activate previously configured port settings
//=============== FLL Settings=========================================================================
     __bis_SR_register(SCG0);                 // disable FLL
     CSCTL3 |= SELREF__REFOCLK;               // Set REFO as FLL reference source
     CSCTL0 = 0;                              // clear DCO and MOD registers
     CSCTL1 &= ~(DCORSEL_7);                  // Clear DCO frequency select bits first
     CSCTL1 |= DCORSEL_3;                     // Set DCO = 8MHz
     CSCTL2 = FLLD_0 + 243;                   // DCODIV = 8MHz  (FLLN*1)=243*1=244  Fout=244*32768=7.995.392 Hz
     __delay_cycles(3);
     __bic_SR_register(SCG0);                 // enable FLL
     while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); // Poll until FLL is locked

     CSCTL4 = SELMS__DCOCLKDIV | SELA__REFOCLK; // set default REFO(~32768Hz) as ACLK source, ACLK = 32768Hz
                                              // default DCODIV as MCLK and SMCLK source


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



    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode
                          // to activate previously configured port settings


    _BIS_SR(GIE);                                            // Enable General interrupts

    volatile unsigned long int i;        // volatile to prevent optimization

    while(1)
    {
        while (P2IN & SW1)
        {
        P1OUT ^= GREEN_LED;         // toggle P1.0



       if (getRXStatus_int()==DATA_AVAILABLE)
       {
           c=getChar_int();

           while(getTXStatus()!=TX_EMPTY);
           putChar_nb(c);


       }



        for(i=100000; i>0; i--);     // delay
        }

    }


}


void putChar_nb(char c)
    {
        UCA0TXBUF = c;
    }

int getTXStatus(void)
{
    return (UCA0IFG & UCTXIFG);
}



char getChar_int(void)
{
    return rxdata;
}

int getRXStatus_int(void)
{
    volatile int tmp;

    tmp=rxsts;

    rxsts=NO_DATA_AVAILABLE;

    return (tmp);
}




#pragma vector=USCI_A0_VECTOR
__interrupt void UART_A0_ISR(void)

{   volatile static int j=10;
    volatile int dummy;
                 dummy=(UCA0IV);            // Clear Interrupt all interrupt flags but ADCIFG0

    switch(dummy)
    {

      case USCI_NONE :
      break;
      case USCI_UART_UCRXIFG:          /* UART Receive Interrupt Flag */

      rxdata=UCA0RXBUF;
      rxsts=DATA_AVAILABLE;

      if(j)
      str[j--]=rxdata;

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









