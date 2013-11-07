#include <msp430.h> 
#include "LCDDriver/LCDDriver.h"
#include "TemplateGame/game.h"
#include "clock/clock.h"
#include "msp430-rng/rand.h"

#define BUTTON_1 1
#define BUTTON_2 2
#define BUTTON_3 3
#define BUTTON_4 4
#define CLOCK 10

void setup();
void clearTimer();
void updateBoard(board_t myGame);
void buildBombs(board_t myGame);
void makeHarder(board_t * myGame);

char flag;
short int status;
char gameset;

int main(void)
{
	gameset = 0;
	WDTCTL = WDTPW | WDTHOLD;                 // stop the watchdog timer
	setFrequency(SPEED_1MHZ);
	initSPI();
	LCDinit();
	LCDclear();
	status = 1;
	board_t myGame = newGameBoard(8, 2);
	buildBombs(myGame);		//2 min 19 sec
	updateBoard(myGame);
	int counter = 0;
	flag = 0;
	char hard = 0;
	int result = 0; //Determines what should happen based on the movement made

	setup();

	while (1) {
		if (flag)
		{
			switch (flag) {
				case BUTTON_1:
					clearTimer();
					counter = 0;
					hard = 0;
					result = movDirection(&myGame, 1, 0);
					updateBoard(myGame);
					break;
				case BUTTON_2:
					clearTimer();
					hard = 0;
					counter = 0;
					result = movDirection(&myGame, -1, 0);
					updateBoard(myGame);
					break;
				case BUTTON_3:
					clearTimer();
					counter = 0;
					hard = 0;
					result = movDirection(&myGame, 0, -1);
					updateBoard(myGame);
					break;
				case BUTTON_4:
					clearTimer();
					counter = 0;
					hard = 0;
					result = movDirection(&myGame, 0, 1);
					updateBoard(myGame);
					break;
				case CLOCK:
					counter++;
					break;
			}
			flag = 0;
		}
		if (counter != 0 && hard == 0) {
			makeHarder(&myGame);
			updateBoard(myGame);
			hard = 1;
		}

		if (counter == 4) {
			LCDclear();
			writeStringTwo("  LOSE  ", "        ");
			while (1) {
				gameset = 1;
			}
		}
		if (result == 2) {
			LCDclear();
			writeStringTwo(" !BOOM! ", "        ");
			while (1) {
				gameset = 1;
			}
		}
		if (myGame.player.x == myGame.information.row - 1
				&& myGame.player.y == myGame.information.height - 1) {
			LCDclear();
			writeStringTwo("  WIN   ", "        ");
			while (1) {
				gameset = 1;
			}
		}
	}
}

void makeHarder(board_t * myGame)
{
	const char bomb = '*';
	const char blank = ' ';
	int row = 0, column = 0;
	for (row = 0; row < myGame->information.height; row++) {
		for (column = 0; column < myGame->information.row; column++) {
			if (getPosition(myGame, row, column) == '*') {
				setPosition(myGame, bomb, row, column + status);
				if (myGame->player.x == column + status
						&& myGame->player.y == row) {
					LCDclear();
					writeStringTwo(" !BOOM! ", "        ");
					while (1) {
					gameset=1;
					};
				}
				setPosition(myGame, blank, row, column);
				break;
			}
		}
	}
	status *= -1;
}
void buildBombs(board_t myGame)
{
//unsigned int state = rand();
	int spaceBottom = 1; //prand(state) == 2874
	int spaceTop = 2874 % 3 + 1; //top is between 1-3
	if (2874 % 2 == 0) {
		spaceBottom = spaceTop + (2874 % 2 + 2);
	} else {
		spaceBottom = spaceTop - (2874 % 2 + 2);
	}
	const char bomb = '*';
	setPosition(&myGame, bomb, 0, spaceTop);
	setPosition(&myGame, bomb, 1, spaceBottom);
}

void updateBoard(board_t myGame)
{
	LCDclear();
	char * boardString = toString(&myGame);
	writeString(boardString);
	freeString(boardString);
}

void setup()
{
	P1DIR &= ~(BIT0 | BIT1 | BIT2 | BIT3);               // set buttons to input
	P1REN |= BIT0 | BIT1 | BIT2 | BIT3; // enable internal pull-up/pull-down network
	P1OUT |= BIT0 | BIT1 | BIT2 | BIT3;                  // configure as pull-up
	P1IES |= BIT0 | BIT1 | BIT2 | BIT3; // configure interrupt to sense falling edges
	P1IFG &= ~(BIT0 | BIT1 | BIT2 | BIT3);                // clear flags
	P1IE |= BIT0 | BIT1 | BIT2 | BIT3;                 // enable the interrupts

	TACTL &= ~(MC0 | MC1);			//Stop the clock
	TACTL |= TACLR;					//Reset it back to 0
	TACTL |= TASSEL1;				//Set to SMCLK
	TACTL |= ID0 | ID1;				//Set the clock to 125MHZ
	TACTL &= ~TAIFG;				//Clear out the flag
	TACTL |= MC1;					//Continuous mode
	TACTL |= TAIE;  				//Enable the interrupt
	__enable_interrupt();
}

void clearTimer()
{
	TACTL |= TACLR;
}

void debounce()
{
	__delay_cycles(1000);  //Delay 1ms
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1_ISR(void)
{
	__disable_interrupt();
	if (gameset) {
		gameset = 0;
		WDTCTL = 0x0011;
	}
	if (P1IFG & BIT0) {
		if (BIT0 & P1IES) {
			flag = BUTTON_1;
		} else {
			debounce();
		}
		P1IES ^= BIT0;
		P1IFG &= ~BIT0;
	} else if (P1IFG & BIT1) {
		if (BIT1 & P1IES) {
			flag = BUTTON_2;
		} else {
			debounce();
		}
		P1IES ^= BIT1;
		P1IFG &= ~BIT1;
	}

	if (P1IFG & BIT2) {
		if (BIT2 & P1IES) {
			flag = BUTTON_3;
		} else {
			debounce();
		}
		P1IES ^= BIT2;
		P1IFG &= ~BIT2;
	}

	if (P1IFG & BIT3) {
		if (BIT3 & P1IES) {
			flag = BUTTON_4;
		} else {
			debounce();
		}
		P1IES ^= BIT3;
		P1IFG &= ~BIT3;
	}
	__enable_interrupt();
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR()
{
	TACTL &= ~TAIFG;
	flag = CLOCK;
}
