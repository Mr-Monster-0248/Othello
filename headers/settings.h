#ifndef DEF_SETTING_H
	#define DEF_SETTING_H

	//Function that voids the keyboard's buffer
	void clear_buffer();

	//Function that waits for a key press
	void press_any_key();

	//Function that centers the message "Press any key to continue..." on a given line with any console size
	void center_press_any_key(int line, int consoleLines);

	//Function that return the ASCII code of a pressed key
	char get_pressed_key();

	//Function that asks for a correct size for the game board
	int askBoardWidth();

	//Function that asks a symbol for each player
	void get_player_symbols(char* player1, char* player2);

	//Function that removes the \n from a read string
	void rem_backN(char* string);


#endif