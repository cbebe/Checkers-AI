#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {
    // ******** STRINGS **********
    cout << "----- STRINGS -----" << endl;
    string s = "Zachary";
    cout << s << endl;
    cout << s.substr(3, 4) << endl;

    string mid = "L";
    s += " " + mid + " Friggstad";
    cout << s << endl;

    s.push_back('!');
    cout << s << endl << endl;

    // ******** SORTING **********
    cout << "----- SORTING -----" << endl;
    int array[] = {3, -1, 27, 1, 0, 1, 3, 15, -3};
    // provide the start pointer and a pointer that is one past the end of the array
    sort(array, array+9);
    for (int i = 0; i < 9; ++i) {
        cout << array[i] << ' ';
    }
    cout << endl;

    string names[] = {"Daya", "Eve", "Ethan", "Shay", "Beth", "Prosenjit"};
    // can sort any type that has < implemented
    sort(names, names+6);
    for (int i = 0; i < 6; ++i) {
        cout << names[i] << ' ';
    }
    cout << endl;

    vector<int> vec;
    for (int i = 10; i >= 0; --i) {
        vec.push_back(i);
    }
    // can sort anything with random access iterators
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << endl << endl;

    // ******** NTH ELEMENT **********
    cout << "----- NTH ELEMENT -----" << endl;
    int array2[] = {3, -1, 27, 1, 0, 1, 3, 15, -3};

    /*
        Rearranges the array so the nth element in the sorted order
        is at the nth position.
        Running time: Typically O(n) (so it does not fully sort)

        Parameters:
         - pointer to start
         - pointer to the location where the nth element should be
           in the sorted list
         - pointer one past the end
    */
    nth_element(array2, array2+2, array2+9);
    cout << "Check that index 2 is correct: ";
    for (int i = 0; i < 9; ++i) {
        cout << array2[i] << ' ';
    }
    cout << endl << endl;

    // ******** REVERSE **********
    cout << "----- REVERSE -----" << endl;
    reverse(vec.begin(), vec.end());
    // also works with arrays: reverse(array, array+n);
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << endl << endl;

    // ******** LOWER_BOUND **********
    cout << "----- LOWER_BOUND -----" << endl;

    sort(array, array+9); // in case we did something since last time
    int pos = lower_bound(array, array+9, 7)-array;
    cout << "The first item in 'array' that is not < 7 is at index " << pos << endl
         << " and has value: " << array[pos] << endl;

    sort(vec.begin(), vec.end());
    vector<int>::iterator iter = lower_bound(vec.begin(), vec.end(), 5);
    cout << "The first item in 'vec' that is not < 5 is at index " << (iter-vec.begin()) << endl
         << " and has value: " << *iter << endl;


    return 0;
}
