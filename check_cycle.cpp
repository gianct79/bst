/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <vector>

using namespace std;

struct node {
    int value;
    node *next;

    node() {
        next = 0;
    }
};

struct list {
    node *first;
    node *last;

    list() {
        first = 0;
    }

    ~list() {
        for (node *curr = first; curr;) {
            node *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void add(int v) {
        node *n = new node();
        n->value = v;

        if (!first)
            first = n;
        else
            last->next = n;

        last = n;
    }

    bool hasCycle() {
        node *turt = first;
        node *hare = first;

        while (turt && hare) {
            hare = hare->next;
            if (hare == turt) {
                return true;
            }
            if (hare) {
                hare = hare->next;
            }
            if (turt == hare) {
                return true;
            }
            turt = turt->next;
        }
        return false;
    }

    void print() {
        node *curr = first;
        while (curr) {

            cout << curr->value << ',';
            curr = curr->next;
            if (curr == first)
                curr = 0;
        }
        cout << endl;
    }
};

int main() {

    list l;
    l.print();
    cout << l.hasCycle() << endl;

    l.add(1);
    l.add(2);
    l.add(5);
    l.add(40);
    l.add(20);
    l.add(30);
    l.print();
    cout << l.hasCycle() << endl;

    l.add(15);
    l.print();
    cout << l.hasCycle() << endl;

    l.last->next = l.first;

    //l.print();
    cout << l.hasCycle() << endl;

    return 0;
}