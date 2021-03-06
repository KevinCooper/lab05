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

board_t newGameBoard(int sizeX, int sizeY)
{
	int i;
	int j;
	board_t temp;
	temp.information.height = sizeY;
	temp.information.row = sizeX;

	//Set up the 2d array for use later
	temp.boardPtr = malloc(temp.information.height * sizeof(char *));
	for (i = 0; i < temp.information.height; i++) {
		temp.boardPtr[i] = malloc(temp.information.row * sizeof(char));
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

int movDirection(board_t * board, int xDirection, int yDirection)
{
	if (board->player.x + xDirection < board->information.row
			&& board->player.x + xDirection >= 0
			&& board->player.y + yDirection < board->information.height
			&& board->player.y + yDirection >= 0) {
		if ((getPosition(board, board->player.y + yDirection,
				board->player.x + xDirection) == BLANK)) {
			board->player.x += xDirection;
			board->player.y += yDirection;
			return 1;  //Good move
		} else {
			return 2; //Hit something bad
		}
	} else {
		return 0;  //Hit some wall
	}
}

char * toString(board_t * board)
{
	int i;
	int j;
	char * string = malloc(board->information.height * board->information.row);

	for (i = 0; i < board->information.height; i++)
		for (j = 0; j < board->information.row; j++)
			if (board->player.x == j && board->player.y == i) {
				string[i * board->information.row + j] = 'p';
			} else {
				string[i * board->information.row + j] = board->boardPtr[i][j];
			}

	return string;
}

void freeString(char * string)
{
	free(string);
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

