#ifndef _CHECK_H_
#define _CHECK_H_

#include <string>
#include <vector>
#include <utility> // for pair
#include "board.h"

typedef std::pair<int8, int8> mp; // position pair
typedef std::pair<bool, bool> bp; // bool pair

namespace empty {
  bp moveU(const Board& board, int8 pos);
  bp moveD(const Board& board, int8 pos);
  bp jumpU(const Board& board, int8 pos);
  bp jumpD(const Board& board, int8 pos);
}

#endif