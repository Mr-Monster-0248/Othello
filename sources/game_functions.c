#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "../headers/save_states.h"
#include "../headers/settings.h"
#include "../headers/display.h"

#define EMPTY_CASE 46

//Function that inits the game board and returns a pointer on it
char** init_game_board(int size, char player1Char, char player2Char) //OK
{
	int i = 0, j = 0;
	char** gameBoard = NULL;

	gameBoard = (char**) malloc(size++ * sizeof(char*));
	check_alloc(gameBoard);

	for (i = 0; i < size; i++)
	{
		gameBoard[i] = (char*) malloc((size) * sizeof(char));
		check_alloc(gameBoard[i]);

		for (j = 0; j < size; j++)
			gameBoard[i][j] = EMPTY_CASE;

		gameBoard[i][j] = '\0';

	}


	//Setting the starting pawns for player x
	gameBoard[(size / 2) - 1][(size / 2) - 1] = player1Char;
	gameBoard[size / 2][size / 2] = player1Char;

	//Setting the starting pawns for player o
	gameBoard[size / 2][(size / 2) - 1] = player2Char;
	gameBoard[(size / 2) - 1][size / 2] = player2Char;


	return gameBoard;
}

//Function that returns the number of pawns capturable for a given position, size is the highest index
int check_directions(char** gameBoard, int size, char playerSymbol, int currentX, int currentY) //OK
{
	int i = 0, j = 0, exploreX = 0, exploreY = 0, pawns = 0, potentials = 0;

	/*-------------------------------------------------------
	|														|
	|	TENTATIVE DE VERIFICATION COMMUNE A TOUS LES CAS 	|	Ca devrait marcher, mais je suis pas sûr
	|														|
	-------------------------------------------------------*/

	for (i = currentY - 1; i <= currentY + 1; i++)
	{
		if (i < 0 || i > size) //If the case is not in the game board, skipping a loop
			continue;

		for (j = currentX - 1; j <= currentX + 1; j++)
		{
			if (j < 0 || j > size || (i == currentY && j == currentX) ) //If the case is not in the game board or is the center of the analyzed square, skipping a loop
				continue;

			//If adverse player symbol is found
			if (gameBoard[i][j] != playerSymbol && gameBoard[i][j] != EMPTY_CASE)
			{
				//Getting the coordinates for the begin of the analyze
				exploreX = j;
				exploreY = i;

				potentials = 0; //Number of potential capturable pawns


				//UP LEFT direction
				if (i == currentY - 1 && j == currentX - 1)
				{
					while (exploreX >= 0 && exploreY >= 0)
					{
						if (gameBoard[exploreY][exploreX] != playerSymbol && gameBoard[exploreY][exploreX] != EMPTY_CASE)
							potentials++;

						if (gameBoard[exploreY][exploreX] == playerSymbol)
						{
							pawns += potentials;
							break;
						}

						if (gameBoard[exploreY][exploreX] == EMPTY_CASE)
							break;

						exploreX--;
						exploreY--;
					}

					continue; //Skipping all other possibilities
				}


				//UP direction
				if (i == currentY - 1 && j == currentX)
				{
					while (exploreY >= 0)
					{
						if (gameBoard[exploreY][exploreX] != playerSymbol && gameBoard[exploreY][exploreX] != EMPTY_CASE)
							potentials++;

						if (gameBoard[exploreY][exploreX] == playerSymbol)
						{
							pawns += potentials;
							break;
						}

						if (gameBoard[exploreY][exploreX] == EMPTY_CASE)
							break;
						exploreY--;
					}

					continue; //Skipping all other possibilities
				}


				//UP RIGHT direction
				if (i == currentY - 1 && j == currentX + 1)
				{
					while (exploreX <= size && exploreY >= 0)
					{
						if (gameBoard[exploreY][exploreX] != playerSymbol && gameBoard[exploreY][exploreX] != EMPTY_CASE)
							potentials++;

						if (gameBoard[exploreY][exploreX] == playerSymbol)
						{
							pawns += potentials;
							break;
						}

						if (gameBoard[exploreY][exploreX] == EMPTY_CASE)
							break;

						exploreX++;
						exploreY--;
					}

					continue; //Skipping all other possibilities
				}


				//LEFT direction
				if (i == currentY && j == currentX - 1)
				{
					while (exploreX >= 0)
					{
						if (gameBoard[i][exploreX] != playerSymbol && gameBoard[i][exploreX] != EMPTY_CASE)
							potentials++;

						if (gameBoard[i][exploreX] == playerSymbol)
						{
							pawns += potentials;
							break;
						}

						if (gameBoard[i][exploreX] == EMPTY_CASE)
							break;

						exploreX--;
					}

					continue; //Skipping all other possibilities
				}


				//RIGHT direction
				if (i == currentY && j == currentX + 1)
				{
					while (exploreX <= size)
					{
						if (gameBoard[i][exploreX] != playerSymbol && gameBoard[i][exploreX] != EMPTY_CASE)
							potentials++;

						if (gameBoard[i][exploreX] == playerSymbol)
						{
							pawns += potentials;
							break;
						}

						if (gameBoard[i][exploreX] == EMPTY_CASE)
							break;

						exploreX++;
					}

					continue; //Skipping all other possibilities
				}


				//DOWN LEFT direction
				if (i == currentY + 1 && j == currentX - 1)
				{
					while (exploreX >= 0 && exploreY <= size)
					{
						if (gameBoard[exploreY][exploreX] != playerSymbol && gameBoard[exploreY][exploreX] != EMPTY_CASE)
							potentials++;

						if (gameBoard[exploreY][exploreX] == playerSymbol)
						{
							pawns += potentials;
							break;
						}

						if (gameBoard[exploreY][exploreX] == EMPTY_CASE)
							break;

						exploreX--;
						exploreY++;
					}

					continue; //Skipping all other possibilities
				}

				//DOWN direction
				if (i == currentY + 1 && j == currentX)
				{
					while (exploreY <= size)
					{
						if (gameBoard[exploreY][exploreX] != playerSymbol && gameBoard[exploreY][exploreX] != EMPTY_CASE)
							potentials++;

						if (gameBoard[exploreY][exploreX] == playerSymbol)
						{
							pawns += potentials;
							break;
						}

						if (gameBoard[exploreY][exploreX] == EMPTY_CASE)
							break;

						exploreY++;
					}

					continue; //Skipping all other possibilities
				}


				//DOWN RIGHT direction
				if (i == currentY + 1 && j == currentX + 1)
				{
					while (exploreX <= size && exploreY >= 0)
					{
						if (gameBoard[exploreY][exploreX] != playerSymbol && gameBoard[exploreY][exploreX] != EMPTY_CASE)
							potentials++;

						if (gameBoard[exploreY][exploreX] == playerSymbol)
						{
							pawns +=  potentials;
							break;
						}

						if (gameBoard[exploreY][exploreX] == EMPTY_CASE)
							break;

						exploreX++;
						exploreY++;
					}

					continue; //Skipping all other possibilities
				}
			}


		} //End of x axis for loop


	} //End of y axis for loop

	return pawns;
}


