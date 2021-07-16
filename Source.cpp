#define _CRT_SECURE_NO_WARNINGS

// Macros variables
#define NUMBER_OF_LINES 3
#define NUMBER_OF_COLUMNS 3
#define COUNT_ONE_DIGIT_NUMBERS 3
#define LINE_SEPARATOR "\n"

// Libraries used
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Global variables
char numChars[] = { '0', '1', '2' };

/* Function Prorotypes */
void allocateMemoryForTable(char**&);

void deAllocateMemoryForTable(char**&);

void createTable(char**);

void drawMenu();

int inputMenuChoice();

void displayTable(char**, int&, int&, char);

void startGame(char**&, int&, int&, int&, int*);

void displayPlayersLayout(int&, char&, int&, int&);

void validateCoordInputMove(char&, bool&, int&);

void makeAMove(int&, int&);

// Allocate memory for the game table (2x2 char matrix)
void allocateMemoryForTable(char**& table) {
	table = (char**)malloc(NUMBER_OF_LINES * sizeof(int*));
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		table[i] = (char*)malloc(NUMBER_OF_COLUMNS * sizeof(int));
	}
}

// Delete the memory occupied by the matrix
void deAllocateMemoryForTable(char**& table) {
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		free(table[i]);
	}
	free(table);
}

// Build the matrix 
void createTable(char** table) {
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
			table[i][j] = ' ';
		}
	}
}

// Create and display the user menu
void drawMenu() {
	printf("1) New Game(X)\n");
	printf("2) Exit Game\n");
	printf(LINE_SEPARATOR);
}

// Ask user to pick a menu choice
int inputMenuChoice() {
	int menuChoice = 0;
	scanf_s("%d", &menuChoice);

	return menuChoice;
}

// Dysplay the game table (the 2D matrix)
void displayTable(char** table, int& line, int& column, char move) {
	printf(LINE_SEPARATOR);
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		printf(" - - -\n");
		for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
			if (i == line && j == column) {
				table[line][column] = move;
				printf("|");
				printf("%c", table[line][column]);
			}
			else {
				printf("|%c", table[i][j]);
			}

		}
		printf("|\n");
	}
	printf(" - - -\n");
	printf(LINE_SEPARATOR);
}

// Count the elements from a line that are the same as the current move
int getLineCounter(char**& table, int lineCoord, char move) {
	int lineMoveCounter = 0;
	
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		if (table[lineCoord][i] == move) {
			lineMoveCounter++;
		}
	}

	return lineMoveCounter;
}

// Count the elements from a column that are the same as the current move
int getColumnCounter(char**& table, int colCoord, char move) {
	int colMoveCounter = 0;

	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		if (table[i][colCoord] == move) {
			colMoveCounter++;
		}
	}

	return colMoveCounter;
}

// Start the Game
void startGame(char**& table, int& lineCoord, int& columnCoord, int& gameStatus, int* winningStatus) {
	char move;

	displayPlayersLayout(gameStatus, move, lineCoord, columnCoord);
	
	displayTable(table, lineCoord, columnCoord, move);

	// count how many cells on a line contain X
	int lineMoveCounter = getLineCounter(table, lineCoord, move);

	// count how many cells on a column contain X
	int colMoveCounter = getColumnCounter(table, columnCoord, move);

	if ((lineMoveCounter == 3 || colMoveCounter == 3) && move == 'X') {
		*winningStatus = 1;
	}

	if ((lineMoveCounter == 3 || colMoveCounter == 3) && move == '0') {
		*winningStatus = 2;
	}
}

// Display the players' layout
void displayPlayersLayout(int& gameStatus, char& move, int& line, int& column) {

	if (gameStatus == 1) {
		move = 'X';
		printf("\n X Make a move!\n");
		makeAMove(line, column);
		gameStatus == 1 ? gameStatus = 2 : gameStatus = 0;
	}
	else if (gameStatus == 2) {
		move = '0';
		printf("\n 0 Make a move!\n");
		makeAMove(line, column);
		gameStatus == 2 ? gameStatus = 1 : gameStatus = 0;
	}
}

// Validate the player move's coordinates
void validateCoordInputMove(char &coordUserInputMove, bool &isCoordInputADigit, int &coord) {
	for (int i = 0; i < COUNT_ONE_DIGIT_NUMBERS; i++) {		
		if (coordUserInputMove != numChars[i]) {
			isCoordInputADigit = false;
			coord = -1;
		}
		else {
			isCoordInputADigit = true;
			break;
		}
	}
}

// Get the coordinates of the player's movement
void makeAMove(int& line, int& column) {

	bool isLineInputADigit = true;
	bool isColumnInputADigit = true;
	
	char lineUserInput = ' ';
	char columnUserInput = ' ';

	printf("\nEnter the line of your move: ");
	scanf(" %c", &lineUserInput);

	do {
		validateCoordInputMove(lineUserInput, isLineInputADigit, line);

		if (isLineInputADigit) {
			// convert char to int
			line = lineUserInput - '0';
		}
		else {
			printf("Please enter another value: ");
			scanf(" %c", &lineUserInput);
		}


	} while (line != 0 && line != 1 && line != 2 && isLineInputADigit == false);

	printf("Enter the column of your move: ");
	scanf(" %c", &columnUserInput);

	do {
		validateCoordInputMove(columnUserInput, isColumnInputADigit, column);

		if (isColumnInputADigit) {
			// convert char to int
			column = columnUserInput - '0';
		}
		else {
			printf("Please enter another value: ");
			scanf(" %c", &columnUserInput);
		}
	} while (column != 0 && column != 1 && column != 2 && isColumnInputADigit == false);
}

// Main Program
int main(void) {

	// Variables defined
	char** table = NULL;
	int lineCoord = 0;
	int columnCoord = 0;
	int menuChoice = 0;
	char move = ' ';

	/*
		"1" -> X has won
		"2" -> 0 has won
		"3" -> it's a draw
	*/
	int winningStatus = 0;

	/*
		-> 1 - it's player1's turn
		-> 2 -> it's player2's turn
		-> 0 -> the game ended
	*/
	int gameStatus = 1;


	allocateMemoryForTable(table);
	createTable(table);
	drawMenu();

	do {
		menuChoice = inputMenuChoice();

		if (menuChoice == 2) {
			exit(0);
		}
		else if (menuChoice == 1) {
			displayTable(table, lineCoord, columnCoord, move);
			break;
		}
	} while (menuChoice != 1 && menuChoice != 2);

	while (gameStatus != 0) {
		startGame(table, lineCoord, columnCoord, gameStatus, &winningStatus);

		if (winningStatus == 1) {
			printf("\nX has won!\n");
			break;
		}
		else if (winningStatus == 2) {
			printf("\n0 has won!\n");
			break;
		}
	}

	deAllocateMemoryForTable(table);
	return 0;
}
