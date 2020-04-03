#ifndef _COMMS_H_
#define _COMMS_H_

#include "consts_types.h"
#include "move.h"

namespace comm {
  void send_board();
  void receive_board();
  void end_game();
}

#endif