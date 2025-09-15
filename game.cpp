#include <iostream>
#include "game.h"

using namespace std;

// Initialize the board with empty spaces
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Display the current state of the board
void displayBoard(const char board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "\n   |   |   \n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " \n";
        if (i < BOARD_SIZE - 1) {
            cout << "___|___|___\n";
        }
        cout << "   |   |   \n";
    }
    cout << "\n";
}

// Check if a move is valid
bool isValidMove(const char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == EMPTY);
}

// Make a move on the board
void makeMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, char player) {
    board[row][col] = player;
}

// Check if a player has won
bool checkWin(const char board[BOARD_SIZE][BOARD_SIZE], char player) {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    
    return false;
}

// Check if the game is a draw
bool checkDraw(const char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

// Switch the current player
void switchPlayer(char &currentPlayer) {
    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
}
