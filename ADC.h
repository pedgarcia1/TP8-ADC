#ifndef _ADC_H_
#define _ADC_H_

#include "isr.h"
#include "board.h"

typedef struct 
{
    volatile uint16_t value;
    volatile float voltage;
    float vmax;
    float vmin;
}adc_t;


void adcInit(void);

void readADC(void);

void adc2voltage(void);

float getVoltage(void);

uint16_t getValue(void);

#endif // _ADC_H_
