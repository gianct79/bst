#include <iostream>
#include <unordered_map>

using namespace std;

struct node {
    char val;
    node *next;
    node *rand;
};

ostream &operator<<(ostream &out, node* list) {
    node *curr = list;
    while (curr) {
        out << curr->val << '(' << (curr->rand ? curr->rand->val : ' ') << ") ";
        curr = curr->next;
    }
    return out;
}

/*node *clone(node *list) {
    unordered_map<node*, node*> m;
    node *curr = list;
    node *prev, *head = nullptr;
    while (curr) {
        m[curr] = new node { curr->val };
        if (!head) {
            head = m[curr];
        } else {
            prev->next = m[curr];
        }
        prev = m[curr];
        curr = curr->next;
    }

    curr = head;
    while (curr) {
        curr->rand = m[list->rand];
        curr = curr->next;
        list = list->next;
    }

    return head;
}*/

node *clone(node *list) {
	node *curr = list;
	// insert the new motherfuckers between the old ones
	while (curr) {
		curr->next = new node{ curr->val, curr->next };
		curr = curr->next->next;
	}
	curr = list;
	// adjust the fucking random pointers
	while (curr) {
		curr->next->rand = curr->rand ? curr->rand->next : nullptr;
		curr = curr->next->next;
	}
	curr = list;
	node *copy = curr->next;
	node *head = copy;
	// adjust next pointers (cleanup)
	while (curr && copy) {
		curr->next = curr->next ? curr->next->next : nullptr;
		copy->next = copy->next ? copy->next->next : nullptr;
		copy = copy->next;
		curr = curr->next;
	}
	return head;
}

int main() {
    auto e = new node {'E'};
    auto d = new node {'D', e};
    auto c = new node {'C', d};
    auto b = new node {'B', c};
    auto a = new node {'A', b};

    a->rand = d;
    b->rand = b;
    c->rand = a;
    e->rand = d;

    cout << a << '\n';
    auto m = clone(a);
	delete a; delete b; delete c; delete d; delete e;
    cout << m << '\n';

    return 0;
}
