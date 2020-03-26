#ifndef _DRAW_H
#define _DRAW_H

#include "consts_types.h"

// this namespace is for functions that 
// only concerns with drawing on the screen
namespace draw {
  screenPos position(int8_t pos);
  void piece(const Piece& piece);
  void unhighlight(const Piece& piece);
  void highlight(const Piece& piece, bool cap);
  void mark(int8_t pos);
  void clear(int8_t pos);
}

#endif