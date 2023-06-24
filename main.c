/***************************************************************************//**
  @file     main.c
  @brief    Archivo principal
  @Author   Ignacion Quintana, Teo Nicoletti, Tristan Gonzalez Branca y Pedro Garcia Delucis
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "system.h"
#include "button.h"
#include "gpio.h"
#include "encoder.h"
#include "board.h"
#include "isr.h"
#include "SSDisp.h"
#include "hardware.h"
#include "boardleds.h"

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

void AppInit(void);
void AppRun(void);
void checkOpen(void);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

// Estructura de datos para el display
display_t display = {
    .psw_try = {0, 0, 0, 0},
    .active = 0
};

const char PSW[] = {1, 2, 3, 4}; // Contraseña
uint8_t mistakes = 0;

void main(void)
{
    // NO TOCAR
    systemInitFirst();
    boardInit();
    AppInit();
    systemInitLast();

    for (;;)
        AppRun();
    // NO TOCAR
}

void AppInit(void)
{
    // Inicialización (se ejecuta 1 sola vez al comienzo)
    // Inicialización del display
    setDisplay(display.psw_try);
    setActive(display.active);
    displayInit();
    encoderInit(); // Inicialización del encoder
    buttonInit(); // Inicialización del boton
    ledsInit(mistakes); // Inicialización de los LEDs (contador de errores)
}

void AppRun(void)
{
    // Loop (se ejecuta constantemente en un ciclo infinito)

    // Verificar si se ha cambiado el estado del encoder
    uint8_t encoderFlag = encoderGetStatus();
    uint8_t buttonFlag = buttonGetStatus();
    // Logica segun estado del encoder
    switch (encoderFlag) {
        case CW:
            // El encoder gira en sentido horario
            encoderResetStatus(); // Reinicia el estado del encoder
            // Logica para aumentar el numero visible en el display entre 0 y 9
            display.psw_try[display.active] = display.psw_try[display.active] + 1;
            display.psw_try[display.active] %= 10;
            setDisplay(display.psw_try); // Muestra el numero en el display
            break;
        case CCW:
            // El encoder gira en sentido antihorario
            encoderResetStatus(); // Reinicia el estado del encoder
            // Logica para aumentar el numero visible en el display entre 0 y 9
            if (display.psw_try[display.active] == 0)
                display.psw_try[display.active] = 10;
            display.psw_try[display.active] = display.psw_try[display.active] - 1;
            display.psw_try[display.active] %= 10;
            setDisplay(display.psw_try); // Muestra el numero en el display activo
            break;
    }

    if (buttonFlag) {
        // Se ha presionado el botón
        buttonResetStatus();
        display.active++; // Cambiar que display se esta modificando

        if (display.active == 4)
            checkOpen(); // Cuando el usuario toca le boton estado en el ultimo display se verifica si la contrasena es correcta

        display.active %= 4; // Se mantiene el contador para solo 4 displays
        setActive(display.active);
    }
}

void checkOpen() // Verificar si la contraseña ingresada es correcta
{
    int i;
    for (i = 0; i < 4; i++) {
        if (PSW[i] != display.psw_try[i]) {
            mistakes++; // Si la contrasena ingresada no es correcta se incrementa el contador de errores
            setLeds(mistakes); // Cambian los leds para mostar el numero de errores
            break;
        }
        if (i == 3) {
            // La contraseña es correcta
            displayOpen(); // Se escribe OPEN en el display
            mistakes = 0; // Se resetea contador de errores
            setLeds(mistakes);  // Cambian los leds para mostar el numero de errores
        }
    }

    if (mistakes >= 3) {
        // Se ha alcanzado el límite de intentos incorrectos
        displayLocked(); // Se muestra que la contrasena es incorrecta en el display
        __delay_cycles(DELAY_CYCLES); // Delay para bloquear el micro ya que la contrasena es incorrecta
        // Se resetean los estados del encoder y boton para evitar entradas durante el bloqueo del display
        encoderResetStatus();
        buttonResetStatus();
        setDisplay(display.psw_try);
        mistakes = 2; // Se reduce le numero de errores
        setLeds(mistakes);
    }
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