//Function that returns the number of moves available and a list of moves available
int available_moves(char** gameBoard, int size, char playerSymbol, int*** movesList) //OK
{
	int i = 0, j = 0, moves = 0, positionMoves = 0;

	if (*movesList)
		free(*movesList);

	*movesList = (int**) malloc(sizeof(int*));
	check_alloc(*movesList);

	for (i = 0; i < size; i++) //Exploring all y axis except the most right and left values
		for (j = 0; j < size; j++) //Exploring all x axis except the most right and left values
			if ( gameBoard[i][j] == EMPTY_CASE ) //If one of the player's pawns has been found at this location
			{
				//Counting the number of moves for this position
				positionMoves = check_directions(gameBoard, size + 1, playerSymbol, j, i);

				if (positionMoves)
				{
					*movesList = (int**) realloc(*movesList, ++moves * sizeof(int*));
					check_alloc(*movesList);

					(*movesList)[moves - 1] = (int*) calloc(3, sizeof(int));
					check_alloc( (*movesList)[i] );

					(*movesList)[moves - 1][0] = j; //Storing the x position
					(*movesList)[moves - 1][1] = i; //Storing the y position
					(*movesList)[moves - 1][2] = positionMoves; //Storing the number of captured pawns for this position
					
				}
			}

	return moves;
}


