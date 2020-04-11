// ---------------
// menu.h
// ---------------
// Interface file for menu.cpp
//

#ifndef _MENU_H_
#define _MENU_H_

#include "consts_types.h"
#include "comms.h"

// consts for the menu screen
namespace menu {
  using namespace c;
  const int16_t box = 15;
  // difficulty
  const screenPos diff = {off_x + b_sq, off_y + b_sq};
  const screenPos dBtn = {diff.x - (2 * b_sq)/3, diff.y};
  const screenPos difftxt = {diff.x + 20, diff.y + 20};
  // first move
  const screenPos first = {off_x + b_sq, off_y + b_sq * 4};
  const screenPos fBtn = {first.x - (2 * b_sq)/3 , first.y};
  const screenPos firsttxt = {first.x + 20, first.y + 20};
  // start button
  const screenPos sBtn = {off_x + b_sq * 3, off_y + b_width - b_sq};
  const screenPos sBtnD = {65, 20};
  
  // const strings
  const char bot[] = "BOT";
  const char player[] = "PLAYER";
  const char easy[] = "RANDOM";
  const char imp[] = "MINIMAX";
};

// lets player choose some game options
bool menuScreen();

#endif