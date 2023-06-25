/***************************************************************************//**
  @file     main.c
  @brief    Archivo principal del TP8 ej. 1
  @Author   Ignacion Quintana, Teo Nicoletti, Tristan Gonzalez Branca y Pedro Garcia Delucis
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "system.h"
#include "gpio.h"
#include "board.h"
#include "SSDisp.h"
#include "hardware.h"
#include "ADC.h"
#include "boardleds.h"

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
unsigned int voltage;
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

void AppInit(void);
void AppRun(void);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
#define EJERCICIO 2

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



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

#if EJERICCIO == 1
void AppInit(void)
{
    // Inicializaci�n (se ejecuta 1 sola vez al comienzo)
    // Inicializaci�n del display
    setDisplay([0, 0, 0, 0]);
    displayInit(STATIC);
    adcInit();
    
}

void AppRun(void)
{
    // Loop (se ejecuta constantemente en un ciclo infinito)
    voltage = getVoltage();

    setDisplay_float(voltage);

}
#elif EJERICCIO == 2

void appInit(void)
{
    // Inicializaci�n (se ejecuta 1 sola vez al comienzo)
    // Inicializaci�n del display
    setDisplay([0, 0, 0, 0]);
    displayInit(STATIC);
    adcInit();
    ledsInit(OFF);
    
}   

void appRun(void)
{
    // Loop (se ejecuta constantemente en un ciclo infinito)
    voltage = getVoltage();

    setDisplay_float(voltage);

    if (voltage > 3.3/2)
    {
        setLeds(ON);
    }else if (voltage <= 3.3/2)
    {
        setLeds(OFF);
    }
    
}

#elif EJERICCIO == 3

#endif // EJERICCIO


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