//Function that shows the playable cases
void show_hints(char** gameBoard, int size, int** moves, int numberMoves) //OK
{
	int i = 0;

	for (i = 0; i < numberMoves; i++)
		print_color(".", 6 + 3*moves[i][1], 3 + moves[i][0], 14, 0); //Displaying the playable cases in yellow

	//Waiting for a keyboard interaction
	set_cursor(1, 1);
	get_pressed_key();

	for (i = 0; i < numberMoves; i++)
		print_color(".", 6 + 3*moves[i][1], 3 + moves[i][0], 0, 15); //Hiding the shown hints
}


//Function that changes the symbol of all captured pawns
void capture_pawns(char*** gameBoard, int size, int xCoord, int yCoord, char playerChar) //OK
{
	int i = 0, j = 0, exploreX = 0, exploreY = 0;

	for (i = yCoord - 1; i <= yCoord + 1; i++)
	{
		//Checking if the coordinates are correct
		if (i < 0 || i >= size)
			continue;

		for (j = xCoord - 1; j <= xCoord + 1; j++)
		{
			//Checking the coordinates before trying anything to avoid memory dump
			if ( (i == yCoord && j == xCoord) || j < 0 || j >= size )
				continue;

			//Checking UP LEFT direction
			if (i == yCoord - 1 && j == xCoord - 1)
			{
				exploreX = j;
				exploreY = i;

				//Going as far as possible
				while ( exploreX >= 0 && exploreY >= 0 && (*gameBoard)[exploreY][exploreX] != playerChar && (*gameBoard)[exploreY][exploreX] != EMPTY_CASE )
				{
					exploreX--;
					exploreY--;
				}


				//If the program encountered another empty case, doing nothing
				if ( exploreX < 0 || exploreY < 0 || (*gameBoard)[exploreY][exploreX] == EMPTY_CASE )
				{
					continue;
				}


				//If the program encountered one of the player's pawns
				while (exploreY != yCoord)
				{
					(*gameBoard)[exploreY][exploreX] = playerChar; //Capturing the pawn
					exploreX++;
					exploreY++;
				}
			}


			//Checking UP direction
			if (i == yCoord - 1 && j == xCoord)
			{
				exploreY = i;
				exploreX = j;

				//Going as far as possible
				while ( exploreY >= 0 && (*gameBoard)[exploreY][exploreX] != playerChar && (*gameBoard)[exploreY][exploreX] != EMPTY_CASE )
					exploreY--;


				//Checking the last checked case
				if ( exploreY < 0 || (*gameBoard)[exploreY][j] == EMPTY_CASE )
				{
					continue;
				}

				while (exploreY != yCoord)
				{
					(*gameBoard)[exploreY][exploreX] = playerChar;
					exploreY++;
				}
			}


			//Checking UP RIGHT direction
			if (i == yCoord - 1 && j == xCoord + 1)
			{
				exploreY = i;
				exploreX = j;

				//Going as far as possible
				while ( exploreY >= 0 && exploreX <= size && (*gameBoard)[exploreY][exploreX] != playerChar && (*gameBoard)[exploreY][exploreX] != EMPTY_CASE )
				{
					exploreY--;
					exploreX++;
				}


				//Checking the case where the program stopped
				if ( exploreX > size || exploreY < 0 || (*gameBoard)[exploreX][exploreY] == EMPTY_CASE)
				{
					continue;
				}

				//Capturing the pawns
				while (exploreX != xCoord)
				{
					(*gameBoard)[exploreY][exploreX] = playerChar;
					exploreY++;
					exploreX--;
				}
			}


			//Checking LEFT direction
			if (i == yCoord && j == xCoord - 1)
			{
				exploreX = j;
				exploreY = i;

				while (exploreX >= 0 && (*gameBoard)[exploreY][exploreX] != playerChar && (*gameBoard)[exploreY][exploreX] != EMPTY_CASE )
					exploreX--;


				//Checking the case where the program stopped
				if ( exploreX < 0 || (*gameBoard)[exploreY][exploreX] ==  EMPTY_CASE )
				{
					continue;
				}

				//Capturing the pawns
				while ( exploreX != xCoord )
				{
					(*gameBoard)[exploreY][exploreX] = playerChar;
					exploreX++;
				}
			}


			//Checking RIGHT direction
			if (i == yCoord && j == xCoord + 1)
			{
				exploreX = j;
				exploreY = i;

				//Going as far as possible
				while (exploreX <= size && (*gameBoard)[exploreY][exploreX] != playerChar && (*gameBoard)[exploreY][exploreX] != EMPTY_CASE )
					exploreX++;

				
				//Checking the case where the program stopped
				if ( exploreX > size || (*gameBoard)[exploreY][exploreX] ==  EMPTY_CASE )
				{
					continue;
				}

				//Capturing the pawns
				while ( exploreX != xCoord )
				{
					(*gameBoard)[exploreY][exploreX] = playerChar;
					exploreX--;
				}
			}


			//Checking DOWN LEFT direction
			if (i == yCoord + 1 && j == xCoord - 1)
			{
				exploreX = j;
				exploreY = i;

				//Going as far as possible
				while ( exploreX >= 0 && exploreY <= size && (*gameBoard)[exploreY][exploreX] != playerChar && (*gameBoard)[exploreY][exploreX] != EMPTY_CASE )
				{
					exploreY++;
					exploreX--;
				}


				//Checking the case where the program stopped
				if ( exploreX < 0 || exploreY > size || (*gameBoard)[exploreY][exploreX] == EMPTY_CASE )
				{
					continue;
				}

				//Capturing the pawns
				while ( exploreX != xCoord )
				{
					(*gameBoard)[exploreY][exploreX] = playerChar;
					exploreX++;
					exploreY--;
				}
			}


			//Checking DOWN direction
			if (i == yCoord + 1 && j == xCoord)
			{
				exploreY = i;
				exploreX = j;

				//Going as far as possible
				while ( exploreY <= size && (*gameBoard)[exploreY][exploreX] != playerChar && (*gameBoard)[exploreY][exploreX] != EMPTY_CASE )
					exploreY++;


				//Checking the case where the program stopped
				if ( exploreY > size || (*gameBoard)[exploreY][exploreX] == EMPTY_CASE )
				{
					continue;
				}

				//Capturing the pawns
				while (exploreY != yCoord)
				{
					(*gameBoard)[exploreY][exploreX] = playerChar;
					exploreY--;
				}
			}


			//Checking DOWN RIGHT direction
			if (i == yCoord + 1 && j == xCoord + 1)
			{
				exploreY = i;
				exploreX = j;

				//Going as far as possible
				while ( exploreY <= size && exploreX <= size && (*gameBoard)[exploreY][exploreX] != playerChar && (*gameBoard)[exploreY][exploreX] != EMPTY_CASE )
				{
					exploreX++;
					exploreY++;
				}


				//Checking the case where the program stopped
				if ( exploreY > size || exploreX > size || (*gameBoard)[exploreY][exploreX] == EMPTY_CASE )
				{
					continue;
				}

				//Capturing the pawns
				while ( exploreX != xCoord )
				{
					(*gameBoard)[exploreY][exploreX] = playerChar;
					exploreY--;
					exploreX--;
				}
			}

		}
	}
}


