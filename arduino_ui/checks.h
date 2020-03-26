#ifndef _CHECKS_H
#define _CHECKS_H

#include "consts_types.h"

// these functions alter the move struct/array
namespace check {
  void move(const Piece& piece, moveSt& moves);
  void capture(const Piece& piece, moveSt& moves);
  void backwards(const Piece& piece, moveSt& moves);
}

// bool checks
namespace has {
  bool moves(const moveSt& moves);
  bool captures(const moveSt& moves);
}

#endif