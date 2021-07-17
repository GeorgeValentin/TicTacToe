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
#include <string.h>

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

int getLineCounter(char**, int, char);

int getColumnCounter(char**, int, char);

int determineWinningStatus(int, int, int, int, char);

void checkGameTableCells(char**, int&, int&, int*);

int getMainDiagCounter(char**, int, int, char);

int getSecDiagCounter(char**, int, int, char);

char inputPlayerLineMove(char);

char inputPlayerColumnMove(char);

void settingMenuOption(int, char**, int, int, char);

void startMenu(int&, char**&, int&, int&, char&);

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

// Display the game table (the 2D matrix)
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
int getLineCounter(char** table, int lineCoord, char move) {
	int lineMoveCounter = 0;
	
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		if (table[lineCoord][i] == move) {
			lineMoveCounter++;
		}
	}

	return lineMoveCounter;
}

// Count the elements from a column that are the same as the current move
int getColumnCounter(char** table, int colCoord, char move) {
	int colMoveCounter = 0;

	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		if (table[i][colCoord] == move) {
			colMoveCounter++;
		}
	}

	return colMoveCounter;
}

// Get the winner based on the values on the lines and columns
int determineWinningStatus(int lineMoveCounter, int colMoveCounter, int mainDiagCounter, int secDiagonalCounter, char move) {
	int winningStatus = 0;

	if (lineMoveCounter == 3 || colMoveCounter == 3 || mainDiagCounter == 3 || secDiagonalCounter == 3) {
		if (move == 'X') {
			// X wins
			winningStatus = 1;
		}
		else {
			// 0 wins
			winningStatus = 2;
		}
	}
	else {
		// it is a draw
		winningStatus = 0;
	}

	return winningStatus;
}

// Check if the cell of the current move is occupied
void checkGameTableCells(char** table, int& line, int& column, int* cellStatus)
{
	if (table[line][column] != ' ') {
		*cellStatus = 1;
	}
	else {
		*cellStatus = 0;
	}
}

// Count the elements that contain the current move from the main diagonal of the game table
int getMainDiagCounter(char** table, int lineCoord, int columneCoord, char move)
{
	int mainDiagCounter = 0;

	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
			if (i == j && table[i][j] == move) {
				mainDiagCounter++;
			}
		}
	}

	return mainDiagCounter;
}

// Count the elements that contain the current move from the secondary diagonal of the game table
int getSecDiagCounter(char** table, int lineCoord, int columnCoord, char move) {
	int secDiagCounter = 0;
	
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {

			// only works when NUMBER_OF_LINES == NUMBER_OF_COLUMNS
			if ((i + j) == (NUMBER_OF_LINES - 1) && table[i][j] == move) {
				secDiagCounter++;
			}
		}
	}

	return secDiagCounter;
}

// Start the Game
void startGame(char**& table, int& lineCoord, int& columnCoord, int& gameStatus, int* winningStatus) {
	char move;
	int cellStatus = 0;

	// get player move
	displayPlayersLayout(gameStatus, move, lineCoord, columnCoord);

	do
	{
		// get the status of the current cell
		checkGameTableCells(table, lineCoord, columnCoord, &cellStatus);

		// if the current cell is empty
		if (cellStatus == 0) {
			displayTable(table, lineCoord, columnCoord, move);

			// count how many cells on a line contain the current move
			int lineMoveCounter = getLineCounter(table, lineCoord, move);

			// count how many cells on a column contain the current move
			int colMoveCounter = getColumnCounter(table, columnCoord, move);

			// count how many cells on the main diagonal contain the current move
			int mainDiagCounter = getMainDiagCounter(table, lineCoord, columnCoord, move);

			// count how many cells on the secondary diagonal contain the current move
			int secondaryDiagCounter = getSecDiagCounter(table, lineCoord, columnCoord, move);

			// get the winningStatus
			*winningStatus = determineWinningStatus(lineMoveCounter, colMoveCounter, mainDiagCounter, secondaryDiagCounter, move);
		}
		// if the current cell is not empty
		else 
		{
			// ask the user to input a different one
			printf("\n Enter another cell!\n");
			makeAMove(lineCoord, columnCoord);
		}

	} while (cellStatus != 0); // run the loop until the user enters a valid cell
	
}

