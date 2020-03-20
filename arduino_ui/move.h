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

bool pieceCanMove(int8_t piecePos);
void movePiece(int8_t oldPos, int8_t newPos);

#endif