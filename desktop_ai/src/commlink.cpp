#include "commlink.h"

CommLink::CommLink(const char *portName) {
  // create new connection
  Serial = new SerialPort(portName);
}

CommLink::~CommLink() {
  // disconnect Serial Port
  delete(Serial);
}

// confirm communication with Arduino
// waits for acknowledge flag A
void CommLink::confirm() {
  while(Serial->readline(0)[0] != 'A');
  Serial->writeline("A\n"); // send acknowledge back
}

// reads board state sent by Arduino
// returns false if the game ended
bool CommLink::getBoardState(Board* board) {
  string state = Serial->readline(0);
  // E for endgame flag
  if (state[0] == 'E') {return false;}

  //
  board = new Board(state);
  return true;
}

// send board state to Arduino
void CommLink::sendBoardState(const Board& board) {
  string bstate = board.stateString();

  // send line to serial
  Serial->writeline(bstate + '\n');
}