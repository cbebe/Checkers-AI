#include "commlink.h"
#include "game.h"

int main() {
  CommLink comms; // start communication with Arduino
  std::cout << "Communication ready!" << std::endl;
  comms.sendMove(1,1);
  
  return 0;
}