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