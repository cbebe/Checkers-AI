#ifndef _MOVE_H
#define _MOVE_H

#include "consts_types.h"
#include "pieces.h"

// moves that can be made by a piece
typedef enum {NOT, MOVE, CAPTURE} move;

// struct to store moves in all 4 directions
struct moveSt {
  move UL; move UR;
  move DL; move DR;
};

moveSt findMove(Piece piece);
bool hasMoves(moveSt moves);
void showMoves(int8_t pos, moveSt& moves);

#endif