/*
 * =========================================================================
 *
 *       Filename:  spi.c
 *
 *    Description:  Serial Peripheral Interface library for MSP430G2553 chip.
 *
 *    WARNING!!!! UNTESTED CODE
 *    DO NOT USE YET! CODE IS NOT PROVIDED ASSUMED TO BE FUNCTIONING!!
 *
 *        Version:  0.0.1
 *        Created:  07/12/2015 07:55:40 PM
 *       Revision:  none
 *       Compiler:  msp430-elf-gcc
 *
 *         Author:  W. Alex Best (mn), alexbest@alexbest.me
 *        Company:  Amperture Engineering
 *
 * ==========================================================================
 */

#include <msp430.h>

void spiInit(){
    UCA0CTL1 |= UCSWRST;

    //UCCKPH    - Phase Select, 0 = change -> capture
    //UCCKPL    - Polarity Select, 0 = rising edge
    //UC7BIT    - data length, 0 = 8-bit data
    UCA0CTL0 &= ~(UCCKPH | UCCKPL | UC7BIT | UCMODE0 | UCMODE1);

    //UCMSB     - Most Significant Bit first
    //UCMST     - Master Mode
    UCA0CTL0 |= (UCMSB | UCMST);

    //UCSSEL_2    - Clock Source, SMCLK
    UCA0CTL1 |= UCSSEL_2;

    // Baud Rate 4,000,000, SMCLK 
    UBR00=0x04; UBR10=0x00; UMCTL0=0x00; 

    UCA0MCTL = 0;
    UCA0CTL1 &= ~UCSWRST;

    P1SEL       = BIT1 | BIT2 | BIT4;
    P1SEL2      = BIT1 | BIT2 | BIT4; 
}

void spiSendChar(unsigned char send){
    while(!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = send;
}

unsigned char spiReceiveChar(){
    while(!(IFG2 & UCA0TXIFG));
    return UCA0RXBUF; 
}
