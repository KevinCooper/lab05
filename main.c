#include <msp430.h> 
#include "LCDDriver/LCDDriver.h"
#include "TemplateGame/game.h"
#include "clock/clock.h"
/*
 * main.c
 */
void setup();

char flag;


int main(void) {
	setup();
	int counter;

    while (1) {
    	switch(flag){
    	case BIT0:
    		counter=0;//Also clear the clock!
    	case BIT1:
    		counter=0;
    	case BIT2:
    		counter=0;
    	case BIT3:
    		counter=0;
    	case BIT4:
    		counter++;
    	}
    }
    return 0;
}

void setup(){
    WDTCTL = WDTPW|WDTHOLD;                 // stop the watchdog timer
    P1DIR &= ~(BIT0|BIT1|BIT2|BIT3);                // set buttons to input
    P1IE |= BIT0|BIT1|BIT2|BIT3;                 // enable the interrupts
    P1IES |= BIT0|BIT1|BIT2|BIT3;                   // configure interrupt to sense falling edges
    P1REN |= BIT0|BIT1|BIT2|BIT3;                   // enable internal pull-up/pull-down network
    P1OUT |= BIT0|BIT1|BIT2|BIT3;                   // configure as pull-up
    P1IFG &= ~(BIT0|BIT1|BIT2|BIT3);                // clear flags
    __enable_interrupt();



    TACTL &= ~(MC0|MC1);			//Stop the clock
    TACTL |= TACLR;					//Reset it back to 0
    TACTL |= TASSEL1;				//Set to SMCLK
    TACTL |= ID0|ID1;				//Set the clock to 125MHZ
    TACTL &= ~TAIFG;				//Clear out the flaf
    TACTL |= MC1;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1_ISR(void)
{

    if (P1IFG & BIT0)
    {
        P1IFG &= ~BIT0;                            // clear flag
        flag |= BIT0;
    }
    if (P1IFG & BIT1)
    {
        P1IFG &= ~BIT1;                            // clear flag
        flag |= BIT1;
    }

    if (P1IFG & BIT2)
    {
        P1IFG &= ~BIT2;                         // clear flag
        flag |= BIT2;
    }

    if (P1IFG & BIT3)
    {
        P1IFG &= ~BIT3;                         // clear
        flag |= BIT3;
    }
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(){
	flag |= BIT4;
}
