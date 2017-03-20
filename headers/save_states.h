#ifndef DEF_SAVE_STATES_H
	#define DEF_SAVE_STATES_H

	//Function that checks if a given pointer is correctly allocated, quit the program if not
	void check_alloc(void* file);

	//Function that reads the rules from the rules.txt file
	void disp_rules();

	//Function that counts the number of pawns
	int** list_pawns(char** gameBoard, int size, char toCheck);

	//Function that writes a save state of the game
	void write_saveState(int** listWhites, int numberWhites, int** listBlacks, int numberBlacks, int round);

	//Function that reads a save state from the game
	void load_saveState(int round, char*** gameBoard, int size, char blackSymbol, char whiteSymbol);

	//Function that erases all the temporary save files 
	void clear_saves(int rounds);

	//Function that reads a log line
	void read_log(char** logLine, int lineNumber);

	//Function that writes a log line
	void write_log(char* line, int round);
	
#endif