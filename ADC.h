#ifndef _ADC_H_
#define _ADC_H_
#define VMAX 3.66
#define VMIN 0

#include "board.h"


typedef struct 
{
    volatile uint16_t value;
    volatile float voltage;
}adc_t;


void adcInit(void);

void readADC(void);

void adc2voltage(void);

float getVoltage(void);

uint16_t getValue(void);

#endif // _ADC_H_
