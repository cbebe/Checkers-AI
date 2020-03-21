#include <iostream>
using namespace std;

int main() {
  for (int i = 0; i < 32; i++) {
    bool k = (i % 8) / 4;
    cout << i << ": " << k << endl;
    if ((i % 8)/4) {
      cout << "second" << endl;
    }
    if (!((i%8)/4)) {
      cout << "first" << endl;
    }
  }
  return 0;
}