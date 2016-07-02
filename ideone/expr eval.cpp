#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

int apply(stack<char> &ops, stack<int> &values) {
	int b = values.top(); values.pop();
	int a = values.top(); values.pop();
	char op = ops.top(); ops.pop();
	//cout << "DBG " << a << op << b << '\n';
	switch (op) {
		case '+': return a + b; break;
		case '-': return a - b; break;
		case '*': return a * b; break;
		case '/': return a / b; break;
	}
	return 0;
}

bool has_precedence(char op1, char op2) {
    if (op2 == '(' || op2 == ')') {
        return false;
    }
    if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-')) {
        return false;
    }
    return true;
}

int eval(string const &s) {

	stack<int> values;
	stack<char> ops;

	for (int i = 0; i < s.size(); ++i) {
		char c = s[i];
		if (isspace(c)) {
			continue;
		}
		if (isdigit(c)) {
			int t = 0;
			for (; i < s.size() && isdigit(s[i]); ++i) {
				t *= 10;
				t += s[i] - '0';
			}
			values.push(t); 
			i--;
		} else if (c == '(') {
			ops.push(c);
		} else if (c == ')') {
			while (ops.top() != '(') {
				values.push(apply(ops, values));
			}
			ops.pop();
		} else if (c == '+' || c == '-' || c == '*' || c == '/') {
			while (!ops.empty() && has_precedence(c, ops.top())) {
				values.push(apply(ops, values));
			}
			ops.push(c);
		}
	}
	while (!ops.empty()) {
		values.push(apply(ops, values));
	}
	return values.top();
}

int main() {
	string s;
	while (getline(cin, s)) {
		cout << s << " = " << eval(s) << '\n';
	}
	return 0;
}

/*
int eval(const char *expr) {
    int ax = 0;
    int op = 1;
    for (; *expr; ) {
        if (isdigit(*expr)) {
            int n = 0;
            while (isdigit(*expr)) {
                n *= 10;
                n += *expr++ - '0';
            }
            ax += (op * n);
            // reset flags
            op = 1;
        } else {
            if (*expr == '+') {
                // op *= 1; ;
            } else if(*expr == '-') {
                op *= -1;
            } else {
                // error 
            }
            ++expr;
        }
    }
    return ax;
}
*/
