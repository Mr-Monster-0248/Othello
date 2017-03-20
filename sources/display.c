#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <myconio.h>
#include <windows.h>

#include "../headers/settings.h"
#include "../headers/save_states.h"


//Function that clears the screen
void clear()
{
    clrscr();
}


//So that the myconio.h gotoxy function will be usable everywhere without warnings
void set_cursor(int x, int y)
{
    gotoxy(x, y);
}


//So that the myconio.h textcolor function will be usable everywhere without warnings
void set_text_color(int color)
{
    textcolor(color);
}


//Function that sets the console size
void set_console(int numberLines, int numberColumns)
{
    char *command = (char*) malloc(35 * sizeof(char));
    check_alloc(command);

    sprintf(command, "mode con LINES=%d COLS=%d", numberLines, numberColumns);

    system(command);

    free(command);
}


//Display a message on the screen at given coordinates x and y
void print_xy(char* string, int x, int y)
{
	//Setting the cursor to the given coordinates
    gotoxy(x, y);

    cprintf("%s", string);
}


//Display a message centered on a line
void disp_center(char* string, int line, int consoleLines)
{
    print_xy(string, consoleLines/2 - strlen(string)/2, line);
}


//Display a coloured message on the screen at given coordinates x and y
void print_color(char* string, int x, int y, int backgroundColor, int textColor)
{
	//Setting the text color and background color
    textcolor(textColor);
    textbackground(backgroundColor);

    //Displaying the text at the given coordinates
    print_xy(string, x, y);

    //Setting the text color and background color to default
    textcolor(15);
    textbackground(0);
}

//Display a zone with a defined color
void draw_zone(int xTop, int yTop, int xDown, int yDown, int color)
{
    int x, y;

    //for each case we print a space with a background
    //this method allows to create a colored zone
    textbackground(color);
    for(y = yTop; y < yDown; y++)
        for(x = xTop; x < xDown; x++)
            print_xy(" ", x, y);

    textbackground(0); //reinisializing the background color to avoid error with futur printf
}


//Function that displays the start screen
int startScreen()
{
    int i = 0;
    char key = 'p';

    //Setting the color of the text to light green over black
    textcolor(10);

    clear();

    set_console(23, 100);

    do
    {

        //Displaying the columns
        for (i = 2; i <= 22; i++)
        {
            Sleep(50);
            print_xy("|", 22, i);
            print_xy("|", 75, i);
        }
 

    
        disp_center("Black & White", 4, 100);
        disp_center("by", 7, 100);
        disp_center("Camille BRIAND", 11, 100);
        disp_center("and", 13, 100);
        disp_center("Thibault LEPEZ", 15, 100);


        gotoxy(33, 20);
        print_xy("Press Q to quit", 24, 19);
        print_xy("Press R to see the rules", 24, 20);
        print_xy("Press D to use default settings", 24, 21);
        print_xy("Press any other key to play", 24, 22);

        //Getting the choice from the user
        key = get_pressed_key();

        clear();

        switch(key)
        {
            case 'Q':
                exit(EXIT_SUCCESS);
                break;

            case 'q':
                exit(EXIT_SUCCESS);
                break;


            case 'R':
                disp_rules();
                press_any_key();
                break;

            case 'r':
                disp_rules();
                press_any_key();
                break;


            case 'd':
                clear();
                set_console(22, 100);
                return 1;
                break;

            case 'D':
                clear();
                set_console(22, 100);
                return 1;
                break;


            default:
                break;
        }

        clear();

        set_console(22, 100);

    } while (key == 'R' || key == 'r');

    return 0;
}


//Function that displays the game board
void disp_game_board(char** gameBoard, int size, char player1Char, char player2Char)
{
    int i = 0, j = 0;

    char toDisp[3];

    toDisp[2] = '\0';

    size++; //So that it would be easier to compute

    for (i = 0; i < size; i++)
    {
        //Resetting the characters to display
        toDisp[0] = ' ';
        toDisp[1] = ' ';

        //Computing the corresponding x index character (alphabet character) and displaying it
        *toDisp = 65 + i;
        print_xy(toDisp, 6 + 3*i, 2);

        //Resetting the characters again
        toDisp[0] = ' ';
        toDisp[1] = ' ';

        //Displaying the y index
        if (i >= 9)
        {
            toDisp[0] = (i+1) / 10 + 48;
            toDisp[1] = (i+1) % 10 + 48;
        } else {
            toDisp[1] = 49 + i;
        }

        print_xy(toDisp, 2, 3 + i);

        toDisp[1] = ' ';
    
        for (j = 0; j < size; j++)
        {
        
            *toDisp = gameBoard[i][j]; //Getting the content of the case

            if (*toDisp == player1Char)
                textcolor(10);
            else
                if(*toDisp == player2Char)
                    textcolor(12);


            print_xy(toDisp, 6 + 3*i, 3 + j); //Displaying it at matching coordinates
        
            textcolor(15);
        }   
    }
}


//Function that displays the statistics window
void disp_statistics(int numberWhites, int numberBlacks, int size, char playerChar, char adverseChar, int round)
{
    char* toDisp = (char*) malloc(20 * sizeof(char));
    check_alloc(toDisp);

    //Drawing a white zone for the interface
    draw_zone( (8*size + 25)/2 - 8, 2, (8*size + 25)/2 + 16, 11, 15);

    //Displaying the round
    sprintf(toDisp, "Round %d", round);
    print_color(toDisp, (8*size + 25)/2, 2, 15, 0);

    //Displaying the active player's symbol
    sprintf(toDisp, "it's %c turn", playerChar);
        
    print_color(toDisp, (8*size + 25)/2 - 4, 4, 15, 0);

    //Displaying the count of pawns
    sprintf(toDisp, "%c = %d pawns", playerChar, numberWhites);
    print_color(toDisp, (8*size + 25)/2 - 6, 7, 15, 0);
    sprintf(toDisp, "%c = %d pawns", adverseChar, numberBlacks);
    print_color(toDisp, (8*size + 25)/2 - 6, 8, 15, 0);


    free(toDisp);
}


//Function that displays the commands palette
void disp_commands(int size)
{    
    draw_zone(3, 7 + size, 19, size + 14, 15);

    print_color("Commands", 7, 7 + size, 15, 0);

    print_color("P = Place pawn", 4, size + 8, 15, 0);
    print_color("S = Skip turn", 4, size + 9, 15, 0);
    print_color("H = Show hints", 4, size + 10, 15, 0);
    print_color("R = Rules", 4, size + 11, 15, 0);
    print_color("L = Load round", 4, size + 12, 15, 0);
    print_color("Q = Quit", 4, size + 13, 15, 0);
}


//Function that displays the interface at each round
void disp_interface(char** gameBoard, int size, int round, char player1Char, char player2Char, int* numberPawns)
{
    set_console(size + 15, 4*size + 70);

    //Setting the text color to white
    textcolor(15);
    disp_game_board(gameBoard, size, player1Char, player2Char);

    //Disp commands palette
    disp_commands(size);

    disp_statistics(numberPawns[0], numberPawns[1], size, player1Char, player2Char, round);
}