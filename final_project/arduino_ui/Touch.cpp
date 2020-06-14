// ---------------
// touchs.cpp
// ---------------
// Contains all functions related to the touch screen
//

#include "Touch.h"

TouchScreen ts = TouchScreen(xp, yp, xm, ym, 300);

// touch screen pins, obtained from the documentation
const uint8_t yp = A3;
const uint8_t xm = A2;
const uint8_t ym = 9;
const uint8_t xp = 8;
// calibration data for the touch screen, obtained from documentation
// the minimum/maximum possible readings from the touch point
const uint16_t ts_minx = 100;
const uint16_t ts_miny = 120;
const uint16_t ts_maxx = 940;
const uint16_t ts_maxy = 920;

// thresholds to determine if there was a touch
const uint16_t min_pressure = 10;
const uint16_t max_pressure = 1000;

// Processes touch screen input
// Returns the coordinates of the touched point
screenPos Touch::process()
{
  TSPoint touch = ts.getPoint();
  pinMode(yp, OUTPUT);
  pinMode(xm, OUTPUT);
  screenPos tp;
  // checks if screen was not touched
  if (touch.z < min_pressure || touch.z > max_pressure)
  {
    // return an arbitrarily large negative number
    tp.x = untouched;
    tp.y = untouched;
    return tp;
  }
  tp.x = map(touch.y, ts_minx, ts_maxx, tft_width - 1, 0);
  tp.y = map(touch.x, ts_miny, ts_maxy, tft_height - 1, 0);
  return tp;
}

// waits for user to touch the screen
void Touch::wait()
{
  while (process().x == untouched)
    ;
}

// hold the Arduino until screen is not touched
void Touch::hold()
{
  while (process().x != untouched)
    ;
}