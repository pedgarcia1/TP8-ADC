#ifndef _ADC_H_
#define _ADC_H_

#include "isr.h"

typedef struct 
{
    uint16_t value;
    float voltage;
    float vmax;
    float vmin;
}adc_t;


void adcInit(void);

unsigned int readADC(void);

void adc2voltage(void);


#endif // _ADC_H_