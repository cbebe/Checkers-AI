#include <stdio.h>

int main() {
  enum {E, W, B, WK, BK} p = W;
  printf("%c\n", (char) p + '0');
  return 0;
}