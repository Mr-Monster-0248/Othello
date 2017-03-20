#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/save_states.h"
#include "../headers/display.h"
#include "../headers/settings.h"
#include "../headers/save_states.h"
#include "../headers/game_functions.h"

#define EMPTY_CASE 46

//Function that returns the coordinates of the pawn chosen by the AI
int* get_AI_coordinates(int** movesList, int numberMoves)
{
	int i = 0, maxCapture = movesList[0][2], *spots = NULL, numberSpots = 0, *coordinates;

	coordinates = calloc(2, sizeof(int));
	check_alloc(coordinates);


	//Finding the maximum capturable pawns
	for (i = 1; i < numberMoves; i++)
		if (movesList[i][2] > maxCapture)
			maxCapture = movesList[i][2];

	//Finding the number of moves that are the best moves
	for (i = 0; i < numberMoves; i++)
		if (movesList[i][2] == maxCapture)
			numberSpots++;

	//Allocating memory for the coordinates of the best moves
	spots = (int*) malloc(numberSpots * sizeof(int));
	check_alloc(spots);

	numberSpots = 0;

	//Storing the subscripts of the best moves
	for (i = 0; i < numberMoves; i++)
		if (movesList[i][2] == maxCapture)
			spots[numberSpots++] = i;

	//Computing a random number to get a random position among the best ones
	srand(time(NULL));
	numberSpots = rand()%numberSpots;

	coordinates[0] = movesList[spots[numberSpots]][0];
	coordinates[1] = movesList[spots[numberSpots]][1];

	return coordinates;
}


//Function that returns 1 if the player wants to play against the AI, 0 if not
int ask_AI()
{
	char againstIA = 'n';

	print_xy("Do you want to play against the AI ? (y/n) ", 30, 5);

	do
	{
		set_cursor(50, 8);
		againstIA = get_pressed_key();
		clear();
	} while (againstIA != 'n' && againstIA != 'N' && againstIA != 'y' && againstIA != 'Y');

	if (againstIA == 'y' || againstIA == 'Y')
		return 1;
	
	return 0;
}


//Function that starts a new round, returns 1 if a pawn has been placed, 0 if not
int new_round_AI(char*** gameBoard, int size, char playerSymbol, char opposingSymbol, int round)
{
	int i = 0, j = 0, pawns[2] = {0}, moves = 0, **movesList = NULL;

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

	//Computing the available moves
	moves = available_moves(*gameBoard, size, playerSymbol, &movesList);

	//Displaying the interface so that the player make a choice
	disp_interface(*gameBoard, size, round, playerSymbol, opposingSymbol, pawns);

	//If no pawn can be placed, returning 0
	if (moves == 0)
		return 0;


	get_AI_coordinates(movesList, moves);

	place_pawn(gameBoard, size, movesList, moves, playerSymbol, round);

	return 1;
}