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
#include "drv_UART.h"
#include "timer.h"

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
float voltage;
uint16_t value;
uint8_t lightState;

uint16_t uart_time = 800;
uint8_t write_mode = 'C';
unsigned char tx_message[6];
unsigned char rcv_message;
uint8_t encoderFlag;
uint8_t rxFlag;
uint8_t transmitterFlag;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

void AppInit(void);
void AppRun(void);
void float2ASCII(float number);
void int2ASCII(uint8_t number);

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
    displayInit(STATIC);
    adcInit();
    timerInitialization(13100); // 100ms timer perdios for ADC interrupt
    timerStart();
    
}

void AppRun(void)
{
    // Loop (se ejecuta constantemente en un ciclo infinito)
    voltage = getVoltage();

    setDisplay_float(voltage);

}

#elif EJERCICIO == 2
#define UPPER_VOLTAGE 2
#define LOWER_VOLTAGE 1.3

void AppInit(void)
{
    // Inicializaci�n (se ejecuta 1 sola vez al comienzo)
    // Inicializaci�n del display
    displayInit(STATIC);
    adcInit();
    timerInitialization(12499); // 100ms timer perdios for ADC interrupt
    timerStart();
    ledsInit(OFF);
    lightState = OFF;
}   

void AppRun(void) // Loop (se ejecuta constantemente en un ciclo infinito)
{
    voltage = getVoltage();

    setDisplay_float(voltage);

    if((lightState == OFF) && (voltage >= UPPER_VOLTAGE))
    {
        lightState = ON;
        setLeds(ON);
    }

    if ((lightState == ON) && (voltage <= LOWER_VOLTAGE))
    {
        lightState = OFF;
        setLeds(OFF);
    }
}

#elif EJERCICIO == 3

#define UPPER_VOLTAGE 2
#define LOWER_VOLTAGE 1.3
#define UART_LLIMIT 100
#define UART_ULIMIT 2000

void appInit(void)
{
    // Inicializaci�n (se ejecuta 1 sola vez al comienzo)
    // Inicializaci�n del display
    displayInit(STATIC);
    adcInit();
    UART_init();
    ledsInit(OFF);
    lightState = OFF;


}   

void appRun(void) // Loop (se ejecuta constantemente en un ciclo infinito)
{
    voltage = getVoltage();
    value = getValue();

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
    
    // Verificar si hubo un mensaje
    rxFlag = getRXStatus();


    if (rxFlag > 0){
        rcv_message = getChar();
        resetRXStatus();
        if(rcv_message == 'C' || rcv_message == 'V'){
            write_mode = rcv_message;
        }
    }

    // Enviar el mensaje
    tx_message[5] = '\n';

    if (write_mode == 'C'){
        int2ASCII(value);
    }else{ if(write_mode == 'V'){
        float2ASCII(voltage);
    }
    }
    setTXMessage(tx_message, 6);

    // Logica segun estado del encoder
    switch (encoderFlag) {
        case CW:
            // El encoder gira en sentido horario
            encoderResetStatus(); // Reinicia el estado del encoder
            uart_time += 100;
            if (uart_time < UART_ULIMIT)
                uart_time = UART_ULIMIT; 

            setUARTPeriod(2*uart_time);
            break;

        case CCW:
            // El encoder gira en sentido antihorario
            encoderResetStatus(); // Reinicia el estado del encoder
            uart_time -= 100;
            if (uart_time < UART_LLIMIT)
                uart_time = UART_LLIMIT;
            
            setUARTPeriod(2*uart_time);
            break;

    }
 
}

#endif // EJERCICIO


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void float2ASCII(float number){

    uint8_t integer_digits;
    integer_digits = (int)log10(number) + 1;
    uint16_t digit;

    uint8_t i;

    if (integer_digits == 0){
        integer_digits = 1;
    }
    for (i = 0; i < 4; i++)
    {
        digit = (uint16_t) ((number)/pow(10,integer_digits-1-i));

        digit = digit - ((uint16_t) (digit/10))*10;

        if (i>0){
            tx_message[i+1] = digit + '0';
        }
        else{
            tx_message[0] = digit + '0';
            tx_message[1] = '.';
        }
    }
}

void int2ASCII(uint8_t number){
    uint8_t integer_digits;
    integer_digits = (int)log10(number) + 1;
    uint16_t digit;

    uint8_t i;

    for (i = 0; i < (5 - integer_digits); i++){
        tx_message[i] = '0';
    }

    for (i = 5 - integer_digits; i < 5; i++)
    {
        digit = (uint16_t) ((number)/pow(10,integer_digits-1-i));

        digit = digit - ((uint16_t) (digit/10))*10;

        tx_message[i] = digit + '0';
    }
}
