/***************************************************************************//**
  @file     gpio.h
  @brief    Header de servicios simples de pines GPIO, similares a Arduino
  @author   Grupo 5
 ******************************************************************************/

#ifndef _GPIO_H_
#define _GPIO_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "common.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define LOW             0
#define HIGH            1

#ifndef INPUT
#define INPUT           0
#define OUTPUT          1
#define INPUT_PULLUP    2
#define INPUT_PULLDOWN  3
#endif // INPUT


// Convertir el puerto y el n�mero en identificador de pin
// Ej: P1.4 -> PORTNUM2PIN(1, 4) --> 0x14
//     P2.6 -> PORTNUM2PIN(2, 6) --> 0x26
#define PORTNUM2PIN(po, n)  ((po)<<4 | (n))
#define PIN2PORT(pi)        (((pi)>>4) & 0x03)
#define PIN2NUM(pi)         ((pi) & 0x07)


#define ADD2MSK(p, msk) \
    do { \
        if ((((p) & 0xF0) >> 4) == 1) { \
            msk |= (1 << ((p) & 0x0F)); \
        } else if ((((p) & 0xF0) >> 4) == 2) { \
            msk |= ((1 << (((p) & 0x0F)) << 8)); \
        } \
    } while (0);



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef uint8_t gpio_t;


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Configura el pin especificado para comportarse como un GPIO
 * @param pin Identificador del pin (seg�n PORTNUM2PIN)
 * @param mode Modo deseado (INPUT, OUTPUT, INPUT_PULLUP o INPUT_PULLDOWN)
 */
void gpioMode(gpio_t pin, uint8_t mode);

/**
 * @brief Escribe un valor HIGH o LOW en un pin digital
 * @param pin Identificador del pin (seg�n PORTNUM2PIN)
 * @param value Valor deseado (HIGH o LOW)
 */
void gpioWrite(gpio_t pin, uint8_t value);

/**
 * @brief Invierte el valor de un pin digital (HIGH<->LOW)
 * @param pin Identificador del pin (seg�n PORTNUM2PIN)
 */
void gpioToggle(gpio_t pin);

/**
 * @brief Lee el valor de un pin digital, ya sea HIGH o LOW
 * @param pin Identificador del pin (seg�n PORTNUM2PIN)
 * @return HIGH o LOW
 */
uint8_t gpioRead(gpio_t pin);

/**
 * @brief Escribe un valor de 8 bits en los pines especificados en la mascara. La mascara es de 16 bits porque controla los dos puertos a la vez. Los 8 menos significativos corresponden al puerto 1 y los 8 mas significativos al puerto 2.
 * @param byte Valor de 8 bits a escribir en los pines
 * @param mask Mascara de 16 bits que indica en que pines se debe escribir. Un 1 en la mascara indica que se debe escribir en el pin correspondiente.
 * @return
 * @note Modificacion by Teo. Consultar ante dudas.
 */
void gpioWriteMaskedByte (uint16_t byte, uint16_t mask);

/*******************************************************************************
 ******************************************************************************/

#endif // _GPIO_H_
