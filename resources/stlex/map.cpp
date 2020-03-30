// compile this example with the c++11 flag
// eg. g++ list.cpp -o list -std=c++11

#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

int main() {
    // maps and unordered maps are associative containers
    // think: python dictionaries

    // map<T, K> assumes the < operator is defined for T and it defines
    // a "total ordering" of all items, the entries will be ordered by key
    map<string, int> grades;

    // unordered_map<T, K> assumes T has a hash function: the STL provides
    // hash functions for primitive types and for strings, you have to
    // define your own hash function for custom types, see documentation
    unordered_map<string, int> ugrades;

    // MAIN DIFFERENCE:
    // map keeps things in sorted order (by key), but
    //   insertions/deletions/lookups/updates take O(log n) time.
    //   supports finding the greatest key <= some query key in O(log n) time
    // unordered_set does not maintain an order, but
    //   insertions/deletions/lookups/updates probably take O(1) time (hashing).
    string names[] = {"Zac", "Omid", "Paul"};
    int scores[] = {82, 85, 93};

    for (int i = 0; i < 3; ++i) {
        grades[names[i]] = scores[i];
        ugrades[names[i]] = scores[i];
    }

    // add one more person
    grades["Ron"] = 95;
    ugrades["Ron"] = 95;

    cout << "Sizes: " << grades.size() << ' ' << ugrades.size() << endl;

    cout << "Map entries:";
    for (map<string, int>::iterator it = grades.begin(); it != grades.end(); ++it) {
        // the iterator has two components: the key and the value
        cout << " (" << it->first << ',' << it->second << ')';
    }
    cout << endl;

    cout << "Unordered map entries:";
    for (unordered_map<string, int>::iterator it = ugrades.begin(); it != ugrades.end(); ++it) {
        // the iterator has two components: the key and the value
        cout << " (" << it->first << ',' << it->second << ')';
    }
    cout << endl;

    cout << "Adding 'Doug' changing the grade for 'Zac', removing 'Omid'..." << endl;
    grades["Doug"] = 16;
    grades["Zac"] = 72;
    grades.erase("Omid");
    cout << "Map entries:";
    for (auto p : grades) {
        cout << " (" << p.first << ',' << p.second << ')';
    }
    cout << endl;

    // can also get the number of buckets in an unordered_map

    return 0;
}
