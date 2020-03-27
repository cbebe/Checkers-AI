#ifndef _GAME_MECHANICS_H
#define _GAME_MECHANICS_H

#include "consts_types.h"
#include "move.h"

void chooseMove(selected& pieceSel, bool turn, moveSt& moves, bool *capture = NULL, move type = MOVE);
bool mustCapture(bool turn);
void showCap(bool *capture, bool turn, bool show = true);

#endif