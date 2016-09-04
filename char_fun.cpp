/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <stack>
#include <vector>

#include <ctype.h>
#include <string.h>

using namespace std;

unsigned substr(char *str, unsigned pos, unsigned len) {
    char *w = str + pos;
    char *r = w + len;
    while (r && *r)
        *w++ = *r++;
    if (w)
        *w = '\0';
    return w - str;
}

unsigned substr_i(char *str, unsigned pos, unsigned len) {
    unsigned w = pos;
    unsigned r = w + len;
    while (str[r])
        str[w++] = str[r++];
    if (str[w])
        str[w] = '\0';
    return w;
}

unsigned remove_text_in_parenthesis(char *str, unsigned size) {
    stack<unsigned> open;
    for (unsigned i = 0; i < size; i++) {
        if (str[i] == '(') {
            open.push(i);
        } else if (str[i] == ')' && !open.empty()) {
            unsigned len = i - open.top();
            open.pop();
            i -= len;
            size = substr(str, i, len + 1);
        }
    }
    return size;
}

string reverse(const string &src) {
    stack <string> heap;
    string temp;
    for (auto it : src) {
        temp += it;
        if (isspace(it)) {
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

unsigned count_words(const string &src) {
    unsigned cnt = 0;
    string temp;
    for (auto it : src) {
        if (isspace(it)) {
            if (temp.length() > 0) {
                cnt++;
                temp.erase();
            }
        } else {
            temp += it;
        }
    }
    if (temp.length() > 0) {
        cnt++;
    }
    return cnt;
}

unsigned count_words(char *src) {
    unsigned cnt = 0;
    char *s = src;
    char *r = src;
    for (; r && *r; r++) {
        if (isspace(*r)) {
            if (s < r) {
                cnt++;
            }
            s = r + 1;
        }
    }
    if (s < r) {
        cnt++;
    }
    return cnt;
}

unsigned count_chars(const string &src, const char c) {
    unsigned cnt = 0;
    for (auto it : src) {
        if (c == it) {
            cnt++;
        }
    }
    return cnt;
}

char *remove_chars(char *src, const char c) {
    char *s = src;
    char *w = src;
    for (char *r = src; r && *r; r++) {
        if (c == *r)
            continue;
        *w = *r;
        w++;
    }
    if (w) {
        *w = '\0';
    }
    return s;
}

int main() {

    string test("the quick brown fox jumps over the lazy dog!");

    cout << reverse(test) << '\n';
    cout << reverse("") << '\n';

    cout << count_chars("ab*cde**fgh***", '*') << '\n';
    cout << count_chars("", ' ') << '\n';

    cout << count_words(test) << '\n';

    cout << count_words("the quick brown fox jumps over the lazy dog") << '\n';
    cout << count_words("") << '\n';
    cout << count_words("  ") << '\n';
    cout << count_words(" a") << '\n';

    vector<char> stuff(9);

    strcpy(&stuff[0], "ab*de*gh");
    cout << remove_chars(&stuff[0], '*') << '\n';

    strcpy(&stuff[0], "********");
    cout << remove_chars(&stuff[0], '*') << '\n';

    strcpy(&stuff[0], "abc efg ");
    cout << remove_chars(&stuff[0], ' ') << '\n';

    strcpy(&stuff[0], "");
    cout << remove_chars(&stuff[0], ' ') << '\n';

    string s = {"0123(45)6789"};
    cout << s.c_str() << '\n';

    remove_text_in_parenthesis(&s[0], test.size());
    cout << s.c_str() << '\n';

    return 0;
}
