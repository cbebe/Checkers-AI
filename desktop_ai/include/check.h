#ifndef _CHECK_H_
#define _CHECK_H_

#include <string>
#include <vector>
#include <algorithm> // for copy
#include <utility> // for pair
#include "board.h"

enum move_t {NOT, MOVE, CAPTURE};

typedef std::pair<int8, int8> mp; // position pair
typedef std::pair<enum move_t, mp> move; // move type and position pair pair

typedef std::pair<bool, bool> bp; // bool pair

typedef enum {UP, DOWN} dir_t; // direction of the piece
typedef enum {ADJACENT, DIAGONAL} tile_t;

const int8 os1[] = {-4, -3, 4, 5};
const int8 os2[] = {-5, -4, 3, 4};
const int8 dg[] = {-9, -7, 7, 9};
const int8 numpcs = 12; // number of pieces per player

// checks for enemies/empty tiles
bp boardCheck(const Board& board, int8 pos, 
              tile_t nbr, dir_t d, Piece q);

int findLeftOS(int pos, int leftEdge, int bottomEdge);
int findRightOS(int pos, int rightEdge, int bottomEdge);

#endif