/*
 * Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
 */

#include <iostream>

#include <stack>

using namespace std;

namespace gtlib {

template <class T>
class binary_tree {

	struct Node {
	    Node(const T &value, Node* left, Node* right) : value(value), left(left), right(right) {
	    }

	    const T value;
	    Node* left;
	    Node* right;
	};

	Node *root_;

public:
	binary_tree() : root_(nullptr) {
	}

	~binary_tree() {
		destroy_it(root_);
	}

	Node *add(const T& v, Node *parent = nullptr) {

		if (!parent) {
			parent = new Node(v, nullptr, nullptr);
			if (!root_) {
				root_ = parent;
			}			
		} else if (v < parent->value) {
			parent->left = add(v, parent->left);
		} else if (v > parent->value) {
			parent->right = add(v, parent->right);
		}

		return parent;
	}

	bool search(const T& v, Node *parent = nullptr) {
		if (parent == nullptr) {
			return false;
		} else if (v < parent->value) {
			return search(v, parent->left);
		} else if (v > parent->value) {
			return search(v, parent->right);
		} else {
			return true;
		}
	}

	bool search_it(const T& v, Node *parent = nullptr) {

		stack<Node*> tovisit;
		tovisit.push(parent);

		while (tovisit.size() > 0) {

			const Node *curr = tovisit.top();
			tovisit.pop();

			if (curr) {

				tovisit.push(curr->left);
				tovisit.push(curr->right);

				if (curr->value == v) {
					return true;
				}
			}
		
		}

		return false;
	}

	void destroy(Node *parent) {
		if (parent) {
			destroy(parent->left);
			destroy(parent->right);

			delete parent;
		}
	}

	void destroy_it(Node *parent) {

		stack<Node*> tovisit;
		tovisit.push(parent);

		while (tovisit.size() > 0) {

			Node *curr = tovisit.top();
			tovisit.pop();

			if (curr) {
			
				tovisit.push(curr->left);
				tovisit.push(curr->right);

				delete curr;
			}
		
		}

	}
};

}

int main() {

	gtlib::binary_tree<int> tree;

	auto *root = tree.add(4);

	tree.add(2, root);
	tree.add(1, root);
	tree.add(3, root);
	tree.add(6, root);
	tree.add(5, root);
	tree.add(7, root);

	tree.add(3, root);

	cout << tree.search_it(2, root) << endl;
	cout << tree.search(7, root) << endl;

	cout << tree.search_it(10, root) << endl;

	return 0;
}
