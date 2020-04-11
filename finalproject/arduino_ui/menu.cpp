// ---------------
// menu.cpp
// ---------------
// Contains all functions related to the menu screen
//

#include "menu.h"

extern shared_vars shared;
using namespace menu;

// prints text given the position
void printText(screenPos pos, const char* text) {
  shared.tft->setCursor(pos.x, pos.y);
  shared.tft->fillRect(pos.x, pos.y, 120, 16, TFT_WHITE);
  shared.tft->setTextColor(TFT_BLACK);
  shared.tft->print(text);
}

// bool function to check whether a button was pressed
bool button(screenPos t, screenPos b1, screenPos b2) {
  const int dz = 3;
  // checks the bounds of the button
  return  t.x > b1.x - dz && t.x < b1.x + b2.x + dz &&
          t.y > b1.y - dz && t.y < b1.y + b2.y + dz;
}

// lets player choose some options on the touch screen
void processTS(bool& turn, int& difficulty) {
  turn = true; // true means bot is first
  bool diff = true; // true means easy
  bool done = false;
  while (!done) {
    screenPos t = touch::process();
    // select the difficulty
    if (button(t, dBtn, {box, box})) {
      diff = !diff;
      if (diff) {printText(difftxt, easy);} 
      else {printText(difftxt, imp);}
      touch::hold();
    }
    // select who moves first
    if (button(t, fBtn, {box, box})) {
      turn = !turn;
      if (turn) {printText(firsttxt, bot);} 
      else {printText(firsttxt, player);}
      touch::hold();
    }

    // done selecting
    if (button(t, sBtn, sBtnD)) {
      done = true;
      touch::hold();
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
  printText(diff, "Decision making:");
  printText(difftxt, easy);
  printText(first, "First Move:");
  printText(firsttxt, bot);
  printText(sBtn, "START");
  
  // draw check boxes/buttons
  tft.drawRect(dBtn.x, dBtn.y, box, box, TFT_BLACK);
  tft.drawRect(fBtn.x, fBtn.y, box, box, TFT_BLACK);
  tft.drawRect(sBtn.x - 3, sBtn.y - 3, sBtnD.x, sBtnD.y, TFT_BLACK);

  bool start; int difficulty;
  processTS(start, difficulty); // lets player change the options
  // send options to Serial
  comm::start_game(start, difficulty);
  return start;
}