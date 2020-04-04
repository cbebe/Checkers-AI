#ifndef _BOARD_H_
#define _BOARD_H_

#include <list>
#include <iostream>
#include <string>

typedef signed char int8;
typedef enum pc {
  E, // empty
  W,B, // white and black
  WK,BK, // white and black kings
  OUT // out of bounds
} Piece;


const int8 bSize = 32; // board size

// string containing starting positions for pieces
const std::string newBoard = "22222222222200000000111111111111";

class Board {
public:
  Board(const std::string& boardState = newBoard);
  ~Board();

  bool move(int8 oldPos, int8 newPos); // moves piece
  void remove(int8 pos); // removes a piece from the board
  Piece get(int8 pos) const; // returns piece in position

  void displayBoard() const; // display board in stdout
  std::string stateString() const; // returns current board state string

private:
  void set(int8 pos, Piece pc);
  Piece *boardArray;
};

#endif