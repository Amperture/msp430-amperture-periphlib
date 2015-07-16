// Header Includes
#include <msp430g2553.h>
#include "uart.h"


//GPIO Definitions
#define TXLED BIT0
#define RXLED BIT6
#define TXD BIT2
#define RXD BIT1


//Mailboxes and flags for RX and TX
volatile unsigned char txFlag;
volatile unsigned char txChar;
volatile unsigned char rxFlag;
volatile unsigned char txFlag;


void uartInit(void){
    // Select DCO and MODx settings. Set MCLK to 1MHZ
    //   Remember, 1,000,000 Hz clock cycle.
    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    // Setup the GPIO
    //  P1.1 = RXD
    //  P1.2 = TXD 
    P1SEL |= RXD + TXD;
    P1SEL2 |= RXD + TXD;
    P1DIR = TXLED + RXLED;
    P1OUT &= ~(TXLED + RXLED);

    //Setup the Baud Rate
    // For now, we hard code to 9600 baud.
    // TODO: User-Definable Baud Rate.
    UCA0CTL1 |= UCSSEL_2;       // UART clock attached to SMCLK

    UCA0BR0 = 104;              // 1MHz / 9600 = 104.166666...
    UCA0BR1 = 0;

    UCA0MCTL = UCBRS0; // UCBRSx = 1, UCBRFx = 0

    UCA0CTL1 &= ~UCSWRST;
    __bix_SR_register(GIE);
}
    
void uartSendChar(char toSend){
    txChar = toSend;
    IE2 |= UCA0TXIE;
    while (txFlag == 1); 
    txFlag = 1;
}

void uartSendString(char *toSend){
    while(*toSend){
        *toSend++;
    }
}

static void
__attribute__((__interrupt__(USCIAB0TX_VECTOR)))
USCI0TX_ISR(void){ // TX Interrupt Handler
    // Turn on TX LED.
    P1OUT |= TXLED;

    // Place mailbox byte into buffer.
    UCA0TXBUF = txChar;

    // Lower the mailbox flag
    txFlag = 0;

    //Disable TX Interrupt
    IE2 &= ~(UCA0TXIE);

    // Turn off TX LED.
    P1OUT &= ~(TXLED);
}

static void
__attribute__((__interrupt__(USCIAB0RX_VECTOR)))
USCI0RX_ISR(void){ // RX Interrupt Handler
    P1OUT |= RXLED;
    rxChar = UCA0RXBUF;
    rxFlag = 1; 
    P1OUT &= ~RXLED;
}


