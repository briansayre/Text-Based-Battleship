// Battleship
// Brian Sayre
// 11/19/2018
// bsayre
// Section E

// cd C:/Users/brian/Documents/FreshmanYear/Fall/SE185/Bonus
// gcc battleship.c -o battleship.exe -lncurses
// ./battleship

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0
#define ROWS 5
#define COLM 5
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define GUESSED 2
#define PLAYER 1
#define COMPUTER 0
#define SHOW 0
// If SHOW is 1, the computers boats are visible
// If SHOW is 0, the computers boats are hidden


// Prototypes
void genComputerBoard(char board[ROWS][COLM]);
int loseTest (char board[ROWS][COLM]);
void drawBoard(int which, char board[ROWS][COLM]);


int main(void) {
	char playerBoard[ROWS][COLM];
	char computerBoard[ROWS][COLM];
	char playerGuessedBoard[ROWS][COLM];
	char computerGuessedBoard[ROWS][COLM];
	int i, j;
	int valid = 0, whoWon = 0;
	int Lx, Ly, Ldirection;
	int Mx, My, Mdirection;
	int Sx, Sy;
	int Gx, Gy;
	srand(time(NULL));
	
	// Starts screen
	//system("resize -s 30 75");
	initscr();
	
	// Fills the computer's and player's board
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLM; j++) {
			computerBoard[i][j] = '-';
			playerBoard[i][j] = '-';
			playerGuessedBoard[i][j] = '-';
			computerGuessedBoard[i][j] = '-';
		}
	}
	
	// Randomly generates the computers ship placements
	genComputerBoard(computerBoard);
	
	// Draws the boards on the screen
	if (SHOW) {
		drawBoard(COMPUTER, computerBoard);
	}
	else {
		drawBoard(GUESSED, playerGuessedBoard);
	}
	drawBoard(PLAYER, playerBoard);
	
	// Draws directions and grid on screen
	
	// Directions
	mvprintw(21, 12, "%s", "DIRECTIONS:");
	mvprintw(22, 12, "%s", "0 = UP");
	mvprintw(23, 12, "%s", "1 = RIGHT");
	mvprintw(24, 12, "%s", "2 = DOWN");
	mvprintw(25, 12, "%s", "3 = LEFT");
	
	// Symbol Key
	mvprintw(21, 29, "%s", "SYMBOL KEY:");
	mvprintw(22, 29, "%s", "O = BOAT");
	mvprintw(23, 29, "%s", "X = HIT");
	mvprintw(24, 29, "%s", "+ = MISS");
	mvprintw(25, 29, "%s", "- = UNTOUCHED");
	
	// Grid Key
	mvprintw(21, 50, "%s", "GRID KEY:");
	mvprintw(22, 49, "%s", "     X");
	mvprintw(23, 49, "%s", "   01234");
	mvprintw(24, 49, "%s", "  0*****");
	mvprintw(25, 49, "%s", "  1*****");
	mvprintw(26, 49, "%s", "Y 2*****");
	mvprintw(27, 49, "%s", "  3*****");
	mvprintw(28, 49, "%s", "  4*****");
	
	// Draws whose turn it is
	mvprintw(5, 8, "%s", "WHOS TURN:");
	mvprintw(6, 8, "%s", " PLAYER");
	mvprintw(7, 8, "%s", " COMPUTER");
	mvprintw(6, 8, "%c", '>');
	refresh();
	
	// Board lines
	for (i = 0; i < 75; i++) {
		mvprintw(14, i, "%c", '=');
		mvprintw(19, i, "%c", '=');
		mvprintw(30, i, "%c", '=');
	}
	for (i = 0; i < 31; i++) {
		mvprintw(i, 75, "%s", "||");
	}
	refresh();
	
	// Gets user input for boat placement
	
		// Long boat input
		while (!valid) {
			Lx = 10;
			Ly = 10;
			Ldirection = 10;
			
			// Gets user input
			while ( Lx > 4 && Ly > 4 && Ldirection > 3) {
				mvprintw(16, 0, "%s", "Enter a valid coordinate(0-4) and a valid direction(0-3) for long boat:   ");
				mvprintw(17, 0, "%s", "x,y,direction = ");
				refresh();
				scanw("%d,%d,%d", &Lx, &Ly, &Ldirection);
				mvprintw(17, 15, "%s", "              ");
			}
			
			// Checks if what is entered is valid
			if ((Ly == 0 && Lx == 0) || (Ly == 0 && Lx == 1) || (Ly == 1 && Lx == 0) || (Ly == 1 && Lx == 1) ) {
				if (Ldirection == RIGHT || Ldirection == DOWN) {
					valid = 1;
				}
			}
			if ((Ly == 2 && Lx == 0) || (Ly == 2 && Lx == 1)) {
				if (Ldirection == UP || Ldirection == 1 || Ldirection == DOWN) {
					valid = 1;
				}
			}
			if ((Ly == 3 && Lx == 0) || (Ly == 3 && Lx == 1) || (Ly == 4 && Lx == 0) || (Ly == 4 && Lx == 1)) {
				if (Ldirection == UP || Ldirection == RIGHT) {
					valid = 1;
				}
			}
			if ((Ly == 0 && Lx == 2) || (Ly == 1 && Lx == 2)) {
				if (Ldirection == RIGHT || Ldirection == DOWN || Ldirection == LEFT) {
					valid = 1;
				}
			}
			if (Ly == 2 && Lx == 2) {
				valid = 1;
			}
			if ((Ly == 3 && Lx == 2) || (Ly == 4 && Lx == 2)) {
				if (Ldirection == UP || Ldirection == RIGHT || Ldirection == LEFT) {
					valid = 1;
				}
			}
			if ((Ly == 0 && Lx == 3) || (Ly == 0 && Lx == 4) || (Ly == 1 && Lx == 3) || (Ly == 1 && Lx == 4)) {
				if (Ldirection == DOWN || Ldirection == LEFT) {
					valid = 1;
				}
			}
			if ((Ly == 2 && Lx == 3) || (Ly == 2 && Lx == 4)) {
				if (Ldirection = 0 || Ldirection == DOWN || Ldirection == LEFT) {
					Ldirection = (rand()%3)+1;
					if (Ldirection == RIGHT) {
						Ldirection = UP;
					}
					valid = 1;
				}
			}
			if ((Ly == 3 && Lx == 3) || (Ly == 3 && Lx == 4) || (Ly == 4 && Lx == 3) || (Ly == 4 && Lx == 4)) {
				if (Ldirection == UP || Ldirection == LEFT) {
					valid = 1;
				}
			}
			
			// If what was entered is valid, enters boat into array
			if (valid) {
				if (Ldirection == UP) {
					playerBoard[Ly][Lx] = 'O';
					playerBoard[Ly-1][Lx] = 'O';
					playerBoard[Ly-2][Lx] = 'O';
				}
				else if (Ldirection == RIGHT) {
					playerBoard[Ly][Lx] = 'O';
					playerBoard[Ly][Lx+1] = 'O';
					playerBoard[Ly][Lx+2] = 'O';
				}
				else if (Ldirection == DOWN) {
					playerBoard[Ly][Lx] = 'O';
					playerBoard[Ly+1][Lx] = 'O';
					playerBoard[Ly+2][Lx] = 'O';
				}
				else if (Ldirection == LEFT) {
					playerBoard[Ly][Lx] = 'O';
					playerBoard[Ly][Lx-1] = 'O';
					playerBoard[Ly][Lx-2] = 'O';
				}
			}
		}
		
		// Draws updated player board
		drawBoard(PLAYER, playerBoard);
		
		
		// Medium boat
		valid = 0;
		while (!valid) {
			Mx = 10;
			My = 10;
			Mdirection = 10;
			
			// Gets user input
			while ( Mx > 4 && My > 4 && Mdirection > 3) {
				mvprintw(16, 0, "%s", "Enter a valid coordinate(0-4) and a valid direction(0-3) for medium boat:");
				mvprintw(17, 0, "%s", "x,y,direction = ");
				refresh();
				scanw("%d,%d,%d", &Mx, &My, &Mdirection);
				mvprintw(17, 15, "%s", "              ");
			}
			
			// Checks if what is entered is valid
			if ((My == 0 && Mx == 0)) {
				if (Mdirection == RIGHT || Mdirection == DOWN) {
					if (Mdirection == RIGHT && playerBoard[My][Mx+1] != 'O') {
						valid = 1;
					}
					else if (Mdirection == DOWN && playerBoard[My+1][Mx] != 'O') {
						valid = 1;
					}
				}
			}
			if ((My == 1 && Mx == 0) || (My == 2 && Mx == 0) || (My == 3 && Mx == 0)) {
				if (Mdirection == UP || Mdirection == RIGHT || Mdirection == DOWN) {
					if (Mdirection == RIGHT && playerBoard[My][Mx+1] != 'O') {
						valid = 1;
					}
					else if (Mdirection == DOWN && playerBoard[My+1][Mx] != 'O') {
						valid = 1;
					}
					else if (Mdirection == UP && playerBoard[My-1][Mx] != 'O') {
						valid = 1;
					}
				}
			}
			if ((My == 4 && Mx == 0)) {
				if (Mdirection == UP || Mdirection == RIGHT) {
					if (Mdirection == RIGHT && playerBoard[My][Mx+1] != 'O') {
						valid = 1;
					}
					else if (Mdirection == UP && playerBoard[My-1][Mx] != 'O') {
						valid = 1;
					}
				}
			} 
			if ((My == 0 && Mx == 1) || (My == 0 && Mx == 2) || (My == 0 && Mx == 3)) {
				if (Mdirection == RIGHT || Mdirection == DOWN || Mdirection == LEFT) {
					if (Mdirection == RIGHT && playerBoard[My][Mx+1] != 'O') {
						valid = 1;
					}
					else if (Mdirection == DOWN && playerBoard[My+1][Mx] != 'O') {
						valid = 1;
					}
					else if (Mdirection == LEFT && playerBoard[My][Mx-1] != 'O') {
						valid = 1;
					}
				}
			}
			if ((My == 1 && Mx == 1) || (My == 1 && Mx == 2) || (My == 1 & Mx == 3) || (My == 2 && Mx == 1) || (My == 2 && Mx == 2) || 
				(My == 2 && Mx == 3) || (My == 3 && Mx == 1) || (My == 3 && Mx == 2) || (My == 3 && Mx == 3)) {
				if (Mdirection == RIGHT && playerBoard[My][Mx+1] != 'O') {
						valid = 1;
				}
				else if (Mdirection == DOWN && playerBoard[My+1][Mx] != 'O') {
						valid = 1;
					}
				else if (Mdirection == LEFT && playerBoard[My][Mx-1] != 'O') {
					valid = 1;
				}
				else if (Mdirection == UP && playerBoard[My-1][Mx] != 'O') {
						valid = 1;
				}
			}
			if ((My == 4 && Mx == 1) || (My == 4 && Mx == 2) || (My == 4 && Mx == 3)) {
				if (Mdirection == UP || Mdirection == RIGHT || Mdirection == LEFT) {
					if (Mdirection == RIGHT && playerBoard[My][Mx+1] != 'O') {
						valid = 1;
					}
					else if (Mdirection == LEFT && playerBoard[My][Mx-1] != 'O') {
						valid = 1;
					}
					else if (Mdirection == UP && playerBoard[My-1][Mx] != 'O') {
						valid = 1;
					}
				}
			}
			if (((My == 0 && Mx == 4))) {
				if (Mdirection == DOWN || Mdirection == LEFT) {
					if (Mdirection == DOWN && playerBoard[My+1][Mx] != 'O') {
						valid = 1;
					}
					else if (Mdirection == LEFT && playerBoard[My][Mx-1] != 'O') {
						valid = 1;
					}
				}
			}
			if ((My == 1 && Mx == 4) || (My == 2 && Mx == 4) || (My == 3 && Mx == 4)) {
				if (Mdirection = UP || Mdirection == DOWN || Mdirection == LEFT) {
					Mdirection = (rand()%3)+1;
					if (Mdirection == RIGHT) {
						Mdirection = UP;
					}
					if (Mdirection == DOWN && playerBoard[My+1][Mx] != 'O') {
						valid = 1;
					}
					else if (Mdirection == LEFT && playerBoard[My][Mx-1] != 'O') {
						valid = 1;
					}
					else if (Mdirection == UP && playerBoard[My-1][Mx] != 'O') {
						valid = 1;
					}
				}
			}
			if ((My == 4 && Mx == 4)) {
				if (Mdirection == UP || Mdirection == LEFT) {
					if (Mdirection == LEFT && playerBoard[My][Mx-1] != 'O') {
					valid = 1;
					}
					else if (Mdirection == UP && playerBoard[My-1][Mx] != 'O') {
						valid = 1;
					}
				}
			}
			
			// If what was entered is valid, enters boat into array
			if (valid) {
				if (Mdirection == UP) {
					playerBoard[My][Mx] = 'O';
					playerBoard[My-1][Mx] = 'O';
				}
				else if (Mdirection == RIGHT) {
					playerBoard[My][Mx] = 'O';
					playerBoard[My][Mx+1] = 'O';
				}
				else if (Mdirection == DOWN) {
					playerBoard[My][Mx] = 'O';
					playerBoard[My+1][Mx] = 'O';
				}
				else if (Mdirection == LEFT) {
					playerBoard[My][Mx] = 'O';
					playerBoard[My][Mx-1] = 'O';
				}
			}
		} 
		
		// Draws updated player board
		drawBoard(PLAYER, playerBoard);
		
		// Small boat
		valid = 0;
		while (!valid) {
			Sx = 10;
			Sy = 10;
			
			// Gets user input
			while ( Sx > 4 && Sy > 4) {
				mvprintw(16, 0, "%s", "Enter a valid coordinate(0-4) for your short boat:                       ");
				mvprintw(17, 0, "%s", "               ");
				mvprintw(17, 0, "%s", "x,y = ");
				refresh();
				scanw("%d,%d", &Sx, &Sy);
				mvprintw(17, 15, "%s", "              ");
			}
			
			// Checks if input is valid
			if (playerBoard[Sy][Sx] == 'O' || playerBoard[Sy][Sx] == 'O') {
				valid = 0;
			}
			else {
				valid = 1;
			}
			
			// If the input is valid, input boat into array
			if (valid) {
				playerBoard[Sy][Sx] = 'O';
			}
		}
		
		// Draws updated player board
		drawBoard(PLAYER, playerBoard);
	
	// Loop for player's and computer's turn
	while (TRUE) {
		
		// Clears screen
		for (i = 0; i < 50; i++) {
			mvprintw(16, i, "%c", ' ');
			mvprintw(17, i, "%c", ' ');
		}
		refresh();
		
		Gx = 10;
		Gy = 10;
		
		// Changes turn
		mvprintw(6, 8, "%c", '>');
		mvprintw(7, 8, "%c", ' ');
		refresh();

		// Gets user guess
		while ( Gx > 4 && Gy > 4) {
			mvprintw(16, 0, "%s", "Enter a valid coordinate(0-4) for your guess: ");
			mvprintw(17, 0, "%s", "x,y = ");
			refresh();
			scanw("%d,%d", &Gx, &Gy);
			mvprintw(17, 6, "%s", "       ");
		}
		
		// Checks if user guess was a hit or not and updates board
		if (computerBoard[Gy][Gx] == 'O' || computerBoard[Gy][Gx] == 'X') {
			computerBoard[Gy][Gx] = 'X';
			playerGuessedBoard[Gy][Gx] = 'X';
		}
		else {
			computerBoard[Gy][Gx] = '+';
			playerGuessedBoard[Gy][Gx] = '+';
		}
		
		// Draws updated board
		if (SHOW) {
		drawBoard(COMPUTER, computerBoard);
		}
		else {
			drawBoard(GUESSED, playerGuessedBoard);
		}
		refresh();
		
		// If player won, exit game
		if( loseTest(computerBoard) ) {
			Sleep(1000);
			whoWon = PLAYER;
			break;
		}
		
		// Delays Computer's turn
		mvprintw(6, 8, "%c", ' ');
		mvprintw(7, 8, "%c", '>');
		refresh();
		Sleep(1000);
		
		// Random computer guess, guesses don't repeat
		Gx = rand() % 5;
		Gy = rand() % 5;
		while (computerGuessedBoard[Gy][Gx] != '-') {
			Gx = rand() % 5;
			Gy = rand() % 5;
		}
		computerGuessedBoard[Gy][Gx] = '+';
		
		// Checks if computer guess was a hit or not and updates board
		if (playerBoard[Gy][Gx] == 'O' || playerBoard[Gy][Gx] == 'X') {
			playerBoard[Gy][Gx] = 'X';
		}
		else {
			playerBoard[Gy][Gx] = '+';
		}
		
		// Draws updated board
		drawBoard(PLAYER, playerBoard);
		refresh();
		
		// If computer won, exit game
		if (loseTest(playerBoard)) {
			Sleep(1000);
			whoWon = COMPUTER;
			break;
		}
		
	}
	
	// Ends game, prints winner
	endwin();
	if (whoWon == PLAYER) {
		printf("\n\n\n\n\n\t\aYOU WON\n\n\n\n\n");
	}
	else {
		printf("\n\n\n\n\n\t\aCOMPUTER WON\n\n\n\n\n");
	}
	
	return 0;
}


