/***************************************************************************//**
  @file     SSDisp.h
  @brief    Header del controlador del display de siete segmentos (Seven Segment Driver)
  @Author   Tristan Gonzalez Branca
 ******************************************************************************/

#ifndef _SSDisp_H_
#define _SSDisp_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "common.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define BLINK_SPEED 500
#define BLINK_LIMIT 32768
// Velocidad de parpadeo y límite para el parpadeo del dígito activo

#define BLINK 0
#define STATIC 1
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
uint8_t status2;
// Variable global de ejemplo

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Imprime un dígito en una posición específica
 * @param pos La posición del dígito a imprimir
 */
void printDigit(int pos);

/**
 * @brief Muestra el mensaje "OPEN" en el display
 */
void displayOpen(void);

/**
 * @brief Establece los valores a mostrar en el display
 * @param show[] Arreglo de 4 elementos con los valores a mostrar en cada posición
 */
void setDisplay(uint8_t show[]);

/**
 * @brief Establece el dígito activo en el display
 * @param active La posición del dígito a activar
 */
void setActive(uint8_t active);

/**
 * @brief Rutina de interrupción para el control del display
 */
void displayBlinkISR(void);

void displayStaticISR(void);

/**
 * @brief Inicializa el controlador del display de siete segmentos
 * @param selected_mode Indica el modo en el que se va a utilizar el display. Con un dígito activo (BLINK) o sin (STATIC)
 */
void displayInit(uint8_t selected_mode);

/**
 * @brief Apaga el dígito en la posición especificada
 * @param pos La posición del dígito a apagar
 */
void printOff(int pos);

/**
 * @brief Muestra el mensaje "LOCK" en el display
 */
void displayLocked(void);

/**
 * @brief Convierte un dígito decimal en su valor hexadecimal correspondiente
 * @param val El dígito decimal
 * @param pos La posición en la que se almacenará el valor hexadecimal
 */
void digit2hexa(int val, int pos);
/*******************************************************************************
 ******************************************************************************/

#endif // _SSDisp_H_
