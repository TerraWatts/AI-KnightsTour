//*********************************************************
// Title: Knight's Tour with AI Heuristic Strategy
// Author: Watts Dietrich
// CS 121 Section 001
// Date: March 11, 2010
//*********************************************************
// Description: This program attempts to find a solution to the Knight's tour problem using an AI Heuristic Strategy.
//	For each tour simulated, a random starting position is chosen on a virtual 8x8 chess board. The program assigns 
//	accessiblility values to each square, setting this value to the number available moves to that square. The progran then
//	finds valid moves for the knight and moves to the square with the least accessibility value. If there is more than one such
//	move available, the program chooses randomly between them.

//	When run, the program gives the user a choice between running one tour or running 64 tours. If the user chooses to run
//	just one tour, each move is displayed and the move order is displayed upon completion. If the user chooses 64 tours, the program
//	runs one simulation for each possible starting square. If the program fails to find a complete tour, the end configuration of the board
//	is displayed. Upon completion, the program displays statistics about the 64 tours number of successful and unsuccessful tours, 
//	number of closed tours).

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// function prototypes
void displayBoard(char board[8][8]);
void displayMoves(int moves[8][8]);
void displayAccess(int access[8][8]);
void accessArray(int access[8][8], bool beenThere[8][8], int xChange[8], int yChange[8]);
bool doneCheck(int curRow, int curCol, bool beenThere[8][8], int xChange[8], int yChange[8]);
void makeMove(int &curRow, int &curCol, int &newRow, int &newCol, bool beenThere[8][8], int access[8][8], int xChange[8], int yChange[8]);
void tourCheck( int moves[8][8], bool beenThere[8][8], char board[8][8], int &complete, int &incomplete,int choice, int tour);
void closedTourCheck(int curRow, int curCol, int startX, int startY, int xChange[8], int yChange[8], bool &closed);


