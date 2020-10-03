#include <iostream>
#include <vector>

using namespace std;

int main() {
    // a vector of size 100
    vector<int> vec(5);



    for (int i = 0; i < vec.size(); ++i) {
        vec[i] = i+1;
    }

    vec.push_back(17);

    cout << "Vector size & capacity of underlying array: ";
    cout << vec.size() << ' ' << vec.capacity() << endl;
    cout << "Contents:";
    for (int i = 0; i < vec.size(); ++i) {
        cout << ' ' << vec[i];
    }
    cout << endl;

    vec.pop_back();
    cout << "Contents:";
    for (int i = 0; i < vec.size(); ++i) {
        cout << ' ' << vec[i];
    }
    cout << endl;

    // zero out all entries manually
    for (vector<int>::iterator it = vec.begin(); it < vec.end(); ++it) {
        *it = 0;
    }

    cout << "Contents:";
    for (auto x : vec) {
        cout << ' ' << x;
    }
    cout << endl;

    vec.clear();
    cout << "Should be 0: " << vec.size() << endl;

    return 0;
}
