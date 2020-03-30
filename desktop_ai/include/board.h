#ifndef _BOARD_H_
#define _BOARD_H_

#include <list>
#include <iostream>

typedef signed char int8;
typedef enum {
  E, // empty
  W,B, // white and black
  WK,BK // white and black kings
} piece;

const int8 numpcs = 12;

struct Board {
  // board array
  piece bArray[32];
};


Board newBoard();
void displayBoard(const Board& board);
std::list<Board> possibleMoves(const Board& board, piece player);

#endif