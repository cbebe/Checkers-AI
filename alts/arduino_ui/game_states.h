// ---------------
// game_states.h
// ---------------
// Interface file for game_states.cpp
//

#ifndef _GAME_STATES_H
#define _GAME_STATES_H

#include "consts_types.h"
#include "shared.h"
#include "game_mechanics.h"
#include "menu.h"
#include "Comms.h"

void game(bool start); // starts the game

void gameInit(); // initializes board

#endif