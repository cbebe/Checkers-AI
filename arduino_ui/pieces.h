#ifndef __PIECES_H
#define __PIECES_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include "consts_types.h"

#include "touchs.h"
#include "draw.h"
#include "checks.h"


// namespace for piece-related functions
namespace nspiece {
  void choose(selected& pieceSel, bool turn, moveSt& moves);
  Piece* find(int8_t pos);
  int8_t index(int8_t pos);
  void remove(int8_t piecePos);
}

// namespace for move-related functions
namespace nsmove {
  move legal(const Piece &piece, int8_t newPos, const moveSt& moves);
  void show(int8_t pos, const moveSt& moves);
  bool canMove(int8_t piecePos, moveSt& moves, tile currentPlayer);
  void piece(int8_t oldPos, int8_t newPos);
  void chain(Piece &piece);
  void capture(Piece &piece, int8_t newPos);
}

#endif