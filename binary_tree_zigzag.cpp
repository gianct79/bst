/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <stack>

struct node {
    int value;
    node *left;
    node *right;
};


void bfs(node *root) {
    std::stack < node * > cur_level;
    std::stack < node * > next_level;

    bool flag = false;

    cur_level.push(root);

    while (!cur_level.empty()) {

        auto *tmp = cur_level.top();
        cur_level.pop();

        if (tmp) {
            std::cout << tmp->value << ' ';
            if (flag) {
                next_level.push(tmp->left);
                next_level.push(tmp->right);
            } else {
                next_level.push(tmp->right);
                next_level.push(tmp->left);
            }
        }

        if (cur_level.empty()) {
            std::cout << '\n';
            std::swap(cur_level, next_level);
            flag = !flag;
        }
    }
}


int main() {
    node _1{1, nullptr, nullptr};
    node _3{3, nullptr, nullptr};
    node _2{2, &_1, &_3};
    node _5{5, nullptr, nullptr};
    node _7{7, nullptr, nullptr};
    node _6{6, &_5, &_7};
    node _4{4, &_2, &_6};

    node _9{9, nullptr, nullptr};
    node _11{11, nullptr, nullptr};
    node _10{10, &_9, &_11};
    node _13{13, nullptr, nullptr};
    node _15{15, nullptr, nullptr};
    node _14{14, &_13, &_15};
    node _12{12, &_10, &_14};

    node _8{8, &_4, &_12};

    bfs(&_8);

    return 0;
}