##LCDDriver by Kevin Cooper
<br>
###Description
<br>
This is a driver for the MSP430 to interface with an LCD screen.  The available functions are:<br>
<br>
<br>
Initializes the SPi communication on the MSP430<br>
`void initSPI()`

Initializes the LCD screen and should blank it in the process.<br>
`void LCDinit()`

Clears the LCD screen<br>
`void LCDclear()`

Moves the character pointer to the first line<br>
`void cursorToLineOne()`

Moves the character pointer to the second line<br>
`void cursorToLineTwo()`

Writes the given character to the screen and increments the cursor.<br>
`void writeChar(char asciiChar)`

Writes the given string to the LCD screen, if it is greater than eight characters long, then the second eight characters will be written to the second line.  Any characters after sixteen will not be written to the screen.<br>
`writeString(char * string)`

Writes the given strings to the top and bottom of the LCD screen respectively.  Will not auto wrap.<br>
`writeString(char * string1, char * string2)`

Scrolls the first given string screen to the left on the top line at a rate of five characters per second.  Scrolls the second given string to the left on the bottom line at a rate of five characters per second.<br>
`scrollString(char * string1, char * string2)`

