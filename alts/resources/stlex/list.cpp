// compile this example with the c++11 flag
// eg. g++ list.cpp -o list -std=c++11

#include <iostream>
#include <list>

using namespace std;

int main() {
    int vals[] = {1, 18, 21, 24, 18, 19, 21};

    // can construct a list using a range of values
    // also works with iterators
    list<int> lst(vals, vals+7);

    cout << "List size: " << lst.size() << endl;

    cout << "List contents:";
    for (list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        cout << ' ' << *it;
    }
    cout << endl;

    // remove all occurrences of 21
    lst.remove(21);

    cout << "List size after removing all 21s: " << lst.size() << endl;

    cout << "List contents:";
    for (list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        cout << ' ' << *it;
    }
    cout << endl;

    cout << "Reversing list..." << endl;
    lst.reverse();
    cout << "Contents of list after reversal";
    for (auto x : lst) {
        cout << ' ' << x;
    }
    cout << endl;

    return 0;
}
