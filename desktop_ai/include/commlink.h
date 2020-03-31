#ifndef _COMMLINK_H_
#define _COMMLINK_H_

#include "board.h"
#include "serialport.h"


class CommLink {
public:
  CommLink(const char* portName = "/dev/ttyACM0");
  ~CommLink();
  // get board state from Serial
  Board getBoardState();
  // send move to Serial
  void sendMove(int8 pos, int8 newPos);
  
private:
  SerialPort *Serial;
};


#endif