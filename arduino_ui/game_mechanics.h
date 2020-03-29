#ifndef _GAME_MECHANICS_H
#define _GAME_MECHANICS_H

#include "consts_types.h"
#include "move.h"

void chooseMove(selected& pieceSel, moveSt& moves, bool *capture = NULL, move type = MOVE);
bool mustCapture();
void showCap(bool *capture, bool show = true);

#endif