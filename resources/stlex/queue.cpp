#include <iostream>
#include <queue>

using namespace std;

int main() {
    queue<int> qu;

    cout << "Pushing 0 through 9 on the quack..." << endl;
    for (int i = 0; i < 10; ++i) {
        qu.push(i);
    }

    cout << "Printing and popping first 5 items...";
    for (int i = 0; i < 5; ++i) {
        cout << ' ' << qu.front();
        qu.pop();
    }

    cout << endl;
    cout << "Size is now: " << qu.size() << endl;

    cout << "Pushing 17 and 24" << endl;
    qu.push(17);
    qu.push(24);
    cout << "Size is now: " << qu.size() << endl;

    cout << "Printing and popping the remaining items...";
    while (!qu.empty()) {
        cout << ' ' << qu.front();
        qu.pop();
    }
    cout << endl;

    cout << "Size is now: " << qu.size() << endl;

    return 0;
}
