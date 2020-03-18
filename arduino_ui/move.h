#ifndef _MOVE_H
#define _MOVE_H

#include "consts_types.h"
#include "pieces.h"

typedef enum {NOT, MOVE, CAPTURE} move;

// struct to store moves in all 4 directions
struct moveSt {
  move UL;
  move UR;
  move DL;
  move DR;
};

moveSt findMove(Piece piece);
bool hasMoves(moveSt moves);
void showMoves(Piece piece, moveSt moves);

#endif