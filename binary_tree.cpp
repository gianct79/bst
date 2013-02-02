/*
 * Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
 */

#include <iostream>

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
		destroy(root_);
	}

	Node *add(Node *parent, const T& v) {

		if (!parent) {
			parent = new Node(v, nullptr, nullptr);;
		} else if (v < parent->value) {
			parent->left = add(parent->left, v);
		} else if (v > parent->value) {
			parent->right = add(parent->right, v);
		}

		return parent;
	}

	void destroy(Node *parent) {
		if (parent) {
			destroy(parent->left);
			destroy(parent->right);

			delete parent;
		}
	}
};

}

int main() {

	gtlib::binary_tree<int> tree;

	auto *root = tree.add(nullptr, 4);

	tree.add(root, 2);
	tree.add(root, 1);
	tree.add(root, 3);
	tree.add(root, 6);
	tree.add(root, 5);
	tree.add(root, 7);

	tree.add(root, 3);

	return 0;
}