// Function to randomly generate the computer's board
void genComputerBoard(char board[ROWS][COLM]) {
	int valid = 0;
	int Lx, Ly, Ldirection;
	int Mx, My, Mdirection;
	int Sx, Sy;
	srand(time(NULL));
	
	// Long boat
	
	// Gets random starting position for long boat
	Ly = rand() % 5;
	Lx = rand() % 5;
	
	// Generates a random direction for boat and checks if it is possible
	// If it is not possible, it generates a new direction
	while (!valid) {
		Ldirection = rand()%4;
		if ((Ly == 0 && Lx == 0) || (Ly == 0 && Lx == 1) || (Ly == 1 && Lx == 0) || (Ly == 1 && Lx == 1) ) {
			if (Ldirection == RIGHT || Ldirection == DOWN) {
				valid = 1;
			}
		}
		if ((Ly == 2 && Lx == 0) || (Ly == 2 && Lx == 1)) {
			if (Ldirection == UP || Ldirection == 1 || Ldirection == DOWN) {
				valid = 1;
			}
		}
		if ((Ly == 3 && Lx == 0) || (Ly == 3 && Lx == 1) || (Ly == 4 && Lx == 0) || (Ly == 4 && Lx == 1)) {
			if (Ldirection == UP || Ldirection == RIGHT) {
				valid = 1;
			}
		}
		if ((Ly == 0 && Lx == 2) || (Ly == 1 && Lx == 2)) {
			if (Ldirection == RIGHT || Ldirection == DOWN || Ldirection == LEFT) {
				valid = 1;
			}
		}
		if (Ly == 2 && Lx == 2) {
			valid = 1;
		}
		if ((Ly == 3 && Lx == 2) || (Ly == 4 && Lx == 2)) {
			if (Ldirection == UP || Ldirection == RIGHT || Ldirection == LEFT) {
				valid = 1;
			}
		}
		if ((Ly == 0 && Lx == 3) || (Ly == 0 && Lx == 4) || (Ly == 1 && Lx == 3) || (Ly == 1 && Lx == 4)) {
			if (Ldirection == DOWN || Ldirection == LEFT) {
				valid = 1;
			}
		}
		if ((Ly == 2 && Lx == 3) || (Ly == 2 && Lx == 4)) {
			if (Ldirection = 0 || Ldirection == DOWN || Ldirection == LEFT) {
				Ldirection = (rand()%3)+1;
				if (Ldirection == RIGHT) {
					Ldirection = UP;
				}
				valid = 1;
			}
		}
		if ((Ly == 3 && Lx == 3) || (Ly == 3 && Lx == 4) || (Ly == 4 && Lx == 3) || (Ly == 4 && Lx == 4)) {
			if (Ldirection == UP || Ldirection == LEFT) {
				valid = 1;
			}
		}
	}
	
	// Inserts the boat into array
	if (Ldirection == UP) {
		board[Ly][Lx] = 'O';
		board[Ly-1][Lx] = 'O';
		board[Ly-2][Lx] = 'O';
	}
	else if (Ldirection == RIGHT) {
		board[Ly][Lx] = 'O';
		board[Ly][Lx+1] = 'O';
		board[Ly][Lx+2] = 'O';
	}
	else if (Ldirection == DOWN) {
		board[Ly][Lx] = 'O';
		board[Ly+1][Lx] = 'O';
		board[Ly+2][Lx] = 'O';
	}
	else if (Ldirection == LEFT) {
		board[Ly][Lx] = 'O';
		board[Ly][Lx-1] = 'O';
		board[Ly][Lx-2] = 'O';
	}


	// Medium boat
	
	// Gets initial random starting position for long boat
	My = rand() % 5;
	Mx = rand() % 5;
	valid = 0;
	
	// Makes sure medium boat doesn't start on long boat
	while (!valid){
		if (board[My][Mx] == 'O') {
			My = rand() % 5;
			Mx = rand() % 5;
		}
		else {
			valid = 1;
		}
	}
	
	// Generates a random direction for boat and checks if it is possible
	// If it is not possible, it generates a new direction
	valid = 0;
	while (!valid) {
		Mdirection = rand()%4;
		if ((My == 0 && Mx == 0)) {
			if (Mdirection == RIGHT || Mdirection == DOWN) {
				if (Mdirection == RIGHT && board[My][Mx+1] != 'O') {
					valid = 1;
				}
				else if (Mdirection == DOWN && board[My+1][Mx] != 'O') {
					valid = 1;
				}
			}
		}
		if ((My == 1 && Mx == 0) || (My == 2 && Mx == 0) || (My == 3 && Mx == 0)) {
			if (Mdirection == UP || Mdirection == RIGHT || Mdirection == DOWN) {
				if (Mdirection == RIGHT && board[My][Mx+1] != 'O') {
					valid = 1;
				}
				else if (Mdirection == DOWN && board[My+1][Mx] != 'O') {
					valid = 1;
				}
				else if (Mdirection == UP && board[My-1][Mx] != 'O') {
					valid = 1;
				}
			}
		}
		if ((My == 4 && Mx == 0)) {
			if (Mdirection == UP || Mdirection == RIGHT) {
				if (Mdirection == RIGHT && board[My][Mx+1] != 'O') {
					valid = 1;
				}
				else if (Mdirection == UP && board[My-1][Mx] != 'O') {
					valid = 1;
				}
			}
		} 
		if ((My == 0 && Mx == 1) || (My == 0 && Mx == 2) || (My == 0 && Mx == 3)) {
			if (Mdirection == RIGHT || Mdirection == DOWN || Mdirection == LEFT) {
				if (Mdirection == RIGHT && board[My][Mx+1] != 'O') {
					valid = 1;
				}
				else if (Mdirection == DOWN && board[My+1][Mx] != 'O') {
					valid = 1;
				}
				else if (Mdirection == LEFT && board[My][Mx-1] != 'O') {
					valid = 1;
				}
			}
		}
		if ((My == 1 && Mx == 1) || (My == 1 && Mx == 2) || (My == 1 & Mx == 3) || (My == 2 && Mx == 1) || (My == 2 && Mx == 2) || (My == 2 && Mx == 3) || (My == 3 && Mx == 1) || (My == 3 && Mx == 2) || (My == 3 && Mx == 3)) {
			if (Mdirection == RIGHT && board[My][Mx+1] != 'O') {
					valid = 1;
			}
			else if (Mdirection == DOWN && board[My+1][Mx] != 'O') {
					valid = 1;
				}
			else if (Mdirection == LEFT && board[My][Mx-1] != 'O') {
				valid = 1;
			}
			else if (Mdirection == UP && board[My-1][Mx] != 'O') {
					valid = 1;
			}
		}
		if ((My == 4 && Mx == 1) || (My == 4 && Mx == 2) || (My == 4 && Mx == 3)) {
			if (Mdirection == UP || Mdirection == RIGHT || Mdirection == LEFT) {
				if (Mdirection == RIGHT && board[My][Mx+1] != 'O') {
					valid = 1;
				}
				else if (Mdirection == LEFT && board[My][Mx-1] != 'O') {
					valid = 1;
				}
				else if (Mdirection == UP && board[My-1][Mx] != 'O') {
					valid = 1;
				}
			}
		}
		if (((My == 0 && Mx == 4))) {
			if (Mdirection == DOWN || Mdirection == LEFT) {
				if (Mdirection == DOWN && board[My+1][Mx] != 'O') {
					valid = 1;
				}
				else if (Mdirection == LEFT && board[My][Mx-1] != 'O') {
					valid = 1;
				}
			}
		}
		if ((My == 1 && Mx == 4) || (My == 2 && Mx == 4) || (My == 3 && Mx == 4)) {
			if (Mdirection = UP || Mdirection == DOWN || Mdirection == LEFT) {
				Mdirection = (rand()%3)+1;
				if (Mdirection == RIGHT) {
					Mdirection = UP;
				}
				if (Mdirection == DOWN && board[My+1][Mx] != 'O') {
					valid = 1;
				}
				else if (Mdirection == LEFT && board[My][Mx-1] != 'O') {
					valid = 1;
				}
				else if (Mdirection == UP && board[My-1][Mx] != 'O') {
					valid = 1;
				}
			}
		}
		if ((My == 4 && Mx == 4)) {
			if (Mdirection == UP || Mdirection == LEFT) {
				if (Mdirection == LEFT && board[My][Mx-1] != 'O') {
				valid = 1;
				}
				else if (Mdirection == UP && board[My-1][Mx] != 'O') {
					valid = 1;
				}
			}
		}
	}
	
	// Inserts the boat into array
	if (Mdirection == UP) {
		board[My][Mx] = 'O';
		board[My-1][Mx] = 'O';
	}
	else if (Mdirection == RIGHT) {
		board[My][Mx] = 'O';
		board[My][Mx+1] = 'O';
	}
	else if (Mdirection == DOWN) {
		board[My][Mx] = 'O';
		board[My+1][Mx] = 'O';
	}
	else if (Mdirection == LEFT) {
		board[My][Mx] = 'O';
		board[My][Mx-1] = 'O';
	}
	
	// Short boat
	
	// Gets initial random starting position for long boat
	Sy = rand() % 5;
	Sx = rand() % 5;
	valid = 0;
	
	// Makes sure short boat isn't on other boats
	while (!valid){
		if (board[Sy][Sx] == 'O' || board[Sy][Sx] == 'O') {
			Sy = rand() % 5;
			Sx = rand() % 5;
		}
		else {
			valid = 1;
		}
	}
	
	// Inserts the boat into array
	board[Sy][Sx] = 'O'; 
}


