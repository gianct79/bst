/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

template<typename node_type>
void fix_siblings(node_type *root) {
    queue < node_type * > visited;
    visited.push(root);
    visited.push(0);
    while (node_type *f = visited.front()) {
        visited.pop();
        f->sibling = visited.front();
        if (f->left()) {
            visited.push(f->left());
        }
        if (f->right()) {
            visited.push(f->right());
        }
        if (f->sibling == 0) {
            visited.pop();
            visited.push(0);
        }
    }
}

struct Node {
    Node(char value, Node *left, Node *right) :
            value(value),
            left_(left),
            right_(right),
            sibling(0) { }

    const char value;
    Node *left_;
    Node *right_;
    Node *sibling;

    Node *left() const { return left_; }

    Node *right() const { return right_; }
};

template<typename TInput>
Node *read(TInput &input) {
    char c = input.get();

    if (c == TInput::traits_type::eof() || c == '.') {
        return 0;
    }

    Node *left = read(input);
    Node *right = read(input);

    return new Node(c, left, right);
}

template<typename node_type, typename output_type>
void print_siblings(output_type &out, node_type *n) {
    queue < node_type * > visited;
    visited.push(n);
    while (!visited.empty()) {
        node_type *f = visited.front();
        visited.pop();
        out << f->value;
        if (f->left()) {
            visited.push(f->left());
        }
        if (f->right()) {
            visited.push(f->right());
        }
        if (f->sibling == 0) {
            out << "\n";
        }
    }
}

template<typename node_type, typename output_type>
void print_binary_tree(output_type &out, node_type *n, std::size_t depth = 0, char connector = '+') {
    if (!n) {
        return;
    }

    print_binary_tree(out, n->right(), depth + 1, '/');

    for (int i = depth; i--;) {
        out << "    ";
    }
    out << ' ' << connector << "--" << n->value << endl;

    print_binary_tree(out, n->left(), depth + 1, '\\');
}

int main() {
    string input("RAC...BD..EF..G..");
    //string input("R.C.BD..EF..G..");
    //string input("4217..8..39..A..5.6B..");
    //string input("421.7..3..5G..6B.");
    //string input("42.Z..5B");
    //string input("421..3Z...5G..6B.");
    getline(cin, input);

    stringstream in(input);
    Node *root = read(in);

    print_binary_tree(cout, root);

    fix_siblings(root);

    ostringstream out;
    print_siblings(out, root);

    cout << endl << "result:" << endl << out.str() << endl;

    string expected("R|AB|CDE|FG|");
    //string expected("R|C|B|DE|FG|");
    //string expected("4|25|136|789AB|");
    //string expected("4|25|13G6|7B|");
    //string expected("4|25|ZB|");
    //string expected("4|25|13G6|ZB|");
    getline(cin, expected);
    replace(expected.begin(), expected.end(), '|', '\n');

    if (out.str() == expected) {
        cout << "success" << endl;
    } else {
        cout << "WRONG, expected:" << endl << expected << endl;
    }
}