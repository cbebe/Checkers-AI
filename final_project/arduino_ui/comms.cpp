// ---------------
// Comms.cpp
// ---------------
// Class for communicating with the desktop
//

#include "Comms.h"

extern shared_vars shared;

// sets up communication with desktop
// returns true if successful
bool Comms::setup()
{
  char buff[3];
  Serial.println("A");
  if (read_line(buff, 1000))
    if (buff[0] == 'A')
      return true; // desktop acknowledged
  return false;
}

// starts game with AI, sending the difficulty
// and whether the AI starts first
void Comms::start_game(bool start, int difficulty)
{
  char startMsg[10];
  char turn;
  // start is true when AI goes first
  turn = start ? 'F' : 'S';

  // formats the string according to the protocol
  sprintf(startMsg, "S%c%d", turn, difficulty);

  // send the starting message to Serial
  Serial.println(startMsg);
}

// receives board state from Serial
void Comms::receive_board()
{
  char buff[c::b_size + 2];
  if (read_line(buff, 10000))
  {
    // loop over the board char array to copy it
    for (int8_t i = 0; i < c::b_size; i++)
    {
      // casting char to enum piece_t
      Piece comp = (Piece)(buff[i] - '0');
      // change the board if there are differences
      if (comp != board(i))
      {
        draw::clear(i); // clears tile
        shared.board[i] = comp;
        draw::piece(i); // replaces with new piece
      }
    }
  }
}

// sends board state
void Comms::send_board()
{
  char b[c::b_size];
  for (int8_t i = 0; i < c::b_size; i++)
    b[i] = (char)shared.board[i] + '0'; // casting enum piece_t to char

  Serial.println(b); // send board to serial
}

// ends game
void Comms::end_game()
{
  Serial.println("E"); // end game flag to restart ai
}