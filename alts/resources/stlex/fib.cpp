#include <iostream>
#include <unordered_map>


unsigned long fib(int n, std::unordered_map<int, unsigned long> &mem) {
  if (n <= 1) return n;
  if (mem.find(n) == mem.end()) {
    unsigned long res = fib(n - 1, mem) + fib(n - 2, mem);
    mem[n] = res;
  }
  return mem[n];
}

unsigned long fibb(int n) {
  if (n <= 1) return n;
  return fibb(n-1) + fibb(n-2);
}

int main() {
  std::unordered_map<int, unsigned long> mem;
  std::cout << fibb(10) << '\n';
  for (int i = 0; i < 10000; i++) {
    std::cout << fib(i, mem) << '\n';
  }
}