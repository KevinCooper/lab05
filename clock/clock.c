/*
 * clock.c
 *
 *  Created on: Oct 25, 2013
 *      Author: C15Kevin.Cooper
 */

#include <msp430.h>

#define CLEAR_CLOCK 0x00
#define SPEED_1MHZ 0x01
#define SPEED_8MHZ 0x08
#define SPEED_16MHZ 0x16

void setFrequency(char speed)
{
	DCOCTL = CLEAR_CLOCK;
	switch (speed) {
	case SPEED_1MHZ:
		BCSCTL1 = CALBC1_1MHZ;
		DCOCTL = CALDCO_1MHZ;
		break;
	case SPEED_8MHZ:
		BCSCTL1 = CALBC1_8MHZ;
		DCOCTL = CALDCO_8MHZ;
		break;
	case SPEED_16MHZ:
		BCSCTL1 = CALBC1_16MHZ;
		DCOCTL = CALDCO_16MHZ;
		break;
	}

}

