#include "checkalt.h"

/* 
boolP boardCheck:
General-purpose function for any checks
that need to be made on the board

Checks if tiles are empty/have enemies
-- neighbour is either adjacent or diagonal, 
for checking moves or jumps.
-- query is either empty or the enemy piece.
-- direction is either up or down, 
depending on which piece the side is on.
*/
posP boardCheck(const Board& board, int8 pos, 
              tile_t neighbour, dir_t direction, Piece query) {
  int8 offset[4];
  // check which neighbour we're looking for
  if (neighbour == ADJACENT) {
    // adjacent offsets depend on piece's position
    rowOS(pos, offset); 
  } else {
    // diagonal offsets are constant in every direction
    diagOS(offset);
  }
  Piece queryK = E; // assume query is E
  if (query != E) {
    // assigning the query king piece
    queryK = (query == B) ? BK : WK;  
  }

  bool leftEdge = !((pos - 4) % 8); // piece is on the left
  bool rightEdge = !((pos - 3) % 8); // piece is on the right

  // checks if the pieces are on the top or bottom edge
  if ((direction == UP && pos < 4) ||
      (direction == DOWN && pos > 27)) {
    return {-1, -1}; // can't move
  }
  // else, check
  int8 i = (direction == UP) ? 0 : 2; // starting index for offset
  int8 leftOS, rightOS;
  
  // checks for second outer two columns; can't capture there
  if (neighbour == DIAGONAL) {
    if (!(pos % 8)) {
      leftEdge = true; // piece is on outer left
    }
    if (!((pos-7) % 8)) {
      rightEdge = true; // piece is on the outer right
    }
  }
  if (leftEdge) {
    leftOS = -1; // piece can't move
  } else {
    leftOS = pos + offset[i];
    // get the pieces in the queried tiles
    Piece left = board.get(leftOS);

    // check if the pieces match the query
    bool leftMove = left == query || left == queryK;

    // replace with -1 if the piece can't move there
    if (!leftMove) {leftOS = -1;} 
  }
  if (rightEdge) {
    rightOS = -1;
  } else {
    rightOS = pos + offset[i + 1];
    // get the pieces in the queried tiles
    Piece right = board.get(rightOS);

    // check if the pieces match the query
    bool rightMove = right == query || right == queryK;
    
    if (!rightMove) {rightOS = -1;} // piece can't move
  }

  return {leftOS, rightOS};
}

// both directions for king pieces and chained captures
moveList captureBothDirs(const Board& board, int8 pos) {
  // get the enemy colour
  Piece player = board.get(pos);
  // also consider non-king piece for chain captures
  Piece enemy = (player == B || player == BK) ? W : B;

  moveList captures;
  posP emptyU = boardCheck(board, pos, DIAGONAL, UP, E);
  posP emptyD = boardCheck(board, pos, DIAGONAL, DOWN, E);
  posP enemyU = boardCheck(board, pos, ADJACENT, UP, enemy);
  posP enemyD = boardCheck(board, pos, ADJACENT, DOWN, enemy);

  // place in array to iterate
  int8 empties[] = {emptyU.p1, emptyU.p2, emptyD.p1, emptyD.p2};
  int8 enemies[] = {enemyU.p1, enemyU.p2, enemyD.p1, enemyD.p2};
  for (int i = 0; i < 4; i++) {
    if (empties[i] != -1 && enemies[i] != -1) {
      // move can be made
      captures.push_back({ pos, empties[i] });
    }
  }

  return captures;
}

moveList get::moves(const Board& board, int8 pos) {
  Piece player = board.get(pos);
  moveList moves;
  // determine the direction that the piece can go towards
  // black can only move down, white can only move up
  dir_t direction = (player == B || player == BK) ? DOWN : UP;

  posP pcMvs = boardCheck(board, pos, ADJACENT, direction, E);
  if (pcMvs.p1 != -1) {moves.push_back({ pos, pcMvs.p1 });}
  if (pcMvs.p2 != -1) {moves.push_back({ pos, pcMvs.p2 });}
  
  // check the other direction if piece is king
  if (player == WK || player == BK) {
    dir_t opDirection = (direction == DOWN) ? UP : DOWN;
    pcMvs = boardCheck(board, pos, ADJACENT, opDirection, E);

    if (pcMvs.p1 != -1) {moves.push_back({ pos, pcMvs.p1 });}
    if (pcMvs.p2 != -1) {moves.push_back({ pos, pcMvs.p2 });}  
  }

  return moves;
}


