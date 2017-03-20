#ifndef DEF_DISPLAY_H
	#define DEF_DISPLAY_H
	
	//Function that clears the screen
	void clear();

	//So that the myconio.h gotoxy function will be usable everywhere without warnings
	void set_cursor(int x, int y);

	//So that the myconio.h textcolor function will be usable everywhere without warnings
	void set_text_color(int color);

	//Function that sets the console size
	void set_console(int numberLines, int numberColumns);

	//Display a message on the screen at given coordinates x and y
	void print_xy(char* string, int x, int y);

	//Display a message centered on a line
	void disp_center(char* string, int line, int consoleLines);

	//Display a coloured message on the screen at given coordinates x and y
	void print_color(char* string, int x, int y, int backgroundColor, int textColor);

	//Display a zone with a defined color
	void draw_zone(int xTop, int yTop, int xDown, int yDown, int color);
	
	//Function that displays the start screen
	int startScreen();

	//Function that displays the game board
	void disp_game_board(char** gameBoard, int size, char player1Char, char player2Char);

	//Function that displays the statistics window
	void disp_statistics(int numberWhites, int numberBlacks, int size, char player1Char, char player2Char, int round);

	//Function that displays the commands palette
	void disp_commands(int size);

	//Function that displays the interface at each round
	void disp_interface(char** gameBoard, int size, int round, char player1Char, char player2Char, int* numberPawns);

#endif