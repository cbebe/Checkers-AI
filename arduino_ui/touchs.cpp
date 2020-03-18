#include "touchs.h"

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Processes touch screen input
tPoint processTouchScreen() {
	TSPoint touch = ts.getPoint();
	pinMode(YP, OUTPUT); 
	pinMode(XM, OUTPUT); 
	if (touch.z < MINPRESSURE || touch.z > MAXPRESSURE) {return;}
  tPoint tp;
	tp.x = map(touch.y, TS_MINX, TS_MAXX, TFT_WIDTH - 1, 0);
	tp.y = map(touch.x, TS_MINY, TS_MAXY, TFT_HEIGHT - 1, 0);
  return tp;
}