// Draws the given board on the screen
void drawBoard(int which, char board[ROWS][COLM]) {
	int i,j;
	
	// Prints player board
	mvprintw(7, 31, "%s", "PLAYER'S");
	refresh();
	if (which == PLAYER) {
		for ( i = 0; i < ROWS; i++ ) {
			for ( j = 0; j < COLM; j++ ) {
				mvprintw(i+8, j+32, "%c", board[i][j]);
				refresh();
			}
		}	
	}
	
	// Prints computer board
	mvprintw(0, 30, "%s", "COMPUTER'S");
	refresh();
	if (which == COMPUTER) {
		for ( i = 0; i < ROWS; i++ ) {
			for ( j = 0; j < COLM; j++ ) {
				mvprintw(i+1, j+32, "%c", board[i][j]);
				refresh();
			}
		}
	}
	
	// Prints guessed board
	mvprintw(0, 30, "%s", "COMPUTER'S");
	refresh();
	if (which == GUESSED) {
		for ( i = 0; i < ROWS; i++ ) {
			for ( j = 0; j < COLM; j++ ) {
				mvprintw(i+1, j+32, "%c", board[i][j]);
				refresh();
			}
		}
	}
}


// Checks if a player has lost or not
// return 1 or true = that player lost
// return 0 or false = that player has not lost
int loseTest (char board[ROWS][COLM]) {
	int i, j, oCount = 0;
	
	// Checks if there are any O's in the board
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLM; j++) {
			
			if (board[i][j] == 'O') {
				oCount++;
			}
			
		}
	}
	
	// No 'O's = player lost
	if (oCount == 0) {
		return 1;
	}
	// 'O's = still in the game
	else {
		return 0;
	}
}

// the end 