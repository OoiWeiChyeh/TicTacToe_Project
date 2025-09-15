#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;

int main() {
    srand(time(0)); // Seed for random number generation
    
    Game game;
    int choice;
    bool exitGame = false;
    
    while (!exitGame) {
        game.showMainMenu();
        cout << "Enter your choice (1-5): ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }
        
        // Clear input buffer to prevent any leftover characters
        cin.ignore(10000, '\n');
        
        switch (choice) {
            case 1:
                game.startNewGame(false); // Player vs Player
                break;
            case 2:
                game.startNewGame(true); // Player vs AI
                break;
            case 3:
                game.showLeaderboard();
                break;
            case 4:
                game.showHelp();
                break;
            case 5:
                exitGame = true;
                cout << "Thanks for playing!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }
    
    return 0;
}
