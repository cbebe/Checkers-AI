#ifndef _CHECK_H_
#define _CHECK_H_

#include <string>
#include <vector>
#include <algorithm> // for copy
#include <utility> // for pair
#include "board.h"
            
Piece pieceCheck(const Board& board, int8 pos);

int8 findLeftOS(int pos, int leftEdge, int bottomEdge);
int8 findRightOS(int pos, int rightEdge, int bottomEdge);

#endif