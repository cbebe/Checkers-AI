// ---------------
// draw.h
// ---------------
// Interface file for draw.cpp
//


#ifndef _DRAW_H
#define _DRAW_H

#include "consts_types.h"

// this namespace is for functions that 
// only concerns with drawing on the screen
namespace draw {
  // gives the screen position of the centre of the chosen tile
  screenPos position(int8_t pos);
  // draws the piece on the board
  void piece(int8_t pos);
  // highlights the piece for moving
  void highlight(int8_t pos, bool cap = false);
  // unhighlights the piece and its moves
  void unhighlight(int8_t pos);
  // places a mark on the board if a piece can move there
  void mark(int8_t pos);
  // clear the tile of marks/pieces
  void clear(int8_t pos);
}

#endif