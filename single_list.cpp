/*
* Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
*/

#include <iostream>

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

    list() {
        first = 0;
    }

    ~list() {
        node *curr = first;
        while (curr) {
            node *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    node *add(int v) {
        node *n = new node();
        n->value = v;

        node *last = first;
        while (last && last->next)
            last = last->next;

        if (!last)
            first = n;
        else
            last->next = n;

        return n;
    }

    void remove(int v) {
        node *prev = 0; node *curr = first;
        while (curr) {
            if (curr->value == v) {
                node *temp = curr;
                if (prev) {
                    prev->next = curr->next;
                    curr = prev->next;
                } else {
                    first = curr->next;
                    curr = first;
                }
                delete temp;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    void print() {
        for (node *curr = first; curr; curr = curr->next) {
            cout << curr->value << ',';
        }
        cout << endl;
    }
};

int main() {

    // test empty list
    {
        list l;
        l.print();
        l.remove(3);
        l.print();
    }

    // test single element list
    {
        list l;
        l.add(3);
        l.print();
        l.remove(3);
        l.print();
    }

    // test element to be removed on first pos
    {
        list l;
        l.add(3);
        l.add(1);
        l.add(2);
        l.add(5);
        l.print();
        l.remove(3);
        l.print();
    }

    // test  element to be removed on last pos
    {
        list l;
        l.add(1);
        l.add(4);
        l.add(5);
        l.add(3);
        l.print();
        l.remove(3);
        l.print();
    }

    // test element to be removed on middle pos
    {
        list l;
        l.add(8);
        l.add(3);
        l.add(1);
        l.add(2);
        l.add(3);
        l.add(5);
        l.print();
        l.remove(3);
        l.print();
    }

    // test element to be removed not found
    {
        list l;
        l.add(8);
        l.add(3);
        l.add(1);
        l.add(2);
        l.add(3);
        l.add(5);
        l.print();
        l.remove(7);
        l.print();
    }

    return 0;
}