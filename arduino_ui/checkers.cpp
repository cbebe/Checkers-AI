#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>

#include "pieces.h"

#define SD_CS 10

// display init
MCUFRIEND_kbv tft;

#define BOARD_DARK 19458 // colours for game board
#define BOARD_LIGHT 57113 // please change i don't like
#define B_SQ 35 // board square side length

// struct that stores piece information
struct Piece {
  uint8_t colour;
  bool king;
  uint8_t pos; // position of the piece from 0 to 31
};

Piece gamePieces[24];

// cursor position on the screen
struct drawPos {
  uint16_t x;
  uint16_t y;
};

// determines cursor position on the screen
// given a piece's position on the board
drawPos piecePosition(uint8_t pos) {
  int8_t group = pos / 8; // position from 0 to 3
  int8_t ForS = (pos % 8) / 4; // first or second row of group
  int8_t col = pos % 4; // the column of the piece
  drawPos dp;
  dp.x = ((1 - ForS) * B_SQ) + (2 * col * B_SQ) + 117;
  dp.y = (2 * group * B_SQ) + (ForS * B_SQ) + 37;
  return dp;
}

// draw
void drawPiece(Piece piece) {
  drawPos dp = piecePosition(piece.pos);
  int colour = TFT_BLACK;
  if (piece.colour == 0 ) {
    colour = TFT_WHITE;
  }
  tft.fillCircle(dp.x, dp.y, 15, colour);

  // marks king piece
  if (piece.king) {
    tft.fillCircle(dp.x, dp.y, 4, TFT_RED);
  }
}

void gameStart(bool start) {

  // places pieces on board
  for (uint8_t i = 0; i < 12; i++) {
    // bot pieces
    gamePieces[i] = {1, false, i};
    // player pieces
    gamePieces[i + 12] = {0, false, i + 20};
    // change colour if player chose black
    if (start) {
      gamePieces[i].colour = 0;
      gamePieces[i+1].colour = 1;
    }
    drawPiece(gamePieces[i]); 
    drawPiece(gamePieces[i + 12]);
  }
  
}

// draw checkers board
void drawBoard() {
  tft.fillRect(100,20,280,280, BOARD_DARK);

  // print the light tiles
  for (int i = 0; i < 8; i += 2) {
    for (int j = 0; j < 8; j += 2) {
      tft.fillRect(100 + (i*B_SQ), 20 + (j*B_SQ), B_SQ, B_SQ, BOARD_LIGHT);
      tft.fillRect(135 + (i*B_SQ), 55 + (j*B_SQ), B_SQ, B_SQ, BOARD_LIGHT);

    }
  }
  tft.println(BOARD_LIGHT);
}


void setup() {
  init();

	uint16_t ID = tft.readID();
	tft.begin(ID);
	tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  
  Serial.begin(9600);
  Serial.flush();

  // initialize SD card
  if (!SD.begin(SD_CS)) {
    while (1) {};    // Just wait, stuff exploded.
  }

}


int main() {
  setup();
  



  while (true) {
    bool start = menuScreen();
    drawBoard();
    gameStart(start);
  }
  return 0;
}