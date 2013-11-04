/*
 * LCDDriver.c
 *
 *  Created on: Oct 23, 2013
 *      Author: C15Kevin.Cooper
 */

#include <msp430.h>

#define RS_MASK 0x40
#define TRUE 1
#define FALSE 0
#define NULL_BYTE 0x00
#define SCREEN_LENGTH 8

void SPI_send(char byteToSend);
void writeCommandByte(char commandByte);
void writeDataByte(char dataByte);
void writeCommandNibble(char commandNibble);
void LCD_write_8(char byteToSend);
void LCD_write_4(unsigned char nibbleToSend);
void delayMilli();
void delayMicro();
void set_SS_lo();
void set_SS_hi();
void delayHundred();

char LCDCON = 0x00;
short unsigned int position;

/*
 * Author: Todd Branchflower
 */
void LCDinit()
{
	writeCommandNibble(0x03);

	writeCommandNibble(0x03);

	writeCommandNibble(0x03);

	writeCommandNibble(0x02);

	writeCommandByte(0x28);

	writeCommandByte(0x0C);

	writeCommandByte(0x01);

	writeCommandByte(0x06);

	writeCommandByte(0x01);

	writeCommandByte(0x02);

	SPI_send(0);
	delayMicro();
	position = 0; // Set up the position for the write bytes
}
/*
 * Author: Todd Branchflower
 */
void writeCommandNibble(char commandNibble)
{
	LCDCON &= ~RS_MASK;
	LCD_write_4(commandNibble);
	delayMilli();
}
/*
 * Author: Todd Branchflower
 */
void writeCommandByte(char commandByte)
{
	LCDCON &= ~RS_MASK;
	LCD_write_8(commandByte);
	delayMilli();
}
/*
 * Author: Todd Branchflower
 */
void writeDataByte(char dataByte)
{
	LCDCON |= RS_MASK;
	LCD_write_8(dataByte);
	delayMilli();
}
/*
 * Author: Todd Branchflower
 */
void LCD_write_8(char byteToSend)
{
	unsigned char sendByte = byteToSend;
	sendByte &= 0xF0;
	sendByte = sendByte >> 4;               // rotate to the right 4 times
	LCD_write_4(sendByte);
	sendByte = byteToSend;
	sendByte &= 0x0F;
	LCD_write_4(sendByte);
}

void LCD_write_4(unsigned char nibbleToSend)
{
	nibbleToSend &= 0x0F; //Clear upper half
	nibbleToSend |= LCDCON; //Set LCD control
	nibbleToSend &= 0x7f; //Set E low
	SPI_send(nibbleToSend);
	delayMicro();
	nibbleToSend |= 0x80;
	SPI_send(nibbleToSend);
	delayMicro();
	nibbleToSend &= 0x7f;
	SPI_send(nibbleToSend);
	delayMicro();

}

void delayMilli()
{
	__delay_cycles(1650); //Delay 1.65 ms
}

void delayMicro()
{
	__delay_cycles(45);  //Delay 40.5 micro seconds
}

void delayHundred()
{
	__delay_cycles(200000);  //Delay 200 milli seconds
}
/*
 * Author: Todd Branchflower
 */
void SPI_send(char byteToSend)
{
	volatile char readByte;

	set_SS_lo();

	UCB0TXBUF = byteToSend;

	while (!(UCB0RXIFG & IFG2)) {
		// wait until you've received a byte
	}

	readByte = UCB0RXBUF;

	set_SS_hi();
}

void set_SS_lo()
{
	P1OUT &= ~( BIT4);
}

void set_SS_hi()
{
	P1OUT |= BIT4;
}
/*
 * Author: Kevin Cooper
 */
void initSPI()
{
	UCB0CTL1 |= UCSWRST; //select a clock to use!
	UCB0CTL0 |= UCCKPL | UCMSB | UCMST | UCSYNC;
	UCB0CTL1 |= UCSSEL1;
	UCB0STAT |= UCLISTEN;  //enables internal loopback
	P1SEL |= BIT5;  //make UCB0CLK available on P1.5
	P1SEL2 |= BIT5;
	P1DIR |= BIT4;  //Set up P1.4 to be out SS output
	P1SEL |= BIT7;  //make UCB0SSIMO available on P1.7 ; = MOSI
	P1SEL2 |= BIT7;
	P1SEL |= BIT6; //make UCB0SSOMI available on P1.6; = MISO
	P1SEL2 |= BIT6;
	UCB0CTL1 &= ~UCSWRST; //enable subsystem
}

void cursorToLineTwo()
{
	writeCommandByte(0xA8); // Remember to take out magic number
}

void cursorToLineOne()
{
	writeCommandByte(0x80); // Remember to take out magic number
}

void LCDclear()
{
	writeCommandByte(0x01); // Remember to take out magic number
}

void writeChar(char asciiChar)
{
	writeDataByte(asciiChar);
}

void writeString(char * string)
{
	int i;
	for (i = 0; i < SCREEN_LENGTH * 2; i++) {
		if (i == 8) {
			cursorToLineTwo();
		}
		writeChar(string[i]);
	}
}
void writeStringTwo(char * string1, char * string2)
{
	int i;
	for (i = 0; i < SCREEN_LENGTH; i++)
		writeChar(string1[i]);
	cursorToLineTwo();
	for (i = 0; i < SCREEN_LENGTH; i++)
		writeChar(string2[i]);
}
void scrollString(char * string1, char * string2)
{
	int i;
	char* iterString1 = string1;
	char* iterString2 = string2;
	while (TRUE) {
		LCDclear();
		if (*(iterString1 + SCREEN_LENGTH) == NULL_BYTE)
			iterString1 = string1;
		if (*(iterString2 + SCREEN_LENGTH) == NULL_BYTE)
			iterString2 = string2;
		writeStringTwo(iterString1, iterString2);
		delayHundred();
		iterString1++;
		iterString2++;
	}
}
