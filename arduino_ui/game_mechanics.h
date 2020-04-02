#ifndef _GAME_MECHANICS_H
#define _GAME_MECHANICS_H

#include "consts_types.h"
#include "move.h"

void chooseMove(selected& pieceSel, move_st& moves, move type = MOVE, 
                int8_t *capture = NULL, int8_t capp = 0);
bool mustCapture();

void showCap(int8_t *capture, int8_t capp, bool show = true);

#endif