/*
 * game.h
 *
 *  Created on: Oct 30, 2013
 *      Author: C15Kevin.Cooper
 */

#ifndef GAME_H_
#define GAME_H_

typedef struct{
	int row;
	int height;
} books_t;

typedef struct{
	int x;
	int y;
} player_t;

typedef struct{
	books_t information;
	player_t player;
	char ** boardPtr;
}board_t;




board_t newGameBoard(int sizeX, int sizeY);
void setPosition(board_t * board, char object, int row, int column);
char movDirection(board_t * board, int xDirection, int yDirection);
char * toString(board_t * board);
void freeString( char * string);
int getPlayerPosX(board_t * board);
int getPlayerPosY(board_t * board);
player_t getPlayer(board_t * board);

#endif /* GAME_H_ */
