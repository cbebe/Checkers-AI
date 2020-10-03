#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> st;

    cout << "Pushing 0 through 9 on the stack..." << endl;
    for (int i = 0; i < 10; ++i) {
        st.push(i);
    }

    cout << "Printing and popping first 5 items...";
    for (int i = 0; i < 5; ++i) {
        cout << ' ' << st.top();
        st.pop();
    }

    cout << endl;
    cout << "Size is now: " << st.size() << endl;

    cout << "Pushing 17 and 24" << endl;
    st.push(17);
    st.push(24);
    cout << "Size is now: " << st.size() << endl;

    cout << "Printing and popping the remaining items...";
    while (!st.empty()) {
        cout << ' ' << st.top();
        st.pop();
    }
    cout << endl;
    
    cout << "Size is now: " << st.size() << endl;

    return 0;
}
