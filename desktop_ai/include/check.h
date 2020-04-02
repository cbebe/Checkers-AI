#ifndef _CHECK_H_
#define _CHECK_H_

#include <string>
#include <vector>
#include <algorithm> // for copy
#include <utility> // for pair
#include "board.h"

typedef std::pair<int8, int8> mp; // position pair
typedef std::pair<bool, bool> bp; // bool pair

typedef enum {UP, DOWN} dir_t; // direction of the piece
typedef enum {ADJACENT, DIAGONAL} tile_t;
// checks for enemies/empty tiles
bp boardCheck(const Board& board, int8 pos, 
              tile_t nbr, dir_t d, Piece q);


#endif