#ifndef _COMMLINK_H_
#define _COMMLINK_H_

#include "board.h"
#include "serialport.h"

// wrap serial communication in a class
// to prevent unncessary access
class CommLink
{
public:
  CommLink(const char *portName = "/dev/ttyACM0");
  ~CommLink();

  //confirms connection with Serial
  void confirm();

  // checks whether the AI starts the game or not
  bool startGame(int &difficulty);

  // get board state from Serial
  // returns false if game ended, true otherwise
  bool getBoardState(Board &board);

  // send board state to Serial
  void sendBoardState(const Board &board);

private:
  SerialPort *Serial;
};

#endif