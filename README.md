# Arduino Checkers with AI

An Arduino Checkers game with an opponent Minimax AI controlled by a Linux desktop

## How it Works

1. The Arduino displays an interactive game board in which the player can use make moves.
2. When a move is made, the Arduino sends the board to the desktop through the Serial port.
3. The desktop evaluates the best move to make using the Minimax algorithm and the provided heuristics.
4. The desktop sends the new board to the Arduino using the Serial port.
5. The Arduino displays the changes on the screen and prompts the user for a move.
6. Repeat until the game ends with one side winning or a draw.

## Challenges

- Writing the game engine from scratch using previous checkers knowledge
- Creating the board heuristics that would lead to a challenging opponent AI (failed :sad)

## Future Plans (?)

- Transform the Arduino code from using namespaces to classes
- Create a non-Linux setup so the game can be played on Windows as well
- Consider other options for the AI (better heuristics, machine learning?)

## Authors

Created by [Charles Ancheta](https://github.com/charlesancheta) and [Poulomi Ganguly](https://github.com/poulomi-g) as the Final Project for CMPUT 275
