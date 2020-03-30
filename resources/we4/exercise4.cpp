#include <iostream>
#include <string>
#include "hash_table.h"

using namespace std;

// A wrapper for unsigned integers so they have a .hash() method.
struct UIntWrapper {
  unsigned int val;

  unsigned int hash() const {
    return val;
  }

  // still need this for the HashTable
  bool operator!=(const UIntWrapper& rhs) const {
    return val != rhs.val;
  }
};

int main() {
  HashTable<UIntWrapper> table(20);

  while (true) {
    string ins;
    cin >> ins;

    // Process commands that do not have an integer component.
    if (ins == "S") {
      cout << "size is " << table.size() << endl;
      continue;
    }
    else if (ins == "STOP") {
      break;
    }

    // Otherwise, we are going to read an integer.
    UIntWrapper integer;
    cin >> integer.val;

    if (ins == "I") {
      table.insert(integer);
    }
    else if (ins == "Q") {
      if (table.contains(integer)) {
        cout << "found" << endl;
      }
      else {
        cout << "not found" << endl;
      }
    }
    else if (ins == "R") {
      table.remove(integer);
    }
  }

  return 0;
}
