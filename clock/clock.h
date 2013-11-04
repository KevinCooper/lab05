/*
 * clock.h
 *
 *  Created on: Oct 25, 2013
 *      Author: C15Kevin.Cooper
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#define SPEED_1MHZ 0x01
#define SPEED_8MHZ 0x08
#define SPEED_16MHZ 0x16

/*
 * Author: Kevin Cooper
 * Function: Set the clock frequency to the given speed
 * Inputs: SPEED_1MHZ, SPEED_8MHZ, or SPEED_16MHZ
 */
void setFrequency(char speed);

#endif /* CLOCK_H_ */
