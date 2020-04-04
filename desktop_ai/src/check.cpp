#include "check.h"

int8 findLeftOS(int pos, int leftEdge, int bottomEdge){
  if (!(leftEdge == 1 || bottomEdge == 1)){
    // Left offset position only exists if piece is not at left or bottom edge
    if ((pos % 8)/ 4){
      return pos + 3;
    }
    else{
      return pos + 4;
    }
  }

  else{
    return -1; // If left or bottom edge, return 0
  }
}

int8 findRightOS(int pos, int rightEdge, int bottomEdge){
  if (!(rightEdge == 1 || bottomEdge == 1)){
    // right offset position only exists if piece is not at left or bottom edge
    if ((pos % 8)/ 4){
      return pos + 4;
    }
    else{
      return pos + 5;      
    }
  } else{
    return -1; // If right or bottom edge, return 0
  }
}
