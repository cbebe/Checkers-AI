#ifndef _COMMLINK_H_
#define _COMMLINK_H_

#include "board.h"
#include "serialport.h"


class CommLink {
public:
  CommLink(const char* portName = "/dev/ttyACM0");
  ~CommLink();
  
  // get board state from Serial
  // returns false if game ended, true otherwise
  bool getBoardState(Board& board);

  // send board state to Serial
  void sendBoardState(const Board& board);
  
private:
  SerialPort *Serial;
};


#endif