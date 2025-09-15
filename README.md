TIC-TAC-TOE GAME
================

Description:
------------
A text-based implementation of the classic Tic-Tac-Toe game for two players.
Players take turns marking spaces in a 3x3 grid with their respective symbols (X or O).
The player who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row wins the game.

How to Play:
------------
1. The game starts with an empty 3x3 grid.
2. Player 1 is X and Player 2 is O.
3. On your turn, enter the row and column numbers (0-2) where you want to place your mark.
4. The first player to get three of their marks in a row (horizontally, vertically, or diagonally) wins.
5. If all squares are filled and no player has three in a row, the game ends in a draw.

Compilation Instructions:
-------------------------
Using Visual Studio:
1. Create a new C++ project.
2. Add the provided source files (main.cpp, game.cpp, game.h) to your project.
3. Build and run the project.

Using Command Line (if you have a C++ compiler):
1. Navigate to the project directory.
2. Compile with: g++ main.cpp game.cpp -o tictactoe
3. Run with: ./tictactoe

Files:
------
- main.cpp: Contains the main game loop and program entry point.
- game.h: Header file with constants and function declarations.
- game.cpp: Implementation of game logic functions.

Features:
---------
- Text-based user interface
- Input validation
- Win condition checking
- Draw condition checking
- Player switching

Author:
-------
Ooi Wei Chyeh (Wayden)

Date:
-----
15/9/2024