int main()
{
	srand( time(0) ); // seeds number generator

	//Variables
	char board[8][8]; // represents chess board
	int moves[8][8]; // array to hold move order
	int access[8][8]; // array to hold accessibility values
	int moveCounter = 1; // counter to keep track of move number
	bool beenThere[8][8] = {false}; // array to keep track of squares visited by knight
	bool done = false;
	bool closed = false;
	int newRow=-1; 
	int newColumn=-1; 
	int choice;
	int xChange[] = {1,2,2,1,-1,-2,-2,-1}; // xChange and yChange arrays represent the eight possible movement combinations
	int yChange[] = {-2,-1,1,2,2,1,-1,-2};
	int complete = 0; // Counter tracks number of complete tours
	int incomplete = 0; // Counter tracks number of incomplete tours

	for( int a = 0; a < 8; ++a ) // initializes board array to all dash characters, move and accessability arrays to all zeros. 
	{
		for( int b = 0; b < 8; ++b )
		{
			board[a][b] = '-';
			moves[a][b] = 0;
			access[a][b] = 0;
		}
	}
	cout << "Select option 1 or 2:" << endl << "1. Run one tour, display each move, display move order upon completion" << endl << "2. Run 64 tours, one for each possible starting square, display results" << endl;
	cin >> choice;

	if (choice == 1) // Runs one tour
	{
		int tour = 0;
		int currentRow = rand() % 8; //current y coordinate of knight
		int currentColumn = rand() % 8; //current x coordinate
		while ( done != true ) // loop executes for each move as long as valid moves remain
		{
			accessArray(access, beenThere, xChange, yChange);		
			cout << "\nMove" << moveCounter << endl;
			moveCounter++;		
			makeMove(currentRow, currentColumn, newRow, newColumn, beenThere, access, xChange, yChange);		
			board[currentRow][currentColumn] = 'x'; 
			board[newRow][newColumn] = 'K'; 
			currentRow = newRow;
			currentColumn = newColumn;
			beenThere[currentRow][currentColumn] = true;
			moves[newRow][newColumn] = moveCounter;
			displayBoard(board);
//			displayMoves(moves);	// unneccessary display functions previously used for debugging commented out
//			displayAccess(access);
			for(int a = 0; a < 10000; ++a)	// Pause momentarily between moves
				for(int b = 0; b < 10000; ++b);
			done = doneCheck(currentRow, currentColumn, beenThere, xChange, yChange); // calls function to check if valid moves remain
		}
		tourCheck(moves, beenThere, board, complete, incomplete, choice, tour);
	}
	if (choice == 2) // Runs 64 tours, one for each possible starting square
	{
		int tour = 0;
		int totalMoves = 0;
		int closedCount = 0;
		for (int startY = 0; startY < 8; ++startY)
			for (int startX = 0; startX < 8; ++startX)
			{
				++tour;
				int currentRow = startY; //starting y coordinate of knight
				int currentColumn = startX; //starting x coordinate
				moveCounter = 1;
				bool done = false;
				bool closed = false;
				for( int a = 0; a < 8; ++a ) // initializes board array to all dash characters, move and accessability arrays to all zeros. 
				{
					for( int b = 0; b < 8; ++b )
					{
						board[a][b] = '-';
						moves[a][b] = 0;
						access[a][b] = 0;
						beenThere[a][b] = false;
					}
				}				
				while ( done != true ) // loop executes for each move as long as valid moves remain
				{
					accessArray(access, beenThere, xChange, yChange);					
					moveCounter++;		
					makeMove(currentRow, currentColumn, newRow, newColumn, beenThere, access, xChange, yChange);		
					board[currentRow][currentColumn] = 'x'; 
					board[newRow][newColumn] = 'K'; 
					currentRow = newRow;
					currentColumn = newColumn;
					beenThere[currentRow][currentColumn] = true;
					done = doneCheck(currentRow, currentColumn, beenThere, xChange, yChange); // calls function to check if valid moves remain
				}
				closedTourCheck(currentRow, currentColumn, startX, startY, xChange, yChange, closed);
				if (closed == true)
					closedCount++;

				cout << endl;
				tourCheck(moves, beenThere, board, complete, incomplete, choice, tour);				
			}
			cout << "\n\nResults of 64 tours" << endl << "**************************" << endl << "Number of successfully completed tours: " << complete << endl;
			cout << "Number of closed tours: " << closedCount << endl << "Number of incomplete tours: " << incomplete << endl; // Prints number of complete and incomplete tours
	}	
	
} // End main


void displayBoard(char board[8][8]) // Displays board array
{
	for( int a = 0; a < 8; ++a )
	{
		for( int b = 0; b < 8; ++b )
		{
			cout << board[a][b];
		}
		cout << endl;
	}
}

void displayMoves(int moves[8][8]) // Displays move order array
{
	for( int a = 0; a < 8; ++a )
		{
			for( int b = 0; b < 8; ++b )
			{
				if( moves[a][b] == 0 || moves[a][b] < 10)
					cout << "0";
				cout << moves[a][b] << " ";
			}
			cout << endl << endl;
		}
}

void displayAccess(int access[8][8]) // Displays accessibility values array
{
	for( int a = 0; a < 8; ++a ) 
	{
		for( int b = 0; b < 8; ++b )
		{
			cout << access[a][b];
		}
		cout << endl;
	}
}

void accessArray(int access[8][8], bool beenThere[8][8], int xChange[8], int yChange[8]) // Finds accessibility values
{
	for( int a = 0; a < 8; ++a ) // For each square on the board, finds number of valid moves to that square
	{
		for( int b = 0; b < 8; ++b )
		{
			int validCount = 0;

			for( int c = 0; c < 8; ++c) // Checks validity of each possible move
			{
				int newRow = a + yChange[c];
				int newCol = b + xChange[c];
				if(newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && beenThere[newRow][newCol] == false)
					++validCount;
			}
			access[a][b] = validCount; // Accessibility rating = number of valid moves to the square
		}
	}		
}

