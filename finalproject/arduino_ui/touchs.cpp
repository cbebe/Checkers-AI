// ---------------
// touchs.cpp
// ---------------
// Contains all functions related to the touch screen
//

#include "touchs.h"
using namespace touch;

TouchScreen ts = TouchScreen(xp, yp, xm, ym, 300);


// Processes touch screen input
// Returns the coordinates of the touched point
screenPos touch::process() {
	TSPoint touch = ts.getPoint();
	pinMode(yp, OUTPUT); 
	pinMode(xm, OUTPUT); 
  screenPos tp;
  // checks if screen was not touched
	if (touch.z < minpr || touch.z > maxpr) {
    // return an arbitrarily large negative number
    tp.x = untch; tp.y = untch;
    return tp;
  }
	tp.x = map(touch.y, ts_minx, ts_maxx, tft_width - 1, 0);
	tp.y = map(touch.x, ts_miny, ts_maxy, tft_height - 1, 0);
  return tp;
}

// waits for user to touch the screen
void touch::wait() {
  while (process().x == untch);
}

// hold the Arduino until screen is not touched
void touch::hold() {
  while (process().x != untch);
}