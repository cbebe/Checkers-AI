#include "comms.h"

extern shared_vars shared;

// sends board state 
void comm::send_state() {
  char b[c::b_size];
  for (int8_t i = 0; i < c::b_size; i++) {
    // casting enum to char
    b[i] = (char) shared.board[i] + '0';
  }
  Serial.println(b); // send board to serial
}

// reads line from serial until newline char is received
// does not include newline in string
bool read_line(char *buff, uint32_t timeout) {

  uint32_t deadline = millis() + timeout;
  int8_t len = 0; char c;
  while (millis() < deadline) {
    if (Serial.available()) {
      c = Serial.read();
      if (c == '\n' || c == '\r') {
        return true;
      } else {
        buff[len] = c;
        len++;
        buff[len] = 0; // null terminator
      }
    }
  }
  // timed out or reading failed
  return false;
}

void comm::get_move() {
  char buff[10];
  if (read_line(buff, c::t20s)) {
    int to, from; char move;
    sscanf(buff, "%c %d %d", &move, &from, &to);
    if (move == 'C') {
      nsmove::capture(from, to);
    } else if (move == ';M') {
      nsmove::piece(from, to);
    }
  }
}