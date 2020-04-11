// ---------------
// comms.cpp
// ---------------
// Contains all functions related to communication with the desktop
//


#include "comms.h"

extern shared_vars shared;

// reads line from serial until newline char is received
// does not include newline char in string
bool read_line(char *buff, uint32_t timeout) {

  uint32_t start = millis(), current = 0;
  int8_t len = 0; 
  while (current < timeout) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '\n' || c == '\r') {
        return true;
      } else {
        buff[len] = c;
        len++;
        buff[len] = 0; // null terminator
      }
    }
    current = millis() - start;
  }

  return false;
}

// sets up communication with desktop
// returns true if successful
bool comm::setup() {
  char buff[3];
  Serial.println("A");
  if (read_line(buff, 1000)) {
    if (buff[0] == 'A') { // desktop acknowledged
      return true;
    }
  };
  return false;
}

// receives board state from Serial
void comm::receive_board() {
  char buff[c::b_size + 2];
  if (read_line(buff, 10000)) {
    // loop over the board char array to copy it
    for (int8_t i = 0; i < c::b_size; i++) {
      // casting char to enum piece_t
      Piece comp = (Piece) (buff[i] - '0');
      // change the board if there are differences
      if (comp != board(i)) {
        draw::clear(i); // clears tile
        shared.board[i] = comp;
        draw::piece(i); // replaces with new piece
      }
    }
  }
}

// sends board state 
void comm::send_board() {
  char b[c::b_size];
  for (int8_t i = 0; i < c::b_size; i++) {
    // casting enum piece_t to char
    b[i] = (char) shared.board[i] + '0';
  }
  Serial.println(b); // send board to serial
}

// starts game with AI, sending the difficulty
// and whether the AI starts first
void comm::start_game(bool start, int difficulty) {
  char startMsg[10]; char turn;
  // start is true when AI goes first
  turn = start ? 'F' : 'S';

  // formats the string according to the protocol
  sprintf(startMsg, "S%c%d", turn, difficulty);
  
  // send the starting message to Serial
  Serial.println(startMsg);
}

// ends game
void comm::end_game() {
  Serial.println("E"); // end game flag to restart ai
}