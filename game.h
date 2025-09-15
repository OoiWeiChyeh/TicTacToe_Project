#pragma once

#include <string>
#include <vector>
#include <map>

// Constants
const int BOARD_SIZE = 3;
const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

// Game difficulty levels
enum class Difficulty { EASY, MEDIUM, HARD };

// Player structure to track scores
struct Player {
    std::string name;
    int wins;
    int losses;
    int draws;
};

class Game {
private:
    char board[BOARD_SIZE][BOARD_SIZE];
    char currentPlayer;
    bool vsAI;
    Difficulty aiDifficulty;
    std::map<std::string, Player> leaderboard;
    std::string player1Name;
    std::string player2Name;
    
    // Core game functions
    void initializeBoard();
    bool isValidMove(int row, int col) const;
    void makeMove(int row, int col);
    bool checkWin(char player) const;
    bool checkDraw() const;
    void switchPlayer();
    
    // AI functions
    void makeAIMove();
    std::pair<int, int> findBestMove();
    int minimax(int depth, bool isMaximizing);
    std::pair<int, int> findRandomMove() const;
    std::pair<int, int> findWinningMove(char player) const;
    std::pair<int, int> findBlockingMove() const;
    
    // UI functions
    void clearScreen() const;
    void displayBoard() const;
    void displayStatus() const;
    
    // Utility functions
    void updateLeaderboard(const std::string& name, bool won, bool draw = false);
    void saveLeaderboard() const;
    void loadLeaderboard();
    
public:
    Game();
    
    // Main game flow
    void showMainMenu() const;
    void startNewGame(bool againstAI);
    void showLeaderboard() const;
    void showHelp() const;
};
