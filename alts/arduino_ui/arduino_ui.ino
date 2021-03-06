#include "consts_types.h"
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

#include "shared.h"
#include "game_states.h"

// shared variables
shared_vars shared;
// display and touch screen init
MCUFRIEND_kbv tft;
Touch touch;

// for good ol' printf debugging
void db(const char *msg)
{
  shared.tft->fillRect(0, TFT_HEIGHT - 30, TFT_WIDTH, 30, TFT_BLACK);
  shared.tft->setCursor(0, TFT_HEIGHT - 25);
  shared.tft->setTextSize(2);
  shared.tft->setTextColor(TFT_WHITE);
  shared.tft->print(msg);
}

// returns the tile value of a board position
// use only for comparing, not for value assignment
Piece board(int8_t pos)
{
  // out of bounds
  if (pos < 0 || pos > 31)
    return OUT;

  return shared.board[pos];
}

// adjusts tile offsets depending on row
void tileOS(int8_t p, int8_t *os)
{
  // tile offsets {0:UL, 1:UR, 2:DL, 3:DR}
  os[0] = -4;
  os[2] = 4;
  os[1] = -3;
  os[3] = 5;
  // second row has different offsets
  if (((p % 8) / 4))
    for (int8_t i = 0; i < 4; i++)
      os[i] -= 1;
}

void setup()
{
  // initialize display
  shared.tft = &tft;
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);

  Serial.begin(9600);
  Serial.flush();

  db("Setting up Serial Port with desktop...");
  Comms comm;
  while (!comm.setup())
    ;
  db("Done!");
  delay(500);
}

void loop()
{
  // menu screen to let player choose some options
  bool start = menuScreen();
  gameInit();  // initialize board
  game(start); // start game
}
