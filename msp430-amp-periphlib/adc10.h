/*
 * =====================================================================================
 *
 *       Filename:  adc10.h
 *
 *    Description:  Header information for Amperture Engineering's ADC10 
 *                  Driver Library. 
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

#ifndef ADC10_H
#define ADC10_H
#include <msp430.h>
void adcInit()
unsigned int adcRead();
#endif
