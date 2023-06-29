/***************************************************************************//**
  @file     SSDisp.h
  @brief    Seven Segment Driver
  @author   Tristan Gonzalez Branca
 ******************************************************************************/

#ifndef _UART_H_
#define _UART_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void UART_init(); //INICIALIZA EL UART
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength); //Send array to UART
uint8_t getRXStatus();
void resetRXStatus();
uint8_t getChar();
<<<<<<< HEAD:drv_UART.h
void setUARTPeriod(uint16_t period);
void UARTPeriodic();
void setTXMessage(unsigned char *Text, unsigned char Largo);
=======
>>>>>>> parent of 6096004 (UART PIOLA):UART_TRIS/drv_UART.h

/*******************************************************************************
 ******************************************************************************/

#endif // _UART_H_
