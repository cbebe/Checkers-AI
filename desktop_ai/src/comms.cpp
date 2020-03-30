#include "comms.h"

CommLink::CommLink(const char *portName) {
  // create new connection
  Serial = new SerialPort(portName);
}

CommLink::~CommLink() {
  // disconnect Serial Port
  delete(Serial);
}

Board* CommLink::getBoardState() {
  Board* ptr = NULL;

  return ptr;
}

void CommLink::sendMove(int8 pos, int8 newPos) {

}