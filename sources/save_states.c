#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "../headers/display.h"
#include "../headers/game_functions.h"
#include "../headers/settings.h"


//Function that checks if a given pointer is correctly allocated, quit the program if not
void check_alloc(void* pointer)
{
	if (pointer == NULL)
	{
		clear();
		printf("A memory error occured, please launch the program again\n");
		press_any_key();
		exit(EXIT_FAILURE);
	}
}


//Function that reads the rules from the rules.txt file
void disp_rules()
{
	//Setting a large enough console window
	set_console(34, 120);

	FILE* rules = fopen("rules.txt", "r");
	
	while (!feof(rules))
		printf("%c", fgetc(rules));

	fclose(rules);

	printf("\n\n");
}


//Function that counts the number of pawns
int** list_pawns(char** gameBoard, int size, char toCheck)
{
	int i = 0, j = 0, **list = NULL, numberPawns = 1;

	list = (int**) malloc(numberPawns * sizeof(int*));
	check_alloc(list);
	*list = (int*) malloc(2 * sizeof(int));
	check_alloc(*list);

	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			if (gameBoard[i][j] == toCheck)
			{	
				realloc(list, numberPawns * sizeof(int*));
				list[numberPawns][0] = j;
				list[numberPawns++][1] = i;
			}

	return list;
}


//Function that writes a save state of the game
void write_saveState(int** listWhites, int numberWhites, int** listBlacks, int numberBlacks, int round)
{
	int i = 0 ;
	char* fileName = (char*) malloc(50 * sizeof(char));
	FILE* saveFile = NULL;

	check_alloc(fileName);

	sprintf(fileName, "saves/round%d.sav", round); //Creating a name for the save file

	saveFile = fopen(fileName, "w");
	check_alloc(saveFile);

	free(fileName);

	//Writing the number of white pawns and their coordinates
	fprintf(saveFile, "%d\n", numberWhites);
	for (i = 0; i < numberWhites; i++)
		fprintf(saveFile, "%d %d ", listWhites[i][0], listWhites[i][1]);

	//Writing the number of black pawns and their coordinates
	fprintf(saveFile, "\n%d\n", numberBlacks);
	for (i = 0; i < numberBlacks; i++)
		fprintf(saveFile, "%d %d ", listBlacks[i][0], listBlacks[i][1]);

	fclose(saveFile);
}


//Function that reads a save state from the game
void load_saveState(int round, char*** gameBoard, int size, char blackSymbol, char whiteSymbol)
{
	int i = 0, numberWhites = 0, numberBlacks = 0, **listWhites = NULL, **listBlacks = NULL;
	char *fileName = (char*) malloc(50 * sizeof(char));
	FILE* saveFile = NULL;

	check_alloc(fileName);

	sprintf(fileName, "saves/round%d.sav", round);

	saveFile = fopen(fileName, "r");
	check_alloc(saveFile);

	free(fileName);
	
	//Reading the number of white pawns
	fscanf(saveFile, "%d", &numberWhites);

	//Storing the coordinates of each white pawn
	for (i = 0; i < numberWhites; i++)
		fscanf(saveFile, "%d %d ", &listWhites[i][0], &listWhites[i][1]);

	//Reading the number of black pawns
	fscanf(saveFile, "%d", &numberBlacks);

	//Storing the coordinates of each black pawn
	for (i = 0; i < numberBlacks; i++)
		fscanf(saveFile, "%d %d ", &listBlacks[i][0], &listWhites[i][1]);

	//We do not need to read this file anymore
	fclose(saveFile);


	//Resetting the game board
	*gameBoard = init_game_board(size + 1, blackSymbol, whiteSymbol);


	/*
		Placing the pawns
	*/
	for (i = 0; i < numberWhites; i++)
	{
		(*gameBoard)[ listBlacks[i][1] ][ listBlacks[i][0] ] = blackSymbol;
		(*gameBoard)[ listWhites[i][1] ][ listWhites[i][0] ] = whiteSymbol;
	}
}


//Function that erases all the temporary save files 
void clear_saves(int rounds)
{
	int i = 0;
	char *logFile = malloc(20 * sizeof(char));
	check_alloc(logFile);

	for (i = 0; i < rounds; i++)
	{
		sprintf(logFile, "saves/round%d.sav", i);
		remove(logFile);
	}

	free(logFile);

	system("rmdir saves /S/Q"); //Without asking for confirmation if it remains files
	//system("rmdir saves");
}


//Function that reads a log line
void read_log(char** logLine, int lineNumber)
{
	int i = 0, read = 0;
	char* fileName = (char*) malloc(50 * sizeof(char));
	FILE* log = NULL;

	check_alloc(fileName);
	sprintf(fileName, "saves/log%d.txt", lineNumber);

	log = fopen(fileName, "r");

	//Checking the oppening of the log file
	check_alloc(log);

	free(fileName);

	for (i = 0; !feof(log) && !read; i++)
	{
		*logLine = (char*) malloc(150 * sizeof(char));
		check_alloc(*logLine);

		(*logLine)[i] = fgetc(log);
		realloc(*logLine, (1 + strlen(*logLine)) * sizeof(char));
		check_alloc(*logLine);
	}

	(*logLine)[strlen(*logLine)] = '\0';
	
	fclose(log);		
}


//Function that writes a log line
void write_log(char* line, int round)
{
	FILE* logFile = NULL;
	char* fileName = NULL;

	fileName = (char*) malloc(50 * sizeof(char));

	check_alloc(fileName);

	sprintf(fileName, "saves/log%d.txt", round);

	logFile = fopen(fileName, "w");

	check_alloc(logFile);

	free(fileName);

	fputs(line, logFile);

	fclose(logFile);
}