// ---------------
// comms.h
// ---------------
// Interface file for comms.cpp
//

#ifndef _COMMS_H_
#define _COMMS_H_

#include "move.h"

class Comms
{
public:
  // sets up communication with the desktop
  bool setup();
  // starts the game with the AI
  void start_game(bool start, int difficulty);
  // receive board from Serial
  void receive_board();
  // send board to Serial
  void send_board();
  // ends the game with the AI
  void end_game();

private:
  bool readline(char *buff, uint32_t timeout);
};

#endif