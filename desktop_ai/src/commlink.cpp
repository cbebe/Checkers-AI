#include "commlink.h"

CommLink::CommLink(const char *portName) {
  // create new connection
  Serial = new SerialPort(portName);
}

CommLink::~CommLink() {
  // disconnect Serial Port
  delete(Serial);
}

// reads board state sent by Arduino
Board CommLink::getBoardState() {
  Board board;
  string c = Serial->readline(0);
  for (int i = 0; i < bSize; i++) {
    board.a[i] = static_cast<piece>(c[i]);
  }
  
  return board;
}

void CommLink::sendMove(int8 pos, int8 newPos) {
  Serial->writeline("hi");
}