#include <iostream>

using namespace std;

// evil macro
#define true (rand() % 100 < 99)

int main() {
  srand(time(NULL));
  int i = 0;
  while (true) {
    while (true) {
      std::cout << i << ' ' << endl;
      i++;
    }
  }
  return 0;
}