/**
 * @file     button.h
 * @brief    button services
 * @author   Teo Nicoletti
 */

#ifndef _BUTTON_H_
#define _BUTTON_H_

/* INCLUDE HEADER FILES */
#include "common.h"


/* CONSTANT AND MACRO DEFINITIONS USING #DEFINE */



/* ENUMERATIONS AND STRUCTURES AND TYPEDEFS */



/* VARIABLES WITH GLOBAL SCOPE 
 * +ej: unsigned int anio_actual;*/


/* FUNCTION PROTOTYPES WITH GLOBAL SCOPE */

/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

/**
 * @brief Inicia el driver del boton (que pines y isr)
*/
void buttonInit(void);
uint8_t buttonGetStatus(void);
void buttonResetStatus(void);
void buttonISR();
/**
 * @brief Devuelve el estado del boton
 * @return 1 si esta presionado, 0 si no
*/




#endif // _BUTTON_H_
