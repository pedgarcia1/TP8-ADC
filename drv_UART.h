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

/**
* @brief Inicializa el UART
*/
void UART_init(); 

/**
 * @brief Envia Array por UART
 * @param *TxArray Array a enviar
 * @param ArrayLength Largo del array
 */
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);

/**
 * @brief Devuelve el estado del flag de recepcion 
*/
uint8_t getRXStatus();

/**
 * @brief Resetea el flag de recepcion 
*/
void resetRXStatus();

/**
 * @brief Devuelve el caracter recibido 
*/
uint8_t getChar();

/**
 * @brief Setea el periodo de trabajo de UART
 * @param period Periodo de trabajo 
*/
void setUARTPeriod(uint16_t period);

/**
* @brief Funcion periodica de UART
*/
void UARTPeriodic();

/**
 * @brief Setea el mensaje a enviar por UART
 * @param Text Mensaje a enviar
 * @param Largo Largo del mensaje
*/
void setTXMessage(unsigned char *Text, unsigned char Largo);


/*******************************************************************************
 ******************************************************************************/

#endif // _UART_H_
