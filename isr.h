/***************************************************************************//**
  @file     isr.h
  @brief    Header del driver de interrupciones
  @author   Grupo 5
 ******************************************************************************/

#ifndef _ISR_H_
#define _ISR_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "common.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/




/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: Declarar prototipos de variables globales aquí (ej: extern unsigned int anio_actual;)+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Envía una función para que se ejecute en la rutina de servicio de interrupción
 * @param function Puntero a la función que se ejecutará
 * @param period Período de ejecución de la función en número de interrupciones (ej: 1 = en cada interrupción, 2 = en cada 2 interrupciones, etc.)
 */
void send_to_isr(void (*function)(void), unsigned int period);

// +ej: Declarar prototipos de funciones globales aquí (ej: char lcd_goto (int fil, int col);)+


/*******************************************************************************
 ******************************************************************************/

#endif // _ISR_H_
