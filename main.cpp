#include <iostream>
#include "game.h"

using namespace std;

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    char currentPlayer = PLAYER_X;
    bool gameOver = false;
    int row, col;
    
    // Initialize the board
    initializeBoard(board);
    
    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "Player 1: X, Player 2: O\n";
    cout << "Enter row and column numbers (0-2) to make your move.\n\n";
    
    // Main game loop
    while (!gameOver) {
        // Display the current board
        displayBoard(board);
        
        // Get player input
        cout << "Player " << currentPlayer << ", enter your move (row column): ";
        cin >> row >> col;
        
        // Validate and make the move
        if (isValidMove(board, row, col)) {
            makeMove(board, row, col, currentPlayer);
            
            // Check for win
            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                cout << "Player " << currentPlayer << " wins!\n";
                gameOver = true;
            } 
            // Check for draw
            else if (checkDraw(board)) {
                displayBoard(board);
                cout << "It's a draw!\n";
                gameOver = true;
            } 
            // Continue the game
            else {
                switchPlayer(currentPlayer);
            }
        } else {
            cout << "Invalid move. Please try again.\n";
        }
    }
    
    cout << "Thanks for playing!\n";
    return 0;
}
