#include "ADC.h" 

void adcInit(void)
{
    /* Select Reference */
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
  	//  ADC10CTL0 = SREF_1 + ADC10SHT_2 + ADC10ON + REF2_5V + REFON;

    /*Select input channel P1.7*/
    ADC10CTL1 = INCH_7; // input A7

    /* Enable  P1.7 pin as Analog innput (A7) */
    ADC10AE0 |= 0x80; // P1.7 ADC option select
}

unsigned int readADC(void)
{
	unsigned int adcval;
	ADC10CTL0 |= ENC + ADC10SC; // Enable converter & Start of conversion
	// chequear esta parte de busy
	while (ADC10CTL1 & BUSY)
	{ /* do nothing */ } // Wait if ADC10 core is active
	adcval=ADC10MEM;  // Read adc value
	return adcval;
}

