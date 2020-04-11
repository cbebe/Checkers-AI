#include "offset.h"

//determines row offset for adjacent tiles
void rowOS(int8 pos, int8 *os) {
  if ((pos % 8) / 4) {
    std::copy(std::begin(os2), std::end(os2), os);
  } else {
    std::copy(std::begin(os1), std::end(os1), os);
  }
}

// copies the diagonal offsets to offset array
void diagOS(int8 *os) {
  std::copy(std::begin(dg), std::end(dg), os);
}