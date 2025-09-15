#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>
#include <locale>
#include "game.h"

using namespace std;

// Constructor: Initialize game state
Game::Game() : currentPlayer(PLAYER_X), vsAI(false), aiDifficulty(Difficulty::MEDIUM) {
    initializeBoard();
    loadLeaderboard();
}

// Initialize the game board with empty spaces
void Game::initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Clear the console screen
void Game::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Display the game board with visual enhancements
void Game::displayBoard() const {
    cout << "\n    1   2   3\n";
    cout << "  +-----------+\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i+1 << " ¦ ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Add color to X and O
            if (board[i][j] == PLAYER_X) {
                cout << "\033[1;34m" << board[i][j] << "\033[0m"; // Blue for X
            } else if (board[i][j] == PLAYER_O) {
                cout << "\033[1;31m" << board[i][j] << "\033[0m"; // Red for O
            } else {
                cout << board[i][j];
            }
            cout << " ¦ ";
        }
        cout << "\n";
        if (i < BOARD_SIZE - 1) {
            cout << "  ¦---+---+---¦\n";
        }
    }
    cout << "  +-----------+\n\n";
}

// Display current game status
void Game::displayStatus() const {
    string currentPlayerName;
    if (currentPlayer == PLAYER_X) {
        currentPlayerName = player1Name;
    } else {
        currentPlayerName = vsAI ? "AI" : player2Name;
    }
    
    cout << "Current player: " << currentPlayerName << " (" << currentPlayer << ")\n";
}

// Check if a move is valid
bool Game::isValidMove(int row, int col) const {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == EMPTY);
}

// Make a move on the board
void Game::makeMove(int row, int col) {
    board[row][col] = currentPlayer;
}

// Check if a player has won
bool Game::checkWin(char player) const {
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
bool Game::checkDraw() const {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

// Switch to the other player
void Game::switchPlayer() {
    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

// Get a validated player name with support for Indian names
string Game::getPlayerName(const string& prompt) {
    string name;
    while (true) {
        cout << prompt;
        getline(cin, name);
        
        // Remove leading/trailing whitespace
        size_t start = name.find_first_not_of(" \t\n\r");
        if (start == string::npos) {
            cout << "Name cannot be empty. Please enter a valid name: ";
            continue;
        }
        
        size_t end = name.find_last_not_of(" \t\n\r");
        name = name.substr(start, end - start + 1);
        
        // Check if name is valid (allows letters, spaces, and common Indian name characters)
        bool valid = true;
        bool hasLetter = false;
        
        for (char c : name) {
            // Allow letters, spaces, apostrophes, hyphens, periods, and slashes (for Indian names)
            if (!isalpha(c) && c != ' ' && c != '\'' && c != '-' && c != '.' && c != '/') {
                valid = false;
                break;
            }
            if (isalpha(c)) {
                hasLetter = true;
            }
        }
        
        if (!valid) {
            cout << "Name can only contain letters, spaces, apostrophes, hyphens, periods, and slashes. Please try again:\n";
            continue;
        }
        
        if (!hasLetter) {
            cout << "Name must contain at least one letter. Please try again:\n ";
            continue;
        }
        
        if (name.length() < 1 || name.length() > 20) {
            cout << "Name must be between 1 and 20 characters. Please try again:\n ";
            continue;
        }
        
        break;
    }
    return name;
}

// Get validated integer input within a range
int Game::getValidatedInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            continue;
        }
        
        // Clear the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (value < min || value > max) {
            cout << "Please enter a number between " << min << " and " << max << ".\n";
            continue;
        }
        
        break;
    }
    return value;
}

