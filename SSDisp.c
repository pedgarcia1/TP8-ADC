/***************************************************************************
  @file     SS_Disp.c
  @brief    Controlador de display de siete segmentos (Seven Segment Driver)
  @Author   Tristan Gonzalez Branca
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <msp430.h>
#include "gpio.h"
#include "SSDisp.h"
#include "board.h"
#include "isr.h"
#include <math.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
const int digitArray[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
// Arreglo con los valores hexadecimales correspondientes a cada d�gito (0-9)

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
uint8_t display_show[4];
uint8_t display_active;
uint8_t frame;
uint16_t flag_active;
uint8_t show[4];
uint8_t display_dot;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/**
 * @brief Inicializa el controlador del display de siete segmentos
 */
void displayInit(selected_mode){
    // Configurar los pines de control del display como salidas
    gpioMode (Disp_a, OUTPUT);
    gpioMode (Disp_b, OUTPUT);
    gpioMode (Disp_c, OUTPUT);
    gpioMode (Disp_d, OUTPUT);
    gpioMode (Disp_e, OUTPUT);
    gpioMode (Disp_f, OUTPUT);
    gpioMode (Disp_g, OUTPUT);
    gpioMode (Disp_dot, OUTPUT);
    gpioMode (Disp_sel0, OUTPUT);
    gpioMode (Disp_sel1, OUTPUT);

    if (selected_mode == BLINK)
        send_to_isr(displayBlinkISR, 70);
    else if(selected_mode == STATIC)
        send_to_isr(displayStaticISR, 70);
}

/**
 * @brief Imprime un d�gito en una posici�n espec�fica
 * @param val El valor del d�gito a imprimir
 * @param pos La posici�n en la que se imprimir� el d�gito
 */
void printDigit(int pos){
    // Configurar los pines del display para mostrar el d�gito correspondiente
    gpioWrite(Disp_a, display_show[pos] & 1 << 0);
    gpioWrite(Disp_b, display_show[pos] & 1 << 1);
    gpioWrite(Disp_c, display_show[pos] & 1 << 2);
    gpioWrite(Disp_d, display_show[pos] & 1 << 3);
    gpioWrite(Disp_e, display_show[pos] & 1 << 4);
    gpioWrite(Disp_f, display_show[pos] & 1 << 5);
    gpioWrite(Disp_g, display_show[pos] & 1 << 6);
    gpioWrite(Disp_dot, pos == display_dot);

    gpioWrite(Disp_sel0, pos & 1 << 0);
    gpioWrite(Disp_sel1, pos & 1 << 1);
}

/**
 * @brief Muestra el mensaje "OPEN" en el display
 */
void displayOpen(){
    display_show[0] = 0x3F;
    display_show[1] = 0x73;
    display_show[2] = 0x79;
    display_show[3] = 0x54;
}

/**
 * @brief Muestra el mensaje "LOCK" en el display
 */
void displayLocked(){
    display_show[0] = 0x38;
    display_show[1] = 0x39;
    display_show[2] = 0x74;
    display_show[3] = 0x5E;
}

/**
 * @brief Rutina de interrupci�n para el control del display
 */
void displayBlinkISR(){
    if (frame > 3)
        frame = 0;
    flag_active = flag_active + BLINK_SPEED;

    if (flag_active > BLINK_LIMIT && frame == display_active)
        printOff(frame);
    else
        printDigit(frame);

    frame++;
}

void displayStaticISR(){
    if (frame > 3)
        frame = 0;

        printDigit(frame);

    frame++;
}

/**
 * @brief Apaga el d�gito en la posici�n especificada
 * @param pos La posici�n del d�gito a apagar
 */
void printOff(int pos){
    // Apagar los pines del display correspondientes al d�gito especificado
    gpioWrite(Disp_a, 0);
    gpioWrite(Disp_b, 0);
    gpioWrite(Disp_c, 0);
    gpioWrite(Disp_d, 0);
    gpioWrite(Disp_e, 0);
    gpioWrite(Disp_f, 0);
    gpioWrite(Disp_g, 0);

    gpioWrite(Disp_sel0, pos & 1 << 0);
    gpioWrite(Disp_sel1, pos & 1 << 1);
}

/**
 * @brief Establece los valores a mostrar en el display
 * @param show[] Arreglo de 4 elementos con los valores a mostrar en cada posici�n
 */
void setDisplay(uint8_t show[]){
    digit2hexa(show[0], 0);
    digit2hexa(show[1], 1);
    digit2hexa(show[2], 2);
    digit2hexa(show[3], 3);
}

/**
 * @brief Establece el d�gito activo en el display
 * @param active La posici�n del d�gito a activar
 */
void setActive(uint8_t active){
    display_active = active;
}

/**
 * @brief Convierte un d�gito decimal en su valor hexadecimal correspondiente
 * @param val El d�gito decimal
 * @param pos La posici�n en la que se almacenar� el valor hexadecimal
 */
void digit2hexa(int val, int pos){
    display_show[pos] = digitArray[val];
}

void setDisplay_float(float number){
    
    display_dot = (int)log10(value) + 1;
    uint16_t digit;

    uint8_t i;

    

    for (i = 0; i < 4; i++)
    {
        digit = (uint16_t) ((number)/pow(10,display_dot-1-i));

        display_show[i] = digit - ((uint16_t) (digit/10))*10;
        
    }

    /*char numberString[DISPLAY_DIGITS+1];
    sprintf(numberString, "%f", number);
    for (int i = 0; numberString[i] != '\0' ; i++) {
        if (numberString[i] == '.' || numberString[i] == '-') {
            continue;
        }
        int digit = atoi(&numberString[i]);
        display_show[i] = digit;
        
    }*/

    /*int integerPart = (int)number;
    float fractionalPart = number - integerPart;

    uint8_t integer_digits = (int)log10(number) + 1;

    // Extraer los dígitos de la parte entera
    int temp = abs(integerPart);
    int digitCount = (integerPart == 0) ? 1 : (int)log10(temp) + 1;
    for (int i = digitCount - 1; i >= 0; i--) {
        int digit = temp / (int)pow(10, i);
        display_show[digitCount-1-i] = digit;
        temp %= (int)pow(10, i);
    }

    // Extraer los dígitos de la parte fraccionaria
    while (fractionalPart != 0) {
        fractionalPart *= 10;
        int digit = (int) fractionalPart;
        display_show[digitCount++] = digit;
        fractionalPart -= digit;
    }*/
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/******************************************************************************/
