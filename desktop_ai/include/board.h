#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <string>
#include <array>
#include "piece.h"


// string containing starting positions for pieces
const std::string newBoard = "22222222222200000000111111111111";

class Board {
public:
  // creates new board with given board state
  Board(const std::string& boardState = newBoard);

  bool move(int8 oldPos, int8 newPos); // moves piece
  void remove(int8 pos); // removes a piece from the board
  Piece get(int8 pos) const; // gets piece in position
  void set(int8 pos, Piece pc); // sets the position into a piece

  void display() const; // display board in stdout
  std::string stateString() const; // returns current board state string

  int eval() const; // returns static evaluation of the board
  void calculate(int setValue = 0); // for setting or calculating board value

private:
  std::array<Piece, bSize> boardArray;
  int boardValue;

};

#endif