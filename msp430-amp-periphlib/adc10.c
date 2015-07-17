/*
 * =====================================================================================
 *
 *       Filename:  adc10.c
 *
 *    Description:  10-bit ADC Driver code for MSP430G2553
 *
 *        Version:  0.0.1
 *        Created:  07/16/2015 08:33:39 PM
 *       Revision:  none
 *       Compiler:  msp430-elf-gcc
 *
 *         Author:  W. Alex Best (mn), alexbest@alexbest.me
 *        Company:  Amperture Engineering
 *
 * =====================================================================================
 */

//TODO:
//Allow for proper, non-hardcoded configuration of ADC10 Control Registers.

#include <msp430.h>

void adcInit(){
    //Init all values in ADC10CTL0 to 0
    ADC10CTL0 = 0;
    ADC10CTL1 = 0;

    //Find desired values.
    ADC10CTL1 |= (INCH_0 | ADC10DIV_3);
    ADC10CTL0 |= (ADC10SHT_2 | ADC10SREF_0 | ADC10ON | ADC10IE);

    //Enable P1.0 for ADC
    ADC10AE0 |= BIT0;
}

unsigned int adcRead(){
    //Sample & Conversion Start
    ADC10CTL0 |= ENC + ADC10SC;

    //Enable Interrupts, Enter LPM0
    __bis_SR_register(CPUOFF + GIE);

    return ADC10MEM;
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){

    //Return CPU to active mode
    __bic_SR_register_on_exit(CPUOFF);
}
