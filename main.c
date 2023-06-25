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
#include "encoder.h"
#include "uart.h"

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
unsigned int voltage;
uint8_t lightState;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

void AppInit(void);
void AppRun(void);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
#define EJERCICIO 3

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

#if EJERCICIO == 1


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
#elif EJERCICIO == 2
#define UPPER_VOLTAGE 2;
#define LOWER_VOLTAGE 1.3;

void appInit(void)
{
    // Inicializaci�n (se ejecuta 1 sola vez al comienzo)
    // Inicializaci�n del display
    setDisplay([0, 0, 0, 0]);
    displayInit(STATIC);
    adcInit();
    ledsInit(OFF);
    lightState = OFF;
}   

void appRun(void) // Loop (se ejecuta constantemente en un ciclo infinito)
{
    voltage = getVoltage();

    setDisplay_float(voltage);

    if (lightState == OFF && voltage > UPPER_VOLTAGE)
    {
        lightState = ON;
        ledsInit(ON);
    }
    else if (lightState == ON && voltage < LOWER_VOLTAGE)
    {
        lightState = OFF;
        ledsInit(OFF);
    }
    

}

#elif EJERCICIO == 3

#define UPPER_VOLTAGE 2
#define LOWER_VOLTAGE 1.3
#define UART_LLIMIT 100
#define UART_ULIMIT 2000

uint8_t uart_time = 800;
uint8_t write_mode = "c";
uint16_t tsm_message;
uint8_t rcv_message;
uint8_t encoderFlag;
uint8_t receiverFlag;
uint8_t transmitterFlag;

void appInit(void)
{
    // Inicializaci�n (se ejecuta 1 sola vez al comienzo)
    // Inicializaci�n del display
    setDisplay([0, 0, 0, 0]);
    displayInit(STATIC);
    adcInit();
    Init_uart();
    ledsInit(OFF);
    lightState = OFF;
}   

void appRun(void) // Loop (se ejecuta constantemente en un ciclo infinito)
{
    voltage = getVoltage();

    setDisplay_float(voltage);

    if (lightState == OFF && voltage > UPPER_VOLTAGE)
    {
        lightState = ON;
        ledsInit(ON);
    }
    else if (lightState == ON && voltage < LOWER_VOLTAGE)
    {
        lightState = OFF;
        ledsInit(OFF);
    }

    // Verificar si se ha cambiado el estado del encoder
    encoderFlag = encoderGetStatus();
    receiverFlag = getRXStatus();
    

    if (receiverFlag > 0):{
        rcv_message = getChar();
        if(rcv_message == "c" || rcv_message == "v"):
            write_mode = rcv_message;
    }

    while(/*condicion de mensaje para enviar*/){
        
    }

    // Logica segun estado del encoder
    switch (encoderFlag) {
        case CW:
            // El encoder gira en sentido horario
            encoderResetStatus(); // Reinicia el estado del encoder
            uart_time += 100;
            if (uart_time < UART_ULIMIT):
                uart_time = UART_ULIMIT; 
            
            break;

            break;
        case CCW:
            // El encoder gira en sentido antihorario
            encoderResetStatus(); // Reinicia el estado del encoder
            uart_time -= 100;
            if (uart_time < UART_LLIMIT):
                uart_time = UART_LLIMIT; 
            
            break;
    }
}

#endif // EJERCICIO


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
