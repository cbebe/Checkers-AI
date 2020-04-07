#include "menu.h"

extern shared_vars shared;
using namespace menu;

void printText(screenPos pos, const char* text) {
  shared.tft->setCursor(pos.x, pos.y);
  shared.tft->fillRect(pos.x, pos.y, 120, 16, TFT_WHITE);
  shared.tft->setTextColor(TFT_BLACK);
  shared.tft->print(text);
}

// bool functions to check whether a button was pressed
bool button(screenPos t, screenPos b1, screenPos b2) {
  // checks the bounds of the button
  return  t.x > b1.x - 3 && t.x < b1.x + b2.x + 3 &&
          t.y > b1.y - 3 && t.y < b1.y + b2.y + 3;
}

void processTS(bool& turn, int& difficulty) {
  turn = true; // true means bot is first
  bool diff = true; // true means easy
  bool done = false;
  while (!done) {
    screenPos t = touch::process();
    // select the difficulty
    if (button(t, dBtn, {box, box})) {
      diff = !diff;
      if (diff) {
        printText(difftxt, easy);
      } else {
        printText(difftxt, imp);
      }
      while (touch::process().x != touch::untch);
    }
    // select who moves first
    if (button(t, fBtn, {box, box})) {
      turn = !turn;
      if (turn) {
        printText(firsttxt, bot);
      } else {
        printText(firsttxt, player);
      }
      while (touch::process().x != touch::untch);
    }

    // done selecting
    if (button(t, sBtn, sBtnD)) {
      done = true;
      while (touch::process().x != touch::untch);
    }
  }
  // lmao
  difficulty = diff ? 2 : 1000;
}

// sets up menu screen
bool menuScreen() {
  // get tft screen
  MCUFRIEND_kbv tft = *shared.tft;
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(c::off_x, c::off_y, c::b_width, c::b_width, TFT_WHITE);



  tft.setTextSize(2);
  // Display the Menu

  // print all text
  printText(diff, "Difficulty:");
  printText(difftxt, easy);
  printText(first, "First Move:");
  printText(firsttxt, bot);
  printText(sBtn, "START");
  
  // draw check boxes/buttons
  tft.drawRect(dBtn.x, dBtn.y, box, box, TFT_BLACK);
  tft.drawRect(fBtn.x, fBtn.y, box, box, TFT_BLACK);
  tft.drawRect(sBtn.x - 3, sBtn.y - 3, sBtnD.x, sBtnD.y, TFT_BLACK);

  bool start; int difficulty;
  processTS(start, difficulty);
  comm::start_game(start, difficulty);
  return start;
}