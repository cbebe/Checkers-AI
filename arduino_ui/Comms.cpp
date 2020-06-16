// ---------------
// Comms.cpp
// ---------------
// Class for communicating with the desktop
//

#include "Comms.h"

// reads line from serial until newline char is received
// does not include newline char in string
bool read_line(char *buff, uint32_t timeout)
{

  uint32_t start = millis(), current = 0;
  int8_t len = 0;
  while (current < timeout)
  {
    if (Serial.available())
    {
      char c = Serial.read();
      if (c == '\n' || c == '\r')
      {
        return true;
      }
      else
      {
        buff[len] = c;
        len++;
        buff[len] = 0; // null terminator
      }
    }
    current = millis() - start;
  }

  return false;
}

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
void Comms::receive_board(char *buffer)
{
  read_line(buffer, 10000);
}

// sends board state
void Comms::send_board(Piece *board)
{
  char b[c::b_size];
  for (int8_t i = 0; i < c::b_size; i++)
    b[i] = (char)board[i] + '0'; // casting enum piece_t to char

  Serial.println(b); // send board to serial
}

// ends game
void Comms::end_game()
{
  Serial.println("E"); // end game flag to restart ai
}