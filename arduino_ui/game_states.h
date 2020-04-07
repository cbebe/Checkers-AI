#ifndef _GAME_STATES_H
#define _GAME_STATES_H

#include "consts_types.h"
#include "game_mechanics.h"
#include "comms.h"

// consts for the menu screen
namespace menu {
  using namespace c;
  const screenPos diff = {off_x + b_sq, off_y + b_sq};
  const screenPos first = {off_x + b_sq, off_y + b_sq * 4};
  const screenPos sBtn = {off_x + b_sq * 3, off_y + b_width - b_sq};
  const screenPos sBtnD = {65, 20};
}

void game(bool start);
void gameInit();
bool menuScreen();

#endif