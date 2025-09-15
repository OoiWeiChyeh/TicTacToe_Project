#pragma once

// Constants
const int BOARD_SIZE = 3;
const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

// Function declarations
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void displayBoard(const char board[BOARD_SIZE][BOARD_SIZE]);
bool isValidMove(const char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
void makeMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, char player);
bool checkWin(const char board[BOARD_SIZE][BOARD_SIZE], char player);
bool checkDraw(const char board[BOARD_SIZE][BOARD_SIZE]);
void switchPlayer(char &currentPlayer);