// Wait for user to press Enter
void Game::waitForEnter() const {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Display the main menu
void Game::showMainMenu() const {
    clearScreen();
    cout << "========================================\n";
    cout << "           TIC-TAC-TOE                  \n";
    cout << "========================================\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs AI\n";
    cout << "3. View Leaderboard\n";
    cout << "4. Help & Instructions\n";
    cout << "5. Exit\n";
    cout << "========================================\n";
}

// Start a new game
void Game::startNewGame(bool againstAI) {
    vsAI = againstAI;
    initializeBoard();
    currentPlayer = PLAYER_X;
    
    // Get player names
    if (player1Name.empty()) {
        player1Name = getPlayerName("Enter Player 1 (X) name: ");
        if (leaderboard.find(player1Name) == leaderboard.end()) {
            leaderboard[player1Name] = {player1Name, 0, 0, 0};
        }
    }
    
    if (againstAI) {
        player2Name = "AI";
        // Select AI difficulty
        int diffChoice = getValidatedInput("Select AI difficulty (1-Easy, 2-Medium, 3-Hard): ", 1, 3);
        
        if (diffChoice == 1) aiDifficulty = Difficulty::EASY;
        else if (diffChoice == 3) aiDifficulty = Difficulty::HARD;
        else aiDifficulty = Difficulty::MEDIUM;
    } else {
        if (player2Name.empty() || player2Name == "AI") {
            player2Name = getPlayerName("Enter Player 2 (O) name: ");
        }
        if (leaderboard.find(player2Name) == leaderboard.end()) {
            leaderboard[player2Name] = {player2Name, 0, 0, 0};
        }
    }
    
    // Game loop
    bool gameOver = false;
    
    while (!gameOver) {
        clearScreen();
        displayBoard();
        displayStatus();
        
        if (vsAI && currentPlayer == PLAYER_O) {
            // AI's turn
            cout << "AI is thinking...\n";
            #ifdef _WIN32
                system("timeout 1 >nul");
            #else
                system("sleep 1");
            #endif
            makeAIMove();
        } else {
            // Player's turn
            int row = getValidatedInput("Enter row (1-3): ", 1, 3);
            int col = getValidatedInput("Enter column (1-3): ", 1, 3);
            
            // Convert to 0-based index
            row--;
            col--;
            
            if (!isValidMove(row, col)) {
                cout << "That position is already taken. Please try again.\n";
                waitForEnter();
                continue;
            }
            
            makeMove(row, col);
        }
        
        // Check for win
        if (checkWin(currentPlayer)) {
            clearScreen();
            displayBoard();
            string winnerName = (currentPlayer == PLAYER_X) ? player1Name : player2Name;
            cout << "?? Player " << winnerName << " wins! ??\n";
            
            // Update leaderboard
            if (currentPlayer == PLAYER_X) {
                updateLeaderboard(player1Name, true);
                if (!vsAI) updateLeaderboard(player2Name, false);
            } else {
                if (vsAI) {
                    cout << "The AI wins! Better luck next time.\n";
                } else {
                    updateLeaderboard(player2Name, true);
                }
                updateLeaderboard(player1Name, false);
            }
            
            gameOver = true;
        } 
        // Check for draw
        else if (checkDraw()) {
            clearScreen();
            displayBoard();
            cout << "It's a draw!\n";
            
            // Update leaderboard
            updateLeaderboard(player1Name, false, true);
            if (!vsAI) updateLeaderboard(player2Name, false, true);
            
            gameOver = true;
        } 
        // Continue the game
        else {
            switchPlayer();
        }
    }
    
    // Ask to play again
    char playAgain;
    cout << "\nWould you like to play again? (y/n): ";
    cin >> playAgain;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (tolower(playAgain) == 'y') {
        startNewGame(vsAI);
    } else {
        saveLeaderboard();
    }
}

// AI makes a move based on difficulty
void Game::makeAIMove() {
    pair<int, int> move;
    
    switch (aiDifficulty) {
        case Difficulty::EASY:
            // 70% random moves, 30% smart moves
            if (rand() % 10 < 7) {
                move = findRandomMove();
            } else {
                move = findBestMove();
            }
            break;
            
        case Difficulty::MEDIUM:
            // Try to win, then block, then make a good move
            move = findWinningMove(PLAYER_O);
            if (move.first == -1) {
                move = findWinningMove(PLAYER_X); // Block
                if (move.first == -1) {
                    move = findBestMove();
                }
            }
            break;
            
        case Difficulty::HARD:
            // Always use minimax for best move
            move = findBestMove();
            break;
    }
    
    makeMove(move.first, move.second);
    cout << "AI chose position: " << move.first+1 << " " << move.second+1 << endl;
}

// Find the best move using minimax algorithm
pair<int, int> Game::findBestMove() {
    int bestScore = -1000;
    pair<int, int> bestMove = {-1, -1};
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_O;
                int score = minimax(0, false);
                board[i][j] = EMPTY;
                
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    
    return bestMove;
}

// Minimax algorithm for AI decision making
int Game::minimax(int depth, bool isMaximizing) {
    if (checkWin(PLAYER_O)) return 10 - depth;
    if (checkWin(PLAYER_X)) return depth - 10;
    if (checkDraw()) return 0;
    
    if (isMaximizing) {
        int bestScore = -1000;
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    int score = minimax(depth + 1, false);
                    board[i][j] = EMPTY;
                    bestScore = max(score, bestScore);
                }
            }
        }
        
        return bestScore;
    } else {
        int bestScore = 1000;
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    int score = minimax(depth + 1, true);
                    board[i][j] = EMPTY;
                    bestScore = min(score, bestScore);
                }
            }
        }
        
        return bestScore;
    }
}

