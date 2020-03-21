#ifndef _MOVE_H
#define _MOVE_H

#include "consts_types.h"
#include "pieces.h"

bool pieceCanMove(int8_t piecePos, moveSt& moves, tile currentPlayer);
void movePiece(int8_t oldPos, int8_t newPos);
void showMoves(int8_t pos, const moveSt& moves);

#endif