//Function that asks for coordinates and convers alphabets to integer coordinates
void get_coordinates(int* xCoord, int* yCoord, int size) //BUG
{
	char readChar = '#';
	do
	{
		clear_buffer();
		*xCoord = -1;
		*yCoord = -1;

		print_xy("Enter the coordinates:              ", 2*size + 9, 2*size + 3);
		set_cursor(2*size + 33, 2*size + 3);

		if (scanf("%c%2d", &readChar, yCoord) != 2)
		{
			clear_buffer();
			continue; //New lap
		}


		*xCoord = (int) readChar;

		//Checking xCoord validity
		if ( *xCoord >= 65 && *xCoord <= (65 + size) ) //UPPERCASE
		{
			*xCoord -= 65;
		}
		else
		{
			if ( *xCoord >= 97 && *xCoord <= (97 + size) ) //LOWERCASE
			{
				*xCoord -= 97;
			}
			else
				continue;
		}


		//Checking yCoord validity
		if ( *yCoord >= 1 && *yCoord <= size )
			(*yCoord)--;
		else
			continue;


	} while (*xCoord == -1 || *yCoord == -1);
}


//This function places a pawn on the game board, returns 0 if the given coordinates are not correct
int place_pawn(char*** gameBoard, int size, int **availableMoves, int moves, char playerChar, int round) //BUG
{
	int xCoord = 0, yCoord = 0, i = 0;
	//char* logLine = (char*) malloc(50 * sizeof(char));

	//check_alloc(logLine);

	get_coordinates(&xCoord, &yCoord, size);

	for (i = 0; i < moves; i++)
		if (availableMoves[i][0] == yCoord && availableMoves[i][1] == xCoord)
		{
			(*gameBoard)[xCoord][yCoord] = playerChar;

			/*//Writing a log line
			sprintf(logLine, "Round %d: %c placed a pawn at %c%d", round, playerChar, xCoord + 65, yCoord+1);

			write_log(logLine, round);

			free(logLine);*/

			capture_pawns(gameBoard, size, yCoord, xCoord, playerChar);

			return 1;
		}

	clear();
	printf("You cannot place a pawn at this coordinates!");
	center_press_any_key(9, 100);
	return 0;
}


