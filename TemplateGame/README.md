#Description
This is an implementation of a general purpose game board.
##Functions
Returns a board type that is X wide and Y high.  The player position is initially set to 0,0 on the board and everything else is set to null or empty<br>
`board_t newGameBoard(int sizeX, int sizeY)`

Sets the position on the gameboard to the char type<br>
`void setPosition(board_t * board, char object, int row, int column)`

Attempts to move the player in X/Y direction. Diagonal and moves greater than distance 1 are not supported.<br>
--returns zero if the move was made with no errors<br>
--returns one if the player tried to move out of bounds, no move made<br>
--returns two if the player hit an object, no move made
`char movDirection(board_t * board, char xDirection, char yDirection)`

Returns a pointer to a single string that represents the board <br>
`char * toString(board_t * board)`

Returns the X position of the player.<br>
`int getPlayerPosX(board_t * board)`

Return the Y position of the player.<br>
`int getPlayerPosY(board_t * board)`

Return the player object that the board is maintaining.<br>
`player_t getPlayer(board_t * board)`

Free the string that was previously made with toString. This is IMPORTANT.<br>
`void freeString( char * string)`
