#include "touchs.h"

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Processes touch screen input
tPoint processTouchScreen() {
	TSPoint touch = ts.getPoint();
	pinMode(YP, OUTPUT); 
	pinMode(XM, OUTPUT); 
  tPoint tp;
  // checks if screen was not touched
	if (touch.z < MINPRESSURE || touch.z > MAXPRESSURE) {
    // return an arbitrarily large negative number
    tp.x = UNTOUCHED; tp.y = UNTOUCHED;
    return tp;
  }
	tp.x = map(touch.y, TS_MINX, TS_MAXX, TFT_WIDTH - 1, 0);
	tp.y = map(touch.x, TS_MINY, TS_MAXY, TFT_HEIGHT - 1, 0);
  return tp;
}