bool doneCheck(int curRow, int curCol, bool beenThere[8][8], int xChange[8], int yChange[8]) // Checks to see if any valid moves remain
{
	int validMoves = 0; // Tracks number of valid moves
	for( int c = 0; c < 8; ++c) // Runs through all eight possible movements, checks to see how many are valid.
	{
		int newRow = curRow + yChange[c];
		int newCol = curCol + xChange[c];
		if(newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && beenThere[newRow][newCol] == false)
			validMoves++;
	}
	if( validMoves == 0)
		return true;
	else
		return false;
}

void makeMove(int &curRow, int &curCol, int &newRow, int &newCol, bool beenThere[8][8], int access[8][8], int xChange[8], int yChange[8]) // Makes moves based on accessibility values.
{
	int accessValues[8] ;
	for( int c = 0; c < 8; ++c) // Finds accessibility value for each valid move, stores values in array accessValues
	{
		int newRow = curRow + yChange[c];
		int newCol = curCol + xChange[c];
		if(newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && beenThere[newRow][newCol] == false)
			accessValues[c] = access[newRow][newCol];
		else
			accessValues[c] = 9;		
	}
	int lowest = 9;
	int moveCount = 0;

	for( int c = 0; c < 8; ++c) // Finds lowest accessibility value out of all valid moves
	{
		if( accessValues[c] < lowest)
			lowest = accessValues[c]; 
	}	

	for( int c = 0; c < 8; ++c) // finds number of moves that share the lowest accessibility
	{
		if( accessValues[c] == lowest)
			moveCount++; 
	}

	int coin = rand() % (moveCount); // chooses random number based on number of available moves with lowest accessibility rating
	int moveNum = -1;
	for( int c = 0; c < 8; ++c) // Moves knight to square with lowest access value. If there are multiple moves that share the lowest access value, chooses randomly between them.
	{
		if ( accessValues[c] == lowest )
		{
			moveNum++;
			if (moveNum == coin)
			{
				newRow = curRow + yChange[c];
				newCol = curCol + xChange[c];
			}				
		}
	}
}

void tourCheck( int moves[8][8], bool beenThere[8][8], char board[8][8], int &complete, int &incomplete, int choice, int tour) //Checks to see if tour was completed, increments complete or incomplete counter 
{
	bool tourDone = true;
	for (int a = 0; a < 8; ++a) // Loop checks if all squares have been visited to see if tour was completed.
	{
		for ( int b = 0; b < 8; ++b)
		{
			if (beenThere[a][b] == false)
			{
				tourDone = false;
			}
		}		
	}
	if (tourDone == true) // When tour completed, displays move order
	{
		complete++;
		if (choice == 1) //For one tour
		{
			cout << "\nMove order:" << endl;
			displayMoves(moves);
			cout << "\nKnight's tour successfully completed!"<<endl;
			
		}
		if (choice == 2) //For 64 tours
		{
			cout << "Tour " << tour << " completed successfully";
			for(int a = 0; a < 10000; ++a)	// Pause momentarily between moves
				for(int b = 0; b < 1000; ++b);
		}

	}
	else // Informs user of failure to complete tour
	{	
		incomplete ++;
		if (choice == 1) //For one tour
		{
			cout << "Knight's tour unsuccessful, no further valid moves."<<endl <<endl;
		}		
		if (choice == 2) //For 64 tours
		{
			cout << "Tour " << tour << " unsuccessfull." << endl << "End configuration of board for unsuccessful tour: " << endl;
			displayBoard(board); // Display board for unsuccessful tours 
			for(int a = 0; a < 10000; ++a)	// Pause 
				for(int b = 0; b < 100000; ++b);
		}
	}
}

void closedTourCheck(int curRow, int curCol, int startX, int startY, int xChange[8], int yChange[8], bool &closed) // Checks for closed tours
{
	for(int a = 0; a < 8; ++a)		
	{
		if((startX + xChange[a] == curCol) && (startY + yChange[a] == curRow))
		{
			closed = true;
		}
	}
}