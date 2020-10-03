#ifndef _CHECKALT_H
#define _CHECKALT_H
#include <string>
#include "board.h"  // for board class
#include "offset.h" // for board offsets

// enum types
typedef enum move
{
  NOT,
  MOVE,
  CAPTURE
} move_t; // move type

typedef enum dir
{
  UP,
  DOWN
} dir_t; // direction of the piece

typedef enum tile
{
  ADJACENT,
  DIAGONAL
} tile_t; // neighbour type

// prefer struct over std::pair for named fields
typedef struct posPair
{
  int8 p1;
  int8 p2;
} posP;                             // position pair
typedef std::vector<posP> moveList; // move pair list
typedef std::vector<Board> bList;   // board list

const int8 numpcs = 12; // number of pieces per player

// use to get list of moves by a single piece
namespace get
{
  moveList captures(const Board &board, int8 pos);
  moveList moves(const Board &board, int8 pos);
} // namespace get

// use to modify the board states list
namespace check
{
  bool moves(moveList &moves, const Board &board, bool player);
  void captures(bList &boardList, const Board &board, bool player);
} // namespace check

// gets all the possible moves by the player/bot
bList boardStates(const Board &board, bool player);

#endif