// return a list of the captures that a single piece can make
moveList get::captures(const Board& board, int8 pos) {
  Piece player = board.get(pos);
  // determine colour of enemy pieces
  Piece enemy = (player == B || player == BK) ? W : B;
  // king can capture in both directions
  if (player == WK || player == BK) {
    return captureBothDirs(board, pos);
  }

  moveList captures;
  // determine the direction that the piece can go towards
  // if the pieces are not king

  // black can only move down, white can only move up
  dir_t direction = (player == B) ? DOWN : UP;
  posP isEmpty = boardCheck(board, pos, DIAGONAL, direction, E);
  posP isEnemy = boardCheck(board, pos, ADJACENT, direction, enemy);

  // check if the conditions are valid for capture
  if (isEmpty.p1 != -1 && isEnemy.p1 != -1) {
    captures.push_back({ pos, isEmpty.p1 });
  }
  if (isEmpty.p2 != -1 && isEnemy.p2 != -1) {
    captures.push_back({ pos, isEmpty.p2 });
  }
  return captures;
}

// appends the second vector to the first
void merge(moveList& first, const moveList& second) {
  first.reserve(first.size() + second.size());
  first.insert(first.end(), second.begin(), second.end());
}

bool check::moves(moveList& moves, const Board& board, bool player) {
  bool hasMove = false;
  // determine the current piece playing
  // if player is true, black is playing
  Piece piece = player ? B : W;
  Piece pieceK = (piece == B) ? BK : WK;

  for (int i = 0; i < bSize; i++) {
    Piece p = board.get(i);
    if (p == piece || p == pieceK) {
      // get the possible moves
      moveList pieceMoves = get::moves(board, i);
      
      if (!pieceMoves.empty()) {
        merge(moves, pieceMoves); // merge with the move list
        hasMove = true; // player has at least one move
      }
    }
  }
  return hasMove;
}

int8 pieceToRemove(int8 oldPos, int8 newPos) {
  // getting board offsets
  int8 adj[4], dg[4]; 
  rowOS(oldPos, adj); diagOS(dg);

  // the direction that the piece jumped to
  int8 direction = newPos - oldPos;
  for (int i = 0; i < 4; i++) {
    if (direction == dg[i]) {
      return oldPos + adj[i]; // this is the captured piece
    }
  }
  return -1; // never gets here
}

// recursive function to check for capture chains
void checkForChain(bList& boardList, moveList& captures, const Board& board) {
  for (auto capture : captures) {
    // make a copy of the board
    Board bcopy = Board(board.stateString());
    // capture the piece
    bcopy.remove(pieceToRemove(capture.p1, capture.p2));
    bcopy.move(capture.p1, capture.p2);
    // get moves again
    moveList pieceCaps = captureBothDirs(bcopy, capture.p2);

    if (pieceCaps.empty()) {
      // no chains; evaluation is complete
      boardList.push_back(bcopy);
    } else {
      // recursive call
      checkForChain(boardList, pieceCaps, bcopy);
    }
  }
}

// 
void check::captures(bList& boardList, const Board& board, bool player) {
  // determine the current piece playing
  // if player is true, black is playing
  Piece piece = player ? B : W;
  Piece pieceK = (piece == B) ? BK : WK;

  for (int i = 0; i < bSize; i++) {
    Piece p = board.get(i);
    if (p == piece || p == pieceK) {
      // get the possible moves
      moveList pieceCaps = get::captures(board, i);
      
      if (!pieceCaps.empty()) {
        // now we're checking for capture chains
        checkForChain(boardList, pieceCaps, board);
      }
    }
  }
}

// moves the pieces on the board accoring to the move-position pair
Board parseMove(Board board, posP pos) {
  board.move(pos.p1, pos.p2);
  return board;
}

// returns a list of boards that are the results of all possible moves
// that can be made by either the bot or the player
bList boardStates(const Board& board, bool player) {
  
  // initialize lists
  bList boardList;
  moveList moves;

  // check for captures first
  check::captures(boardList, board, player);
  // now check for moves if we still have to
  if (boardList.empty()) {
    // check moves
    bool hasMoves = check::moves(moves, board, player);
    if (hasMoves) {
      for (auto move : moves) {
        boardList.push_back(parseMove(board, move));
      }
    }
  }
  // will return an empty list 
  // if there are no valid moves either i.e. draw
  return boardList;
}