#include <iostream>
#include <stack>

using namespace std;

// ((4 + 5) - (9 - (8 - 9)))
// ((9) - (9 - (-1))) 
// (9 - (10))
// -1

// (1 - 3 - 3)
// (1 - 6)
// -5
int main() {

    stack<int> val;
    stack<char> op;

    char c;
    while (cin >> c) {
        if (c - '0' >= 0 && c - '9' <= 9) {
            val.push(c - '0');
        } else if (c == '+' || c == '-') {
            op.push(c);
        } else if (c == ')') {
            int x = val.top(); val.pop();
            int y = val.top(); val.pop();
            char o = op.top(); op.pop();
            switch (o) {
                case '+': val.push(y + x); break;
                case '-': val.push(y - x); break;
            }
        }
    }

    cout << val.top() << '\n';

    return 0;
}
