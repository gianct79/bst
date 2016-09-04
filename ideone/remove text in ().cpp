#include <iostream>
#include <stack>


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


unsigned remove_text(char *str, unsigned size) {

    std::stack<unsigned> open;

    for (unsigned i = 0; i < size; i++) {

        if (str[i] == '(')
            open.push(i);
        else if (str[i] == ')' && !open.empty()) {
            unsigned len = i - open.top(); open.pop();
            i -= len;
            size = substr(str, i, len + 1);
        }
    }

    return size;
}


int main() {

    std::string s;
    while (std::cin >> s) {
        unsigned len = remove_text(&s[0], s.size());
        std::cout << "'" << s.c_str() << "' " << len << '\n';
    }

    return 0;
}