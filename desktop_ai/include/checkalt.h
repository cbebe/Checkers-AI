#ifndef _CHECKALT_H
#define _CHECKALT_H
#include <string>
#include <algorithm> // for copy
#include <vector>
#include "board.h"


typedef enum move {NOT, MOVE, CAPTURE} move_t;
typedef enum dir {UP, DOWN} dir_t; // direction of the piece
typedef enum tile {ADJACENT, DIAGONAL} tile_t;

// prefer struct over std::pair for named fields
typedef struct posPair {int8 p1; int8 p2;} posP; // position pair 
typedef std::vector<posP> moveList; // move pair list
typedef std::vector<Board> bList; // board list

const int8 os1[] = {-4, -3, 4, 5};
const int8 os2[] = {-5, -4, 3, 4};
const int8 dg[] = {-9, -7, 7, 9};
const int8 numpcs = 12; // number of pieces per player

namespace get {
  moveList captures(const Board& board, int8 pos);
  moveList moves(const Board& board, int8 pos);
}

namespace check {
  bool moves(moveList& moves, const Board& board, bool player);
  void captures(bList& boardList, const Board& board, bool player);
}

bList boardStates(const Board& board, bool player);

#endif