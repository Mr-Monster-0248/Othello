#ifndef DEF_AI_H
	#define DEF_AI_H
	
	//Function that returns the coordinates of the pawn chosen by the AI
	int* get_AI_coordinates(int** movesList, int numberMoves);

	//Function that returns 1 if the player wants to play against the AI, 0 if not
	int ask_AI();

	//Function that starts a new round, returns 1 if a pawn has been placed, 0 if not
	int new_round_AI(char*** gameBoard, int size, char playerSymbol, char opposingSymbol, int round);
#endif