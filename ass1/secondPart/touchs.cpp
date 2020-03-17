#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <SPI.h>
#include <SD.h>

#include "coordinates.h"
#include "touchs.h"

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// displays nearby restaurants as dots on the screen
void drawDots() {
  restaurant currentRest; int restX, restY;
  int patchBoundX = currentPatchX + MAP_WIDTH - CIRC_RAD;
  int patchBoundY = currentPatchY + MAP_HEIGHT - CIRC_RAD;
  for (int i = 0; i < NUM_RESTAURANTS; i++) {
    getRestaurantFast(i, &currentRest);
    // only draws the dot if it passes the rating threshold
    if (max((currentRest.rating+1)/2, 1) >= ratingSel) {
      // converts from longitude and latitude to pixels relative to map size
      int restX = map(currentRest.lon, LON_WEST, LON_EAST, 0, YEG_SIZE);
      int restY = map(currentRest.lat, LAT_NORTH, LAT_SOUTH, 0, YEG_SIZE);
      // only draws the dots if it is within the screen patch
      if ((restX >= currentPatchX + CIRC_RAD && restX <= patchBoundX) && 
          (restY >= currentPatchY + CIRC_RAD && restY <= patchBoundY)) {
        tft.fillCircle(restX - currentPatchX, restY - currentPatchY, CIRC_RAD, TFT_BLUE);
        tft.drawCircle(restX - currentPatchX, restY - currentPatchY, CIRC_RAD, TFT_WHITE);
      }
    }
  }
}

// function to print strings vertically
void writeVertical(char text[], int indent, int n) {
  int x = MAP_WIDTH + 25;
  int y = MAP_HEIGHT/2 + indent;
  tft.fillRect(x, y - 16, 10, 16*(n+1), TFT_WHITE); // clears previous text
  for (int i = 0; i < n; i++) {
    tft.setCursor(x, y + (15 * i));
    tft.print(text[i]);
  }
}

// writes label on the sort button
void writeLabel() {
  switch (sortSetting) {
  case quick:
    writeVertical("QSORT", 46, 5);
    break;
  case insert:
    writeVertical("ISORT", 46, 5);
    break;
  case both:
    writeVertical("BOTH", 56, 4);
  default:
    break;
  }
  }

// changes sort setting
void changeSort() {
  switch (sortSetting) {
  case quick:
    sortSetting = insert;
    break;
  case insert:
    sortSetting = both;
    break;
  case both:
    sortSetting = quick;
  default:
    break;
  }
  writeLabel();
}

// changes the number on the rating button
void changeNum(int num) {
  tft.fillRect(MAP_WIDTH + 25, MAP_HEIGHT/4, 10,16, TFT_WHITE);
  tft.setCursor(MAP_WIDTH + 25, MAP_HEIGHT/4);
  tft.print(num);
}

// changes rating threshold for restaurants
void setRating() {
  ratingSel++;
  if (ratingSel > 5) {
    ratingSel = 1; // wraps back to 1 from 5
  }
  changeNum(ratingSel);
}

void btnSetup() {
  // draws the buttons on the screen next to the map
  tft.fillRect(MAP_WIDTH + 1, 0, BTN_WIDTH, BTN_HEIGHT, TFT_WHITE);
  tft.drawRect(MAP_WIDTH + 1, 0, BTN_WIDTH, BTN_HEIGHT, TFT_RED);
  tft.fillRect(MAP_WIDTH + 1, MAP_HEIGHT/2 + 4, BTN_WIDTH, BTN_HEIGHT, TFT_WHITE);
  tft.drawRect(MAP_WIDTH + 1, MAP_HEIGHT/2 + 4, BTN_WIDTH, BTN_HEIGHT, TFT_GREEN);

  // labels the buttons (1 and Qsort by default)
  ratingSel = 1;
  sortSetting = quick;
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);
  changeNum(ratingSel);
  writeLabel();
}

// Processes touch screen input
void processTouchScreen() {
	TSPoint touch = ts.getPoint();
	pinMode(YP, OUTPUT); 
	pinMode(XM, OUTPUT); 
	if (touch.z < MINPRESSURE || touch.z > MAXPRESSURE) {return;}

	int16_t screen_x = map(touch.y, TS_MINX, TS_MAXX, TFT_WIDTH - 1, 0);
	int16_t screen_y = map(touch.x, TS_MINY, TS_MAXY, TFT_HEIGHT - 1, 0);
  // draw dots if map was touched
  if (screen_x > 0 && screen_x < MAP_WIDTH) {drawDots();}
  if (screen_x < TFT_WIDTH && screen_x > MAP_WIDTH) {
    if (screen_y < TFT_HEIGHT/2) {setRating();}
    else {changeSort();}
    delay(250);
  }
}