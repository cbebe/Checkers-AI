#ifndef _OFFSET_H_
#define _OFFSET_H_

#include <algorithm> // for copy
#include <vector> // for begin and end
#include "piece.h"

// const arrays for offsets
const int8 os1[] = {-4, -3, 4, 5};
const int8 os2[] = {-5, -4, 3, 4};
const int8 dg[] = {-9, -7, 7, 9};

void rowOS(int8 pos, int8 *os);
void diagOS(int8 *os);

#endif