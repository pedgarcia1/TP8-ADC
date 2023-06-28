/* Es importante que una vez cargado el codigo se pare el debugueo y se reinicie el micro para poder
 * comunicar con la terminal (Putty) */

#include "msp430g2553.h"

//#include <stdio.h>

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);

static volatile char data;

void main(void)

{
 WDTCTL = WDTPW + WDTHOLD; // Stop WDT

 /* Use Calibration values for 1MHz Clock DCO*/
 DCOCTL = 0;
 BCSCTL1 = CALBC1_1MHZ;
 DCOCTL = CALDCO_1MHZ;

 /* Configure Pin Muxing P1.1 RXD and P1.2 TXD */
 P1SEL = BIT1 | BIT2 ;
 P1SEL2 = BIT1 | BIT2;

 /* Place UCA0 in Reset to be configured */
 UCA0CTL1 = UCSWRST;

 /* Configure */
 UCA0CTL1 |= UCSSEL_2; // SMCLK
 UCA0BR0 = 104; // 1MHz 9600
 UCA0BR1 = 0; // 1MHz 9600
 UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1

 /* Take UCA0 out of reset */
 UCA0CTL1 &= ~UCSWRST;

 IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt

__bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
data = UCA0RXBUF;
UARTSendArray("Comando Recibido: ", 18);
UARTSendArray(&data, 1);
UARTSendArray("\n\r", 2);

switch(data){
 case 'V':
 {
     UARTSendArray("Lectura en Volts", 16);
     UARTSendArray("\n\r", 2);
 }
 break;
 case 'C':
 {
     UARTSendArray("Lectura en Crudo", 16);
     UARTSendArray("\n\r", 2);
 }
 break;
 default:
 {
 UARTSendArray("Comando Desconocido: ", 21);
 UARTSendArray(&data, 1);
 UARTSendArray("\n\r", 2);
 }
 break;
 }
}

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength){
 // Send number of bytes Specified in ArrayLength in the array at using the hardware UART 0
 // Example usage: UARTSendArray("Hello", 5);
 // int data[2]={1023, 235};
 // UARTSendArray(data, 4); // Note because the UART transmits bytes it is necessary to send two bytes for each integer hence the data length is twice the array length

while(ArrayLength--){ // Loop until StringLength == 0 and post decrement
 while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
 UCA0TXBUF = *TxArray; //Write the character at the location specified py the pointer
 TxArray++; //Increment the TxString pointer to point to the next character
 }
}
