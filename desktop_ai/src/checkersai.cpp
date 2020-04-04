#include "commlink.h"
#include "game.h"

// int main() {
//   CommLink comms; // start communication with Arduino
//   std::cout << "Preparing communication... ";
//   comms.confirm(); // confirm link with Arduino
//   std::cout << "Communication ready!" << std::endl;
//   Board board, test;
//   string s = "22220102120120111222000000000000";
//   Board *p = 
//   while (true) {
//     comms.sendBoardState(test);
//     if (comms.getBoardState(&board)) {
//       board.displayBoard();
//     }
//   }
  
//   return 0;
// }


// testing some stuff
int main() {
  Board board, test;
  string s = "22220102120120111222000000000000";
  CommLink comms;
  Board *p;
  comms.getBoardState(p);
  p->display();
  
  test.display();
  test = *p;
  test.display();
  delete(p);
  test.display();
  test = board;
  test.display();
  return 0;
}