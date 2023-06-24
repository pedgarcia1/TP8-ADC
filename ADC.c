#include <msp430.h> 

void adcinit(void);

unsigned int adcval=1000;


/** para msp430g2553
 * Simple ADC example. Connect a potenciometer
 *  1 -VCC
 *  2 -P1.7
 *  3 -GND
 *
 *  Insert a break point (see below) and watch adcval variable
 *  Change potentiometer position and see adcval Value when program stop at breakpoint
 *  How many volts represents adcval (use a voltmeter to check results)
 *
 *  Write a Thermostat program that turns on red led when Analog input (A7) is above 2.5Volt and turn red led off when analog input is below 1.5 Volt
 *  Use potentiometer to test the program
 *
 *  Use periodic hardware timer to read ADC once every 1 seg (aprox)
 *
 *  Use ADC interrupts instead of polling
 *
 *
 *
 *
 */
int main(void)
{
    int i;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	adcinit();

	while(1)
	{
	    adcval=ADC10MEM; // Read adc value
	    ADC10CTL0 |= ENC + ADC10SC; // Enable converter & Start of conversión  (insert a breakpoint here and watch variable adcval)
	    for(i=20000; i>0; i--);          // some delay

	}



	return 0;
}




void adcinit(void)
{
    /* Select Reference */
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
  //  ADC10CTL0 = SREF_1 + ADC10SHT_2 + ADC10ON + REF2_5V + REFON;

    /*Select input channel P1.7*/
    ADC10CTL1 = INCH_7; // input A7


    /* Enable  P1.7 pin as Analog innput (A7) */
    ADC10AE0 |= 0x80; // P1.7 ADC option select
}
