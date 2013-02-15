/*
 * Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
 */

#include <iostream>

#include <stack>
#include <ctype.h>

using namespace std;

string reverse(const string &src) {

	stack<string> heap;

	string temp;
	for (auto it = src.begin(); it != src.end(); ++it) {
		temp += *it;
		if (isspace(*it)) {
			heap.push(temp);
			temp.erase();
		}
	}
	heap.push(temp);

	temp.erase();
	while (!heap.empty()) {
		temp += heap.top();
		heap.pop();
	}

	return temp;
}

int main() {

	cout << reverse("the quick brown fox jumps over the lazy dog!") << endl;
	cout << reverse("") << endl;

	return 0;
}
