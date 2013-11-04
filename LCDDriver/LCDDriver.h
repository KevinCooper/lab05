//
// lcd.h
// Author: Todd Branchflower
// Date: 17 October 2013
// Description: Library to interact with the Geek Box LCD.
//

#ifndef LCDDRIVER_H_
#define LCDDRIVER_H_

#define LCDCON 1

/*
 * Author: Kevin Cooper
 * Function: Initializes the SPi communication on the MSP430
 * Inputs: None
 */
void initSPI();

/*
 * Author: Kevin Cooper
 * Function: Initializes the LCD screen and should blank it in the process.  Uses P1.4-1.7 to communicate.
 * Inputs: None
 */
void LCDinit();

/*
 * Author: Kevin Cooper
 * Function: Clears the LCD screen
 * Inputs: None
 */
void LCDclear();

/*
 * Author: Kevin Cooper
 * Function: Moves the character pointer to the second line
 * Inputs: None
 */
void cursorToLineTwo();

/*
 * Author: Kevin Cooper
 * Function: Moves the character pointer to the first line
 * Inputs: None
 */
void cursorToLineOne();

/*
 * Author: Kevin Cooper
 * Function: Writes the given character to the screen and increments the cursor.
 * Inputs: Character asciiChar that should be written
 */
void writeChar(char asciiChar);

/*
 * Author: Kevin Cooper
 * Function: Writes the given string to the LCD screen, if it is greater than eight characters long, then the second eight characters will be written to the second line.  Any characters after sixteen will not be written to the screen.
 * Inputs: String to be written
 */
void writeString(char * string);
/*
 * Author: Kevin Cooper
 * Function: Writes the given strings to the top and bottom line respectively.  Will not wrap the text.
 * Inputs: String to be written to top line, string to be written to bottom line
 */
void writeStringTwo(char * string1, char * string2);

/*
 * Author: Kevin Cooper
 * Function: Scrolls the first given string screen to the left on the top line at a rate of five characters per second.  Scrolls the second given string to the left on the bottom line at a rate of five characters per second.
 * Inputs: String1 to scroll across the top line, String2 to scroll across the bottom line.
 */
void scrollString(char * string1, char * string2);

#endif /* LCDDRIVER_H_ */