//Function that starts a new round, returns 1 if a pawn has been placed, 0 if not
int new_round(char*** gameBoard, int size, char playerSymbol, char opposingSymbol, int round) //To finish
{
	int i = 0, j = 0, pawns[2] = {0}, moves = 0, **movesList = NULL;
	char action;

	//Counting the pawns
	for (i = 0; i <= size; i++)
		for (j = 0; j <= size; j++)
		{
			if ((*gameBoard)[i][j] == playerSymbol)
				pawns[0]++;
			else
				if ((*gameBoard)[i][j] != EMPTY_CASE)
					pawns[1]++;
		}

	moves = available_moves(*gameBoard, size, playerSymbol, &movesList);

	while (1) //Looping until the round is over
	{
		//Displaying the interface so that the player make a choice
		disp_interface(*gameBoard, size, round, playerSymbol, opposingSymbol, pawns);
		set_cursor((8 * size + 25)/2 - 8, 3);

		//Reading the action to perform from the keyboard
		action = get_pressed_key();

		//If the player cannot place any pawn but try to do so
		if (!moves && action != 'L' && action != 'l' && action != 'q' && action != 'Q')
		{
			clear();
			disp_center("You cannot place any pawn, skip your turn!", size + 2, 4*size + 70);
			center_press_any_key(size + 3, 4*size + 70);
			continue;
		}

		if ( moves && (action == 's' || action == 'S') )
		{
			clear();
			disp_center("You cannot skip your turn: you can place a pawn!", size, 4*size + 70);
			center_press_any_key(size + 4, 4*size + 70);
			continue;
		}


		switch (action)
		{
			case 'h':
				show_hints(*gameBoard, size, movesList, moves);	//Show hints
				break;

			case 'H':
				show_hints(*gameBoard, size, movesList, moves);	//Show hints
				break;


			case 'p':
				if (place_pawn(gameBoard, size, movesList, moves, playerSymbol, round))
					return 1;
				break;

			case 'P':
				if (place_pawn(gameBoard, size, movesList, moves, playerSymbol, round))
					return 1;
				break;


			case 'l':
				//Load a round
				break;

			case 'L':
				//Load a round
				break;


			case 'q':
				clear();
				clear_saves(round-1);
				exit(EXIT_SUCCESS);
				break;

			case 'Q':
				clear();
				clear_saves(round-1);
				exit(EXIT_SUCCESS);
				break;

			
			case 's':
				/*logLine = (char*) malloc(50 * sizeof(char));
				check_alloc(logLine);

				sprintf(logLine, "Round %d: %c skipped his turn\n", round, playerSymbol);

				write_log(logLine, round);

				free(logLine);*/

				return 0;	//Skip the round
				break;

			case 'S':
				/*logLine = (char*) malloc(50 * sizeof(char));
				check_alloc(logLine);

				sprintf(logLine, "Round %d: %c skipped his turn\n", round, playerSymbol);

				write_log(logLine, round);

				free(logLine);*/

				return 0;	//Skip the round
				break;


			case 'r': //Rules
				set_text_color(10);
				disp_rules();
				press_any_key();
				break;

			case 'R': //Rules
				set_text_color(10);
				disp_rules();
				press_any_key();
				break;

			default:
				break;
		}

	}

	//The function is not supposed to reach this point, this line is only here to avoid compiler warning
	return 0;
}