/*
 * dco.c
 *
 *  Created on: May 30, 2018
 *      Author: jacoby
 */

#include <msp430.h>


void Init_DCO(void)
{

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

    //===================================================================================================

}
