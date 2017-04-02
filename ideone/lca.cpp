#include <iostream>
#include <vector>

struct node {
    char value;
    std::vector<node*> children;
};

node *get_lca(node *root, node *a, node *b) {

    if (root == nullptr)
        return nullptr;

    if (root->value == a->value || root->value == b->value)
        return root;

    auto h = 0;
    node *last = nullptr;

    for (auto &n : root->children) {
        node *node = get_lca(n, a, b);
        if (node) {
            last = node;
            h++;
        }
        if (h >= 2)
            return root;
    }

    return last;
}

node *get_lca_2(node *root, node *a, node *b) {
    if (!root || root->value == a->value || root->value == b->value) {
        return root;
    }
    node *l = get_lca_2(root->children[0], a, b);
    node *r = get_lca_2(root->children[1], a, b);
    if (l && r) {
        return root; // if a->value, b->value are on both sides
    }
    return l ? l : r; // either one of a->value, b->value is on one side OR a->value, b->value is not in left & right subtrees
}

bool find(node *root, char v) {
    if (!root) {
        return false;
    }
    if (root->value == v) {
        return true;
    }
    for (auto &n : root->children) {
        if (find(n, v)) {
            return true;
        }
    }
    return false;
}

bool path(node *root, char v, std::vector<char> &p) {
    if (!root) {
        return false;
    }
    if (root->value == v) {
        p.push_back(root->value);
        return true;
    }
    for (auto &n : root->children) {
        if (path(n, v, p)) {
            p.push_back(root->value);
            return true;
        }
    }
    return false;
}

int main()
{
    node f { 'F' };
    node g { 'G' };
    node e { 'E', { &f, &g } };

    node h { 'H' };
    node i { 'I' };
    node b { 'B', { &h, &e, &i } };

    node c { 'C' };
    node d { 'D' };
    node a { 'A', { &b, &c, &d } };

    std::cout << get_lca(&a, &a, &a)->value << '\n';
    std::cout << get_lca(&a, &f, &g)->value << '\n';
    std::cout << get_lca(&a, &f, &i)->value << '\n';
    std::cout << get_lca(&a, &f, &d)->value << '\n';
    std::cout << get_lca(&a, &e, &g)->value << '\n';

    return 0;
}
