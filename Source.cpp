#define _CRT_SECURE_NO_WARNINGS

// Macros variables
#define NUMBER_OF_LINES 3
#define NUMBER_OF_COLUMNS 3
#define LINE_SEPARATOR "\n"

// Libraries used
#include <stdio.h>
#include <stdlib.h>

// Function prototypes

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


// Main Program
int main(void) {

	// Variables defined
	char** table = NULL;
	int lineCoord = 0;
	int columnCoord = 0;
	int menuChoice = 0;
	char move = ' ';

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