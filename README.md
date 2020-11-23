# AI-KnightsTour
A C++ program I wrote in college wherein an AI heuristic strategy is used to reliably solve the knight's tour challenge.

Description: This program attempts to find a solution to the Knight's tour problem using an AI Heuristic Strategy.
For each tour simulated, a random starting position is chosen on a virtual 8x8 chess board. The program assigns 
accessiblility values to each square, setting this value to the number available moves to that square. The progran then
finds valid moves for the knight and moves to the square with the least accessibility value. If there is more than one such
move available, the program chooses randomly between them.

When run, the program gives the user a choice between running one tour or running 64 tours. If the user chooses to run
just one tour, each move is displayed and the move order is displayed upon completion. If the user chooses 64 tours, the program
runs one simulation for each possible starting square. If the program fails to find a complete tour, the end configuration of the board
is displayed. Upon completion, the program displays statistics about the 64 tours number of successful and unsuccessful tours, 
number of closed tours).

I would love to build an actual GUI for this at some point, but for now it just runs in the command prompt and draws the chess board with 
ASCII characters.
