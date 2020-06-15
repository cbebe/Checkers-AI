#include "piece.h"

// get array of pieces depending on piece's colour
void getPieces(Piece pc, Piece *array)
{
  using namespace std;
  if (pc == E)
    return; // no piece

  if (pc == B || pc == BK)
    copy(begin(blackSide), end(blackSide), array);
  else
    copy(begin(whiteSide), end(whiteSide), array);
}
