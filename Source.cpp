#define _CRT_SECURE_NO_WARNINGS

/*
TO IMPLEMENT:
-> Validate input so that a player cannot move in an occupied table cell
-> Implement game end - win, draw, lose
*/

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

/* Function prototypes */ 

// Allocate memory for the game table (2x2 char matrix)
void allocateMemoryForTable(char**&);

// Build the matrix 
void createTable(char**);

// Create and display the user menu
void drawMenu();

// Delete the memory occupied by the matrix
void deAllocateMemoryForTable(char**&);

// Ask user to pick a menu choice
int inputMenuChoice();

// Dysplay the game table (the 2D matrix)
void displayTable(char**, int&, int&, char);

// Start the Game
void startGame(char**&, int&, int&, int&);

// Display the players' layout
void displayPlayersLayout(int&, char&, int&, int&);

// Get the coordinates of the player's movement
void makeAMove(int&, int&);

void validateCoordInputMove(char&, bool&, int&);

// Main Program
int main(void) {

	// Variables defined
	char** table = NULL;
	int lineCoord = 0;
	int columnCoord = 0;
	int menuChoice = 0;
	char move = ' ';

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
		startGame(table, lineCoord, columnCoord, gameStatus);
	}

	deAllocateMemoryForTable(table);
	return 0;
}

void allocateMemoryForTable(char**& table) {
	table = (char**)malloc(NUMBER_OF_LINES * sizeof(int*));
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		table[i] = (char*)malloc(NUMBER_OF_COLUMNS * sizeof(int));
	}
}

void deAllocateMemoryForTable(char**& table) {
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		free(table[i]);
	}
	free(table);
}

void createTable(char** table) {
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
			table[i][j] = ' ';
		}
	}
}

void drawMenu() {
	printf("1) New Game(X)\n");
	printf("2) Exit Game\n");
	printf(LINE_SEPARATOR);
}

int inputMenuChoice() {
	int menuChoice = 0;
	scanf_s("%d", &menuChoice);

	return menuChoice;
}

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

void startGame(char**& table, int& lineCoord, int& columnCoord, int& gameStatus) {
	char move;
	displayPlayersLayout(gameStatus, move, lineCoord, columnCoord);

	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {

			// ****** fix this bug
			//if (move == table[i][j]) {
			//	printf("Cell occupied. Please make another move!");
			//	makeAMove(lineCoord, columnCoord);
			//}

			//if (table[i][j] == ) {
			//	gameStatus = 0;
			//}
		}
	}

	displayTable(table, lineCoord, columnCoord, move);
}

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

