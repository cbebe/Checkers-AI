// ---------------
// game_mechanics.h
// ---------------
// Interface file for game_mechanics.cpp
//

#ifndef _GAME_MECHANICS_H
#define _GAME_MECHANICS_H

#include "consts_types.h"
#include "move.h"

// lets player choose a move
void choose_move(selected &pieceSel,
                 move_st &moves,
                 move type = MOVE,
                 int8_t *captureArray = NULL,
                 int8_t numberOfCapturingPieces = 0);

// implements must capture rule
// returns true if player had to capture
bool must_capture();

// show/hide which pieces can capture
void show_cap(int8_t *captureArray, int8_t numberOfCapturingPieces, bool show = true);

#endif