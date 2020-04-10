#include <iostream>
#include <list>
using namespace std;

int foo(int x = 1, int y = 2) {
  cout << x << endl;
  return y;
}

int main() {
  // cout << foo() << endl;
  double x = -1.5;
  if (x) {
    cout << x * 45 << endl;
  }
  return 0;
}