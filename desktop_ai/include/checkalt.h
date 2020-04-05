#ifndef _CHECKALT_H
#define _CHECKALT_H
#include <string>
#include <algorithm> // for copy
#include <list>
#include "board.h"

typedef enum move {NOT, MOVE, CAPTURE} move_t;
typedef enum dir {UP, DOWN} dir_t; // direction of the piece
typedef enum tile {ADJACENT, DIAGONAL} tile_t;

// prefer struct over std::pair for named fields
typedef struct posPair {int8 p1; int8 p2;} posP; // position pair
typedef struct movePair {move_t move; posP pos;} moveP; // move pair
// capture struct, last field is for the captured piece's positions
// the chain in American checkers is at most 9, hence the size
typedef struct capStruct {move_t move; posP pos; int8 caps[9];} capSt; 
typedef std::list<moveP> moveList; // move pair list
typedef std::list<capSt> capList; // capture struct list

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
  bool captures(capList& captures, const Board& board, bool player);
}

namespace parse {
  Board capture(Board board, capSt capture);
  Board move(Board board, moveP move);
}

std::list<Board> boardStates(const Board& board, bool player);

#endif