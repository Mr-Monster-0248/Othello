#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "../headers/game_functions.h"
#include "../headers/save_states.h"
#include "../headers/display.h"
#include "../headers/settings.h"
#include "../headers/AI.h"


int main(int argc, char** argv)
{
	int boardSize = 8, skipP1 = 1, skipP2 = 1, round = 0, useDefaultSettings = 0, useAI = 0;
	char **gameBoard = NULL, player1Symbol = 'x', player2Symbol = 'o';

	//Displaying the start screen
	useDefaultSettings = startScreen(); 

	//Asking if playing against the IA
	useAI = ask_AI();



	if (!useDefaultSettings)
	{
		boardSize = askBoardWidth();

		//Asking symbols for each players
		get_player_symbols(&player1Symbol, &player2Symbol);
	}

	gameBoard = init_game_board(boardSize, player1Symbol, player2Symbol);

	//From now, boardSize will be the maximum index of the board, so we decrease it
	boardSize--;
	

	clear();

	if (useAI == 0)
		while(skipP1 || skipP2)
		{
			//Player1 turn's to play
			skipP1 = new_round(&gameBoard, boardSize, player1Symbol, player2Symbol, ++round);

			//Player2 turn's to play
			skipP2 = new_round(&gameBoard, boardSize, player2Symbol, player1Symbol, ++round);
		}
	else
		while (skipP1 || skipP2)
		{
			//Player's turn
			skipP1 = new_round(&gameBoard, boardSize, player1Symbol, player2Symbol, ++round);

			//AI's turn
			skipP2 = new_round_AI(&gameBoard, boardSize, player2Symbol, player1Symbol, ++round);
		}

	set_console(23, 100);

	disp_center("Too bad! Draw game!", 12, 100);

	center_press_any_key(15, 100);

	set_text_color(10);

	for (round = 0; round <= boardSize; round++)
		free(gameBoard[round]);
	free(gameBoard);

	return 0;
}
