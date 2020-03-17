#ifndef RESTLIST_H
#define RESTLIST_H

#define JOY_SEL 53
#define NUM_LINES 21

struct RestDist {
  uint16_t index;
  uint16_t dist;
};

void loadAllRestaurants();
void joySelect(int prevRest);
void goToResto();
extern int8_t selectedRest;

#endif