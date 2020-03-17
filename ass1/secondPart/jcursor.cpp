#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include <SD.h>

#include "lcd_image.h"
#include "coordinates.h"
#include "jcursor.h"

lcd_image_t yegImage = { "yeg-big.lcd", YEG_SIZE, YEG_SIZE };

// redraws the cursor on the given cursor position
void redrawCursor() {
  tft.fillRect(cursorX - CUR_RAD, cursorY - CUR_RAD,
               CURSOR_SIZE, CURSOR_SIZE, TFT_RED);
}

// draws an entire map patch on the screen
void drawMap() {
  lcd_image_draw(&yegImage, &tft, currentPatchX, currentPatchY,
                 0, 0, MAP_WIDTH, MAP_HEIGHT);
}
// initializes screen to display Edmonton map
void mapInit() {
  tft.fillScreen(TFT_BLACK);
  drawMap();
  redrawCursor();
}

// redraws map background on previous cursor position to remove black trail
void redrawMapBg(uint16_t tempX, uint16_t tempY) {
  int screenPatchX = tempX - CUR_RAD;
  // prevents cursor from moving to black column
  screenPatchX = constrain(screenPatchX, 0, MAP_WIDTH - CURSOR_SIZE);
  int screenPatchY = tempY - CUR_RAD;
  lcd_image_draw(&yegImage, &tft, currentPatchX + screenPatchX, 
                  currentPatchY + screenPatchY, screenPatchX, 
                  screenPatchY, CURSOR_SIZE, CURSOR_SIZE);
}
// processes analog data and changes the increment 
// depending on the read analog value (from +-1px to +-4px)
void processAnalog(int aVal, char dir) {
  int increment = 0;
  if (aVal > POS_BUFFER) {
    increment += 1 + (aVal - POS_BUFFER)/SPEED_DIV;
  } else if (aVal < NEG_BUFFER) {
    increment += -1 +(aVal - NEG_BUFFER)/SPEED_DIV;
  }
  // accounts for the inverted X increment
  if (dir == 'X') {
  	cursorX -= increment;
  } else {
  	cursorY += increment;	
  }
}

// moves map patch depending on which edge of the screen the cursor was touching
void moveMapPatch(bool xl, bool xr, bool yt, bool yb) {
  if (!xl) {currentPatchX -= MAP_WIDTH;}
  if (!xr) {currentPatchX += MAP_WIDTH;}
  if (!yt) {currentPatchY -= MAP_HEIGHT;}
  if (!yb) {currentPatchY += MAP_HEIGHT;}
  // does not load the patch beyond map size
  currentPatchX = constrain(currentPatchX, 0, YEG_SIZE - MAP_WIDTH);
  currentPatchY = constrain(currentPatchY, 0, YEG_SIZE - MAP_HEIGHT);
  cursorX = CENTRE_X; cursorY = CENTRE_Y; // places cursor in the centre
  drawMap(); redrawCursor();
}

// clamps the cursor to the map bounds
void clampMapBounds() {
  if (currentPatchX == 0 && cursorX < CUR_RAD) {cursorX = CUR_RAD;}   
  if (currentPatchX == MAP_MAXX && cursorX > BND_WIDTH) {cursorX = BND_WIDTH;}
  if (currentPatchY == 0 && cursorY < CUR_RAD) {cursorY = CUR_RAD;}
  if (currentPatchY == MAP_MAXY && cursorY > BND_HEIGHT) {cursorY = BND_HEIGHT;} 
} 

void screenBoundCheck() {
  // checks if the cursor is still in bounds of the screen
  bool xInLeftBnd = cursorX >= CUR_RAD; 
  bool xInRightBnd = cursorX <= BND_WIDTH;
  bool yInTopBnd = cursorY >= CUR_RAD; 
  bool yInBotBnd = cursorY <= BND_HEIGHT;
  if (!xInLeftBnd || !xInRightBnd || !yInTopBnd || !yInBotBnd) {
    moveMapPatch(xInLeftBnd, xInRightBnd, yInTopBnd, yInBotBnd);
  }
}

// setup for tft and map patch
void setup() {
  init();
  Serial.begin(9600);
  // SD card initialization for raw reads
  Serial.print("Initializing SPI communication for raw reads...");
  if (!card.init(SPI_HALF_SPEED, SD_CS)) {
    Serial.println("failed! Is the card inserted properly?");
    while (true) {}
  }
  else {
    Serial.println("OK!");
  }
  uint16_t ID = tft.readID();    // read ID from display
  if (ID == 0xD3D3) ID = 0x9481; // write-only shield  
  tft.begin(ID);                 // LCD gets ready to work
	if (!SD.begin(SD_CS)) {
		while (true) {}
	}
	tft.setRotation(1); 
  // sets the current map patch to the middle of the Edmonton map
  currentPatchX = ((YEG_SIZE / MAP_WIDTH)/2) * MAP_WIDTH;
	currentPatchY = ((YEG_SIZE / MAP_HEIGHT)/2) * MAP_HEIGHT;
  // initial cursor position is the middle of the screen
  cursorX = MAP_WIDTH/2;
  cursorY = MAP_HEIGHT/2;

  mapInit();
  pinMode(JOY_SEL, INPUT);
  digitalWrite(JOY_SEL, HIGH);
}

void processJoystick() {
  // temp variables to draw map on later
  int tempX = cursorX, tempY = cursorY;
  processAnalog(analogRead(JOY_HORIZ), 'X'); 
  processAnalog(analogRead(JOY_VERT), 'Y');
  clampMapBounds();
  screenBoundCheck();
  // will only redraw map when the cursor moves to prevent the cursor from flickering
  if (tempX != cursorX || tempY != cursorY) {
    redrawMapBg(tempX, tempY);
    redrawCursor();
  }
}
