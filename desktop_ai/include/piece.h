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

// piece array for colour's allies and enemies
// 0-1 ally, 2-3 enemy
const Piece blackSide[] = {B, BK, W, WK};
const Piece whiteSide[] = {W, WK, B, BK};

#endif