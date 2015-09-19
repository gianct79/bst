/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>

using namespace std;

struct node {
    int value;
    node *next;
};

struct list {

    node *first;

    list() {
        first = 0;
    }

    ~list() {

        node *curr = first;

        while (curr) {
            node *aux = curr;
            curr = curr->next;

            delete aux;
        }
    }

    node *add(int v) {

        node *tail = last();

        node *x = new node();
        x->value = v;
        x->next = 0;


        if (tail == 0) {
            first = x;
        } else {
            tail->next = x;
        }

    }

    node *last() {

        node *prev = 0, *curr = first;
        while (curr) {
            prev = curr;
            curr = curr->next;
        }

        return prev;
    }

    void print() {

        for (node *curr = first; curr; curr = curr->next) {
            cout << curr->value << endl;
        }
    }

    void reverse() {

        node *temp, *prev = 0, *curr = first;

        while (curr) {

            temp = curr->next;
            curr->next = prev;

            prev = curr;
            curr = temp;

        }

        first = prev;

    }

};


int main(int argc, char **argv) {

    list l;

    l.add(1);
    l.add(2);
    l.add(3);

    l.print();

    l.reverse();
    l.print();

    return 0;
}
