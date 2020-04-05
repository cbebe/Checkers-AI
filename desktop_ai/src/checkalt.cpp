#include "checkalt.h"

//determines row offset for adjacent tiles
void rowOS(int8 pos, int8 *os) {
  using namespace std;
  if ((pos % 8) / 4) {
    copy(begin(os2), end(os2), os);
  } else {
    copy(begin(os1), end(os1), os);
  }
}

// copies the diagonal offsets to offset array
void diagOS(int8 *os) {
  std::copy(std::begin(dg), std::end(dg), os);
}

/* 
boolP boardCheck:
checks if tiles are empty/have enemies
neighbour is either adjacent or diagonal, 
for checking moves or jumps.
query is either empty or the enemy piece.
direction is either up or down, 
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

  int8 i = (direction == UP) ? 0 : 2; // starting index for offset
  int8 leftOS = pos + offset[i];
  int8 rightOS = pos + offset[i + 1];
  // get the pieces in the queried tiles
  Piece left = board.get(leftOS);
  Piece right = board.get(rightOS);

  // check if the pieces match the query
  bool leftMove = left == query || left == queryK;
  bool rightMove = right == query || right == queryK;
  
  // replace with -1 if the piece can't move there
  if (!leftMove) {leftOS = -1;}
  if (!rightMove) {rightOS = -1;}

  return {leftOS, rightOS};
}

// both directions for king pieces and chained captures
moveList captureBothDirs(const Board& board, int8 pos, Piece enemy) {
  moveList moves;
  posP emptyU = boardCheck(board, pos, DIAGONAL, UP, E);
  posP emptyD = boardCheck(board, pos, DIAGONAL, DOWN, E);
  posP enemyU = boardCheck(board, pos, ADJACENT, UP, enemy);
  posP enemyD = boardCheck(board, pos, ADJACENT, DOWN, enemy);

  int8 empties[] = {emptyU.p1, emptyU.p2, emptyD.p1, emptyD.p2};
  int8 enemies[] = {enemyU.p1, enemyU.p2, enemyD.p1, enemyD.p2};
  for (int i = 0; i < 4; i++) {
    if (empties[i] != -1 && enemies[i] != -1) {
      moves.push_back({ CAPTURE, { pos, empties[i] }});
    }
  }

  return moves;
}

moveList get::moves(const Board& board, int8 pos) {
  Piece player = board.get(pos);
  moveList moves;
  // determine the direction that the piece can go towards
  // black can only move down, white can only move up
  dir_t direction = (player == B || player == BK) ? DOWN : UP;

  posP pcMvs = boardCheck(board, pos, ADJACENT, direction, E);
  if (pcMvs.p1 != -1) {moves.push_back({ MOVE, { pos, pcMvs.p1 } });}
  if (pcMvs.p2 != -1) {moves.push_back({ MOVE, { pos, pcMvs.p2 } });}
  
  // check the other direction if piece is king
  if (player == WK || player == BK) {
    dir_t opDirection = (direction == DOWN) ? UP : DOWN;
    pcMvs = boardCheck(board, pos, ADJACENT, opDirection, E);

    if (pcMvs.p1 != -1) {moves.push_back({ MOVE, { pos, pcMvs.p1 } });}
    if (pcMvs.p2 != -1) {moves.push_back({ MOVE, { pos, pcMvs.p2 } });}  
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
    return captureBothDirs(board, pos, enemy);
  }

  moveList moves;
  // determine the direction that the piece can go towards
  // if the pieces are not king

  // black can only move down, white can only move up
  dir_t direction = (player == B) ? DOWN : UP;
  posP isEmpty = boardCheck(board, pos, DIAGONAL, direction, E);
  posP isEnemy = boardCheck(board, pos, ADJACENT, direction, enemy);

  // check if the conditions are valid for capture
  if (isEmpty.p1 != -1 && isEnemy.p1 != -1) {
    moves.push_back({ CAPTURE, { pos, isEmpty.p1 } });
  }
  if (isEmpty.p2 != -1 && isEnemy.p2 != -1) {
    moves.push_back({ CAPTURE, { pos, isEmpty.p2 } });
  }
  return moves;
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
        moves.merge(pieceMoves); // merge with the move list
        hasMove = false; // player has at least one move
      }
    }
  }
  return hasMove;
}

bool check::captures(capList& captures, const Board& board, bool player) {

}

Board parse::capture(Board board, capSt capture) {

}

// moves the pieces on the board accoring to the move-position pair
Board parse::move(Board board, moveP moveQ) {
  board.move(moveQ.pos.p1, moveQ.pos.p2);
  return board;
}

std::list<Board> boardStates(const Board& board, bool player) {
  
  // initialize lists
  std::list<Board> boardList;
  moveList moves; capList captures;

  // check for captures first
  bool mustCapture = check::captures(captures, board, player);
  // now check for moves if we still have to
  if (!mustCapture) {
    // check moves
    bool hasMoves = check::moves(moves, board, player);
    if (hasMoves) {
      for (auto move : moves) {
        boardList.push_back(parse::move(board, move));
      }
    }
  } else {
    for (auto capture : captures) {
      boardList.push_back(parse::capture(board, capture));
    }
  }
  
  // will return an empty list 
  // if there are no valid moves either i.e. draw
  return boardList;
}