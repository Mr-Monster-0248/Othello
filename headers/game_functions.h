#ifndef DEF_GAME_FUNCTIONS_H
	#define DEF_GAME_FUNCTIONS_H

	//Function that inits the game board and returns a pointer on it
	char** init_game_board(int size, char player1Char, char player2Char);

	//Function that returns the number of pawns capturable for a given position
	void check_directions(char** gameBoard, int size, char playerSymbol, int currentX, int currentY);

	//Function that returns the number of moves available and a list of moves available
	int available_moves(char** gameBoard, int size, char playerSymbol, int*** movesList);

	//Function that shows the playable cases
	void show_hints(char** gameBoard, int size, int** moves, int numberMoves);

	//Function that changes the symbol of all captured pawns
	void capture_pawns(char*** gameBoard, int size, int xCoord, int yCoord, char playerChar);

	//This function places a pawn on the game board, returns 0 if the given coordinates are not correct
	int place_pawn(char*** gameBoard, int size, int **availableMoves, int moves, char playerChar, int round);

	//Function that asks for coordinates and convers alphabets to integer coordinates
	void get_coordinates(int* xCoord, int* yCoord, int size);

	//Function that starts a new round, returns 1 if a pawn has been placed, 0 if not
	int new_round(char*** gameBoard, int size, char playerSymbol, char opposingSymbol, int round);

#endif