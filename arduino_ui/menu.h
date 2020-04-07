#ifndef _MENU_H_
#define _MENU_H_

#include "consts_types.h"
#include "comms.h"

// consts for the menu screen
namespace menu {
  using namespace c;
  const int16_t box = 15;
  const screenPos diff = {off_x + b_sq, off_y + b_sq};
  const screenPos dBtn = {diff.x - (2 * b_sq)/3, diff.y};
  const screenPos first = {off_x + b_sq, off_y + b_sq * 4};
  const screenPos fBtn = {first.x - (2 * b_sq)/3 , first.y};
  const screenPos sBtn = {off_x + b_sq * 3, off_y + b_width - b_sq};
  const screenPos sBtnD = {65, 20};
  const screenPos difftxt = {diff.x + 20, diff.y + 20};
  const screenPos firsttxt = {first.x + 20, first.y + 20};

  const char bot[] = "BOT";
  const char player[] = "PLAYER";
  const char easy[] = "EASY";
  const char imp[] = "IMPOSSIBLE";
};

bool menuScreen();

#endif