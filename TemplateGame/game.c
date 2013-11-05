/*
 * game.c
 *
 *  Created on: Oct 30, 2013
 *      Author: C15Kevin.Cooper
 */

#include "game.h"
#include <stdlib.h>

#define DATA_SIZE 1   //Size of the char type
#define START_X 0
#define START_Y 0
#define BLANK ' '

char getPosition(board_t * board, int row, int column);

board_t newGameBoard(int sizeX, int sizeY)
{
	int i;
	int j;
	board_t temp;
	temp.information.height = sizeY;
	temp.information.row = sizeX;

	//Set up the 2d array for use later
	temp.boardPtr = malloc(temp.information.height * DATA_SIZE);
	for (i = 0; i < temp.information.height; i++) {
		temp.boardPtr[i] = malloc(temp.information.row * DATA_SIZE);
	}

	//Referenced the following link to better understand how 2d arrays work with pointers in C
	//http://stackoverflow.com/questions/3911400/passing-2d-arrays

	//Initialize a blank board
	for (i = 0; i < temp.information.height; i++)
		for (j = 0; j < temp.information.row; j++)
			temp.boardPtr[i][j] = BLANK;

	//Set up the player
	temp.player.x = START_X;
	temp.player.y = START_Y;

	return temp;
}

void setPosition(board_t * board, char object, int row, int column)
{
	board->boardPtr[row][column] = object;
}

char getPosition(board_t * board, int row, int column)
{
	return board->boardPtr[row][column];
}

char movDirection(board_t * board, char xDirection, char yDirection)
{
	if (board->player.x + xDirection < board->information.row
			&& board->player.y + yDirection < board->information.height
			&& (getPosition(board, board->player.x + xDirection,
					board->player.y + yDirection) == BLANK)) {
		board->player.x += xDirection;
		board->player.y += yDirection;
		return 1;
	} else {
		return 0;
	}
}

char * toString(board_t * board)
{
	int i;
	int j;
	char * string = malloc(board->information.height * board->information.row);

	for (i = 0; i < board->information.height; i++)
		for (j = 0; i < board->information.row; j++)
			string[i * board->information.row + j] = board->boardPtr[i][j];

	return string;
}

int getPlayerPosX(board_t * board)
{
	return board->player.x;
}

int getPlayerPosY(board_t * board)
{
	return board->player.y;
}

player_t getPlayer(board_t * board)
{
	return board->player;
}

