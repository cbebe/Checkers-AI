#include "eval.h"

// returns a piece value
double pieceValue(Piece pc) {
  double pieceVal = 0; // assume empty at first
  if (pc != E) {
    if (pc == BK) {pieceVal = kingVal;}    
    else if (pc == B) {pieceVal = pawnVal;}    
    else if (pc == WK) {pieceVal = -kingVal;}    
    else if (pc == W) {pieceVal = -pawnVal;}
  }
  return pieceVal;
}

// checks for position value
double positionValue(Piece pc, int8 pos) {
  // if the conditions are not met,
  // the piece does not contribute to the decision making
  int posVal = 0; 
  if (pc != E) {
    // check if the pieces are defending their back row
    if (pc == W || pc == WK) {
      if (pos > 27) {
        return backrow;
      }
    } else {
      if (pos < 4) {
        return backrow;
      }
    }
    // if piece is in the middle row
    if (pos > 11 && pos < 20) {
      posVal = midrow;
      // if the piece is in the middle box
      if (!(((pos - 13) % 4) && ((pos - 14) % 4))) {
        posVal = midbox;
      }
    }
  }
  return posVal;
}

// check for piece vulnerability
double defCheck(const Board& board, int8 index) {
  Piece pc = board.get(index);
  // gets piece's ally and enemy colour
  Piece comps[4]; getPieces(pc, comps);

  int8 adj[4]; rowOS(index, adj); // get position of indices
  // adjacent, parallel, and diagonal piece arrays
  Piece n[4], p[4], d[4];

  for (int i = 0; i < 4; i++) {
    // get adjacent, parallel, and diagonal piece values
    n[i] = board.get(index + adj[i]);
    p[i] = board.get(index + prl[i]);
    d[i] = board.get(index + dg[i]);
  }
  for (int i = 0; i < 4; i++) {
    bool emptyBehind = (n[(i + 2) % 4] == E);
    double defVal = emptyBehind ? vulnerable : defended;

    // check if there is an enemy next to the piece
    if (n[i] == comps[2] || n[i] == comps[3]) {
      return defVal;
    }
    // check for possible chain captures

    bool prlAlly = p[i] == comps[0] || p[i] == comps[1];
    bool dgAlly = d[i] == comps[0] || d[i] == comps[1];
    
    // if there is a parallel or diagonal ally piece
    if (prlAlly && dgAlly) {
      // the piece is vulnerable to chain capture
      if (n[i] == E) {return defVal;}
    }
    // also check the other side for parallel ally
    if (prlAlly) {
      if (n[(i + 1) % 4] == E) {
        if (n[(i + 3) % 4] == E) {
          return vulnerable;
        } else {
          return defended;
        }
      }
    }
  }
  // not affected
  return 0;
}

// checks for endgame conditions
// necessary so that the AI would 
// avoid losing as much as possible
double gameOver(const Board& board) {
  int black = 0, white = 0;
  // counts the pieces on the board
  for (int i = 0; i < bSize; i++) {
    Piece pc = board.get(i);
    if (pc == B || pc == BK) {black++;}
    else if (pc == W || pc == WK) {white++;}
    if (black && white) {
      return 0; // no one has lost yet
    }
  }
  if (!black) {
    // no more black pieces
    return -10000;
  } 
  // no more white pieces
  return 10000;
}

// performs a static evaluation on the board
// according to the given heuristics
double staticEval(const Board& board) {
  // check for endgame conditions first
  double eval = gameOver(board);

  // get board value if no one has lost yet
  if (!eval) {
    for (int i = 0; i < bSize; i++) {
      Piece pc = board.get(i);
      // get value of position
      double posVal = positionValue(pc, i);
      // checks if the piece is defended
      posVal += defCheck(board, i);
      eval += pieceValue(pc) * posVal;
    }
  }
  
  return eval;
}