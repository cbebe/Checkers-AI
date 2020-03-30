// compile this example with the c++11 flag
// eg. g++ list.cpp -o list -std=c++11

#include <iostream>
#include <set>
#include <unordered_set>

using namespace std;

int main() {
    int vals[] = {7, 2, 15, 21, -5, -1, 7, 2, 2, 2};

    // the following are equivalent to declaring, eg.,
    // set<int> st;
    // and then inserting all elements of vals[] with a loop

    // set<T> assumes the < operator is defined for T and it defines
    // a "total ordering" of all items
    set<int> st(vals, vals+10);

    // unordered_set<T> assumes T has a hash function: the STL provides
    // hash functions for primitive types and for strings, you have to
    // define your own hash function for custom types, see documentation
    unordered_set<int> ust(vals, vals+10);

    // MAIN DIFFERENCE:
    // set keeps things in sorted order, but
    //   insertions/deletions/lookups take O(log n) time.
    //   supports finding the greatest item <= some query in O(log n) time
    // unordered_set does not maintain an order, but
    //   insertions/deletions/lookups probably take O(1) time (hashing).

    cout << "Sizes: " << st.size() << ' ' << ust.size() << endl;

    cout << "Contents of set:";
    for (set<int>::iterator it = st.begin(); it != st.end(); ++it) {
        cout << ' ' << *it;
    }
    cout << endl;

    cout << "Contents of unordered set:";
    for (unordered_set<int>::iterator it = ust.begin(); it != ust.end(); ++it) {
        cout << ' ' << *it;
    }
    cout << endl;

    cout << "Removing 21 and adding 45 to the set..." << endl;
    st.erase(21);
    st.insert(45);
    cout << "Contents of set:";
    for (auto x : st) {
        cout << ' ' << x;
    }
    cout << endl;

    cout << "Number of buckets in the unordered_set: " << ust.bucket_count() << endl;

    return 0;
}
