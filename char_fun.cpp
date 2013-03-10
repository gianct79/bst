/*
 * Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
 */

#include <iostream>
#include <stack>

#include <ctype.h>
#include <string.h>

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

size_t countWords(const string &src) {

    size_t count = 0;
    string temp;
    
    for (auto it = src.begin(); it != src.end(); ++it) {
        if (isspace(*it)) {
            if (temp.length() > 0) {
                count++;
                temp.erase();
            }
        } else {
            temp += *it;
        }
    }
    if (temp.length() > 0) {
        count++;
    }
    
    return count;
}

size_t countChars(const string &src, const char c) {
    size_t cnt = 0;
    for (auto it = src.begin(); it != src.end(); ++it) {
	if (c == *it) {
	    cnt++;
	}
    }
    return cnt;
}

char *removeChars(char *src, const char c) {
    char *s = src;
    char *w = src;
    for (char *r = src; r && *r; r++) {
	if (c == *r)
	continue;
	*w = *r; w++;
    }

    if (w) {
	*w = '\0';
    }

    return s;
}

int main() {

    cout << reverse("the quick brown fox jumps over the lazy dog!") << endl;
    cout << reverse("") << endl;

    cout << countChars("ab*cde**fgh***", '*') << endl;
    cout << countChars("", ' ') << endl;

    cout << countWords("the quick brown fox jumps over the lazy dog!") << endl;
    cout << countWords("") << endl;
    cout << countWords("  ") << endl;
    cout << countWords(" a") << endl;

    char *stuff = new char[9];

    strcpy(stuff, "ab*de*gh");
    cout << removeChars(stuff, '*') << endl;

    strcpy(stuff, "********");
    cout << removeChars(stuff, '*') << endl;

    strcpy(stuff, "abc efg ");
    cout << removeChars(stuff, ' ') << endl;

    strcpy(stuff, "");
    cout << removeChars(stuff, ' ') << endl;

    delete [] stuff;

    cout << removeChars(nullptr, '*') << endl;

    //char *stuffa = "ab*de*gh";
    //cout << removeChars(stuffa, '*') << endl; // pow!

    return 0;
}
