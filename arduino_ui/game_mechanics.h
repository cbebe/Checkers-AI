#ifndef _GAME_MECHANICS_H
#define _GAME_MECHANICS_H

#include "consts_types.h"
#include "move.h"

void chooseMove(selected& pieceSel, bool turn, moveSt& moves);
void mustCapture(bool turn);

#endif