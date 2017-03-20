#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "../headers/display.h"
#include "../headers/save_states.h"

//Function that voids the keyboard's buffer
void clear_buffer()
{
	fflush(stdin);
}


//Function that waits for a key press
void press_any_key()
{
	printf("Press any key to continue...");
	while(!kbhit());
	getch();
}


//Function that centers the message "Press any key to continue..." on a given line with any console size
void center_press_any_key(int line, int consoleLines)
{
	disp_center("Press any key to continue...", line, consoleLines);
	while(!kbhit());
	getch();
}

//Function that return the ASCII code of a pressed key
char get_pressed_key()
{
	while(!kbhit());
	return getch();
}

//Function that asks for a correct size for the game board
int askBoardWidth()
{
	int size = 0;

	//Resizing the console
	set_console(22, 100);
	
	do
	{
		disp_center("Please enter the number of lines or columns to use for this game (min. 6) (must be even):", 5, 100);
		print_xy("> ", 45, 8);
		print_xy(" <", 52, 8);

		//Resetting the color to green
		set_text_color(10);

		set_cursor(49, 8);

		if ( scanf("%d", &size) )
		{
			if (size < 6 || size % 2 != 0 || size > 26) 
			{
				clear();
				disp_center("This value cannot cannot be used for this game, try another one", 9, 100);
				clear_buffer();
				center_press_any_key(11, 100);
				clear();
				continue;
			}
		}	else	{
				clear_buffer();
				size = 0;
		}

	} while (size < 6 || size % 2 != 0);


	return size;
}


//Function that asks a symbol for each player
void get_player_symbols(char* player1, char* player2)
{
	char symbolOK = 'a', *toDisp = (char*) malloc(2 * sizeof(char));
	
	check_alloc(toDisp);
	toDisp[1] = '\0';

	//Resizing the console
	set_console(22, 100);

	//Setting player 1's symbol
	do
	{
		//Resetting symbolOk
		symbolOK = 'a';

		clear();

		disp_center("Enter the symbol that will be used for player 1", 7, 100);
		disp_center(">     <", 10, 100);

		set_cursor(50, 10);

		*player1 = get_pressed_key();

		clear();

		//Checking if the chosen symbol is not the empty case symbol
		if (*player1 == 46)
		{
			disp_center("Sorry, this symbol is not available for the players", 7, 100);
			set_cursor(50, 10);
			press_any_key();
			continue;
		}

		do
		{
			*toDisp = *player1; 

			disp_center("The symbol that will be used for player 1 is now", 7, 100);
			disp_center(toDisp, 11, 100);

			disp_center("Is it correct? (y/n)", 14, 100);
			set_cursor(50, 15);

			symbolOK = get_pressed_key();
		} while (symbolOK != 'y' && symbolOK != 'Y' && symbolOK != 'n' && symbolOK != 'N');

	} while (symbolOK != 'y' && symbolOK != 'Y');


	do
	{
		//Resetting symbolOk
		symbolOK = 'a';

		clear();

		disp_center("Enter the symbol that will be used for player 2", 7, 100);
		disp_center(">     <", 10, 100);

		set_cursor(50, 10);

		*player2 = get_pressed_key();

		clear();

		//Checking if the chosen symbol is not the empty case symbol
		if (*player2 == 46)
		{
			disp_center("Sorry, this symbol is not available for the players", 7, 100);
			center_press_any_key(12, 100);
			continue;
		}

		//Checking if the chosen symbols are different for both players
		if (*player2 == *player1)
		{
			disp_center("Sorry, this symbol is already taken by player 1", 7, 100);
			center_press_any_key(13, 100);
			continue;
		}


		do
		{
			*toDisp = *player2;

			disp_center("The symbol that will be used for player 2 is now", 7, 100);
			disp_center(toDisp, 11, 100);

			disp_center("Is it correct? (y/n)", 14, 100);
			set_cursor(50, 15);

			symbolOK = get_pressed_key();
		} while (symbolOK != 'y' && symbolOK != 'Y' && symbolOK != 'n' && symbolOK != 'N');

	} while ( (symbolOK != 'y' && symbolOK != 'Y') );

	free(toDisp);
}


//Function that removes the \n from a string read with fgets
void rem_backN(char* string)
{
	char *p = strchr(string, '\n');

	if (p)
		*p = '\0';

}