// Find a random valid move
pair<int, int> Game::findRandomMove() const {
    vector<pair<int, int>> availableMoves;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                availableMoves.push_back({i, j});
            }
        }
    }
    
    if (availableMoves.empty()) {
        return {-1, -1};
    }
    
    int randomIndex = rand() % availableMoves.size();
    return availableMoves[randomIndex];
}

// Find a winning move for the specified player
pair<int, int> Game::findWinningMove(char player) const {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                // Test if this move would win
                char temp = board[i][j];
                const_cast<Game*>(this)->board[i][j] = player;
                bool wouldWin = checkWin(player);
                const_cast<Game*>(this)->board[i][j] = temp;
                
                if (wouldWin) {
                    return {i, j};
                }
            }
        }
    }
    
    return {-1, -1};
}

// Update the leaderboard with game results
void Game::updateLeaderboard(const string& name, bool won, bool draw) {
    if (leaderboard.find(name) != leaderboard.end()) {
        if (draw) {
            leaderboard[name].draws++;
        } else if (won) {
            leaderboard[name].wins++;
        } else {
            leaderboard[name].losses++;
        }
    }
}

// Display the leaderboard
void Game::showLeaderboard() const {
    clearScreen();
    cout << "=============================================\n";
    cout << "                  LEADERBOARD                \n";
    cout << "=============================================\n";
    
    if (leaderboard.empty()) {
        cout << "No games played yet.\n";
    } else {
        cout << left << setw(20) << "Player" 
             << setw(8) << "Wins" 
             << setw(8) << "Losses" 
             << setw(8) << "Draws" 
             << setw(10) << "Win Rate" << endl;
        cout << "---------------------------------------------\n";
        
        for (const auto& entry : leaderboard) {
            const Player& player = entry.second;
            int totalGames = player.wins + player.losses + player.draws;
            float winRate = (totalGames > 0) ? (player.wins * 100.0f / totalGames) : 0;
            
            cout << left << setw(20) << player.name 
                 << setw(8) << player.wins 
                 << setw(8) << player.losses 
                 << setw(8) << player.draws 
                 << setw(10) << fixed << setprecision(1) << winRate << "%" << endl;
        }
    }
    
    cout << "=============================================\n";
    waitForEnter();
}

// Display help and instructions
void Game::showHelp() const {
    clearScreen();
    cout << "========================================\n";
    cout << "           HOW TO PLAY TIC-TAC-TOE      \n";
    cout << "========================================\n";
    cout << "1. The game is played on a 3x3 grid.\n";
    cout << "2. Players take turns marking a square.\n";
    cout << "3. Player 1 is X, Player 2 is O.\n";
    cout << "4. The first player to get 3 of their\n";
    cout << "   marks in a row (up, down, across, or\n";
    cout << "   diagonally) is the winner.\n";
    cout << "5. When all 9 squares are full, the game\n";
    cout << "   is over. If no player has 3 marks in a\n";
    cout << "   row, the game ends in a draw.\n";
    cout << "========================================\n";
    cout << "             GAME CONTROLS              \n";
    cout << "========================================\n";
    cout << "Enter row and column numbers (1-3)\n";
    cout << "when prompted. For example:\n";
    cout << "Row: 1, Column: 1 - Top-left corner\n";
    cout << "Row: 2, Column: 2 - Center position\n";
    cout << "Row: 3, Column: 3 - Bottom-right corner\n";
    cout << "========================================\n";
    waitForEnter();
}

// Save the leaderboard to a file
void Game::saveLeaderboard() const {
    ofstream file("leaderboard.txt");
    if (file.is_open()) {
        for (const auto& entry : leaderboard) {
            const Player& player = entry.second;
            file << player.name << " " << player.wins << " " << player.losses << " " << player.draws << "\n";
        }
        file.close();
    }
}

// Load the leaderboard from a file
void Game::loadLeaderboard() {
    ifstream file("leaderboard.txt");
    if (file.is_open()) {
        string name;
        int wins, losses, draws;
        
        while (file >> wins >> losses >> draws) {
            // Read the rest of the line as the name (allows spaces in names)
            getline(file, name);
            // Remove leading space if present
            if (!name.empty() && name[0] == ' ') {
                name = name.substr(1);
            }
            leaderboard[name] = {name, wins, losses, draws};
        }
        
        file.close();
    }
}
