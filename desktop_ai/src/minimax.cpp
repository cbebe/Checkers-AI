#include "minimax.h"

static long long nodes;

// lets the AI choose a move based on minimax
Board chooseMove(const Board& board, int difficulty) {
  using std::cout;
  using std::endl;
  srand(time(NULL)); // time seed for rand function
  nodes = 0; // reset the number of children

  // get the possible moves the AI can make
  bList boardList = boardStates(board, true);

  // chance that the AI will make a random move
  // the higher the difficulty the lower the chance
  if (!(rand() % difficulty)) {
    cout << "RANDOM MOVE" << endl; 
    // AI has chosen a random move
    return boardList[rand() % boardList.size()];
  }

  // now the AI will use minimax to find the best move
  
  double maxVal = -inf; // the AI is the maximizing player
  int depth = 9; // max working depth is 9 
  Board bestBoard;
  
  {
    using namespace std::chrono;
    // time the function
    auto start = high_resolution_clock::now();
    for (auto bEval : boardList) {
      // get the evaluation of the move
      double eval = minimax(bEval, depth, true, -inf, inf);

      if (eval > maxVal) {
        // this is the new chosen board      
        bestBoard = bEval;
        maxVal = eval;
      }
    }
    auto end = high_resolution_clock::now();
    auto exectime = duration_cast<microseconds>(end - start);
    // display execution time
    printf("Execution time: %ld microseconds\n", exectime.count());
  }

  // print board value
  cout << "Board value: " << maxVal << endl;
  cout << "Number of children: " << nodes << endl;
  
  return bestBoard;
}

// recursive function to find the min/max value of a move
double minimax(const Board& board, int depth, bool maxPlayer, double alpha, double beta) {
  if (depth == 0) {
    return staticEval(board);
  } else if (gameOver(board)) {
    std::cout << "Someone won" << std::endl;
    // either side's pieces are all captured
    return staticEval(board); 
  }
  // get the possible moves that the player can make
  bList bStates = boardStates(board, maxPlayer);
  if (bStates.empty()) {
    std::cout << "Out of moves" << std::endl;
    return staticEval(board); // game has ended; no more moves
  }

  double compEval = maxPlayer ? -inf : inf;

  for (auto child : bStates) {
    nodes++; // count the number of children in the tree
    double eval = minimax(child, depth - 1, !maxPlayer, alpha, beta);

    // keep track of the best and worst values so far (alpha/beta)
    if (maxPlayer) {
      compEval = std::max(compEval, eval);
      alpha = std::max(alpha, eval);
    } else {
      compEval = std::min(compEval, eval);
      beta = std::min(beta, eval);
    }
    // prune branches if it would not affect the outcome
    if (beta <= alpha) {break;}
  }
  // return the min/max value acquired
  return compEval;
}