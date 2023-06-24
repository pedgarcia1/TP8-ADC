
/**
 * @file     button.c
 * @brief    Driver para control de un boton conectado a un pin digital
 * @author   Teo Nicoletti
 */


/** INCLUDE HEADER FILES **/
#include "button.h"
#include "gpio.h"
#include "board.h"
#include "isr.h"




/* CONSTANT AND MACRO DEFINITIONS USING #DEFINE */



/* ENUMERATIONS AND STRUCTURES AND TYPEDEFS */



/* VARIABLES WITH GLOBAL SCOPE 
 * +ej: unsigned int anio_actual;*/


/* FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 * +ej: static void falta_envido (int);+ */


/** ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 * +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+ */


/** STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
// +ej: static int temperaturas_actuales[4];+ */

uint8_t button_now, status_button, button_before;

/* GLOBAL FUNCTION DEFINITIONS */

void buttonInit(void){
    gpioMode(BUTTON_PIN, INPUT_PULLUP);
    send_to_isr(buttonISR, 10);
}

void buttonISR(void){

    if (!status_button){
    button_now = gpioRead(BUTTON_PIN);
    status_button = (button_now ^ 1) && button_before;
    button_before = button_now;
    }
}

uint8_t buttonGetStatus(){
    return status_button;
}

void buttonResetStatus(){
    status_button = 0;
}


/* LOCAL FUNCTION DEFINITIONS */


