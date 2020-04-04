#ifndef _CHECKALT_H
#define _CHECKALT_H

#include <string>
#include <vector>
#include <algorithm> // for copy
#include "board.h"

enum move_t {NOT, MOVE, CAPTURE};
typedef enum dir {UP, DOWN} dir_t; // direction of the piece
typedef enum tile {ADJACENT, DIAGONAL} tile_t;

// prefer struct over std::pair for named fields
typedef struct posPair {int8 oldP; int8 newP;} posP; // position pair
typedef struct movePair {enum move_t move; posP pos;} moveP; // move pair
typedef struct boolPair {bool left; bool right;} boolP; // bool pair for left or right move


const int8 os1[] = {-4, -3, 4, 5};
const int8 os2[] = {-5, -4, 3, 4};
const int8 dg[] = {-9, -7, 7, 9};
const int8 numpcs = 12; // number of pieces per player

// checks for enemies/empty tiles
boolP boardCheck(const Board& board, int8 pos, 
              tile_t nbr, dir_t d, Piece q);



#endif