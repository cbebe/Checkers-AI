#include <iostream>
#include <list>
using namespace std;

int foo(int x = 1, int y = 2) {
  cout << x << endl;
  return y;
}

int main() {
  cout << foo() << endl;

  return 0;
}