// Display the players' layout
void displayPlayersLayout(int& gameStatus, char& move, int& line, int& column) {

	switch (gameStatus) {
		case 1:
			move = 'X';
			printf("\n %c make a move! \n", move);
			makeAMove(line, column);
			gameStatus == 1 ? gameStatus = 2 : gameStatus = 0;
			break;

		case 2:
			move = '0';
			printf("\n %c make a move! \n", move);
			makeAMove(line, column);
			gameStatus == 2 ? gameStatus = 1 : gameStatus = 0;
		break;

		default:
			break;
	}
}

// Validate the player move's coordinates to make sure the inputted value is a digit
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

// Input the line coordinate of the move
char inputPlayerLineMove(char lineUserInput) {
	switch (lineUserInput) {
	case ' ':
		printf(" Enter the line of your move: ");
		break;
	
	default: 
		printf(" Please enter another value for the line: ");
		break;
	}
	scanf(" %c", &lineUserInput);

	return lineUserInput;
}

// Input the column coordinate of the move
char inputPlayerColumnMove(char columnUserInput) {
	
	switch (columnUserInput) {
	case ' ':
		printf(" Enter the column of your move: ");
		break;

	default:
		printf(" Please enter another value for the column: ");
		break;
	}
	scanf(" %c", &columnUserInput);

	return columnUserInput;
}

// Get the coordinates of the player's movement
void makeAMove(int& line, int& column) {

	bool isLineInputADigit = true;
	bool isColumnInputADigit = true;
	
	char lineUserInput = ' ';
	char columnUserInput = ' ';

	// get input for the line coordinate of the move
	lineUserInput = inputPlayerLineMove(lineUserInput);

	do {
		validateCoordInputMove(lineUserInput, isLineInputADigit, line);

		if (isLineInputADigit) {
			// convert char to int
			line = lineUserInput - '0';
		}
		else {
			lineUserInput = inputPlayerLineMove(lineUserInput);
		}

	} while (line != 0 && line != 1 && line != 2 && isLineInputADigit == false);

	// get input for the column coordinate of the move
	columnUserInput = inputPlayerColumnMove(columnUserInput);

	do {
		validateCoordInputMove(columnUserInput, isColumnInputADigit, column);

		if (isColumnInputADigit) {
			// convert char to int
			column = columnUserInput - '0';
		}
		else {
			columnUserInput = inputPlayerColumnMove(columnUserInput);
		}
	} while (column != 0 && column != 1 && column != 2 && isColumnInputADigit == false);
}

// Define the functionality for when a user chooses a certain menu option
void settingMenuOption(int menuChoice, char** table, int lineCoord, int columnCoord, char move) {
	
	switch (menuChoice) {
	case 1: 
		displayTable(table, lineCoord, columnCoord, move);
		break;

	case 2:
		exit(0);
		break;
	}
}

// Start the menu 
void startMenu(int& menuChoice, char**& table, int& lineCoord, int& columnCoord, char& move) {
	menuChoice = inputMenuChoice();
	do {
		if (menuChoice != 1 && menuChoice != 2) {
			printf("\nPlease choose another option!\n");
			menuChoice = inputMenuChoice();
		}
		settingMenuOption(menuChoice, table, lineCoord, columnCoord, move);
	} while (menuChoice != 1 && menuChoice != 2);
}

// Main Program
int main(void) {

	// Variables defined
	char** table = NULL;
	int lineCoord = 0;
	int columnCoord = 0;
	int menuChoice = 0;
	char move = ' ';
	int counterOccupiedCells = 0;

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
	startMenu(menuChoice, table, lineCoord, columnCoord, move);
	
	while (gameStatus != 0) {
		startGame(table, lineCoord, columnCoord, gameStatus, &winningStatus);

		counterOccupiedCells++;

		if (winningStatus == 1) {
			printf("\nX has won!\n");
			gameStatus = 0;
			break;
		}
		else if (winningStatus == 2) {
			printf("\n0 has won!\n");
			gameStatus = 0;
			break;
		}	

		if (counterOccupiedCells == 9) {
			break;
		}
	}

	if (winningStatus == 0) {
		printf("\nIt's a draw!\n");
		gameStatus = 0;
	}

	deAllocateMemoryForTable(table);
	return 0;
}
