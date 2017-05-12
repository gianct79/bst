#include <iostream>

using namespace std;

struct node {
    int val;
    node *next;
};

void print(node* list) {
    node *curr = list;
    while (curr) {
        cout << curr->val << ' ';
        curr = curr->next;
    }
}

node *clone(node *list) {
    node *curr = list;
    node *prev, *head = nullptr;
    while (curr) {
        node *temp = new node { curr->val };
        if (!head) {
            head = temp;
        } else {
            prev->next = temp;
        }
        prev = temp;
        curr = curr->next;
    }
    return head;
}

int main() {

    auto n = new node {1, new node { 2, new node { 3, new node { 4 } } } };
    print(n);

    cout << '\n';

    auto m = clone(n);
    print(m);

    return 0;
}
