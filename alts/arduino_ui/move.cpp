// ---------------
// move.cpp
// ---------------
// Contains all functions related to moving the pieces on the board
//

#include "move.h"

extern shared_vars shared;
Check check;

// captures a piece
void nsmove::capture(int8_t oldPos, int8_t newPos)
{
  int8_t os[4];
  tileOS(oldPos, os); // set tile offsets
  for (int i = 0; i < 4; i++)
  {
    // checks which direction the capturing piece jumped to
    if (newPos - oldPos == c::dg[i])
    {
      // remove captured piece from the board
      nspiece::remove(oldPos + os[i]);
      break;
    }
  }
  nsmove::piece(oldPos, newPos);
  nsmove::chain(newPos); // checks for capture chain
}

void nsmove::chain(int8_t pos)
{
  Draw draw;
  move_st moves = c::empty_moveset;
  check.checkCapture(pos, moves);
  // do nothing if there are no moves
  if (!check.hasCaptures(moves))
    return;

  // highlight possible moves
  draw.highlight(pos);
  nsmove::show(pos, moves);
  int8_t newPos = nspiece::touch();
  // waits for the player to make a legal move
  while (!nsmove::legal(pos, newPos, moves))
    newPos = nspiece::touch();

  draw.unhighlight(pos);
  // recursively calls capture piece until
  // there are no valid captures
  nsmove::capture(pos, newPos);
}

// checks if the selected move is legal
move nsmove::legal(int8_t pos, int8_t newPos, const move_st &moves)
{
  int8_t os[4];
  tileOS(pos, os); // adjust adjacent tile offsets

  for (int i = 0; i < 4; i++)
  {
    if ((moves.m[i] == CAPTURE) && newPos == (pos + c::dg[i]))
      return CAPTURE;
    if ((moves.m[i] == MOVE) && newPos == (pos + os[i]))
      return MOVE;
  }
  // piece can't move to the selected position
  return NOT;
}

// moves a piece from one position to another
void nsmove::piece(int8_t oldPos, int8_t newPos)
{
  Draw draw;
  Piece p = board(oldPos);
  // now tile is empty
  draw.clear(oldPos);
  shared.board[oldPos] = EMPTY;

  // checks for promotion if piece is not king yet
  if (!(p == PK || p == BK))
    // promotion if a piece reaches the other side of the board
    if ((p == BOT && newPos >= 28 && newPos < 32) ||
        (p == PLAYER && newPos >= 0 && newPos < 4))
      p = (p == BOT) ? BK : PK; // promote piece to king

  // piece in new position
  shared.board[newPos] = p;
  // draw piece in new position
  draw.piece(newPos);
}

// show valid moves on the screen
void nsmove::show(int8_t pos, const move_st &moves)
{
  Draw draw;
  // adjacent tile offsets vary depending on row
  int8_t os[4];
  tileOS(pos, os);

  for (int i = 0; i < 4; i++)
    if (moves.m[i] == MOVE)
      draw.mark(pos + os[i]); // piece moves
    else if (moves.m[i] == CAPTURE)
      draw.mark(pos + c::dg[i]); // piece captures
}

// shows the player where to move the piece
// returns true if a piece can move/capture
bool nsmove::can_move(int8_t pos, move_st &moves, move type)
{
  move_st temp = moves; // keep previous moveset
  moves = c::empty_moveset;
  if (type == MOVE)
    check.checkMove(pos, moves); // checks for valid moves
  else if (type == CAPTURE)
    check.checkCapture(pos, moves); // checks for valid captures
  else if (type == NOT)
  {
    // if checking for both
    check.checkMove(pos, moves);
    check.checkCapture(pos, moves);
  }
  check.checkBackwards(pos, moves);
  if (check.hasMoves(moves) || check.hasCaptures(moves))
    return true;

  moves = temp; // revert to previous moveset
  return false;
}