#ifndef _PIECE_H_
#define _PIECE_H_

// piece definitions

typedef signed char int8;
const int8 bSize = 32; // board size
typedef enum pc {
  E, // empty
  W,B, // white and black
  WK,BK, // white and black kings
  OUT // out of bounds
} Piece;

#endif