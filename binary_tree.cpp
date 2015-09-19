/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>

#include <stack>
#include <queue>

using namespace std;

namespace gtlib {

    template<class T>
    class binary_tree {

        struct Node {
            Node(const T &value, Node *left = nullptr, Node *right = nullptr) : value(value), left(left), right(right) {
            }

            const T value;
            Node *left;
            Node *right;
        };

        Node *root_;

    public:
        binary_tree() : root_(nullptr) {
        }

        ~binary_tree() {
            destroy_it(root_);
        }

        Node *add(const T &v, Node *parent = nullptr) {

            if (!parent) {
                parent = new Node(v);
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

        Node *add_it(const T &v, Node *parent = nullptr) {

            Node *tmp = parent;
            Node *prev = nullptr;

            while (tmp) {
                prev = tmp;
                if (v < tmp->value) {
                    tmp = tmp->left;
                } else {
                    tmp = tmp->right;
                }
            }

            tmp = new Node(v);

            if (!root_) {
                root_ = tmp;
            } else if (v < prev->value) {
                prev->left = tmp;
            } else if (v > prev->value) {
                prev->right = tmp;
            }
            return tmp;
        }

        bool search(const T &v, Node *parent = nullptr) {
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

        bool search_it(const T &v, Node *parent = nullptr) {

            stack < Node * > tovisit;
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

            stack < Node * > tovisit;
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

        size_t get_height(Node *parent = nullptr) {
            if (!parent) {
                return 0;
            } else {
                return 1 + max(get_height(parent->left), get_height(parent->right));
            }
        }

        size_t get_height_it(Node *parent = nullptr) {

            size_t height = 0;

            queue < Node * > visited;
            visited.push(parent);
            visited.push(nullptr);

            while (Node *f = visited.front()) {
                visited.pop();
                if (f->left) {
                    visited.push(f->left);
                }
                if (f->right) {
                    visited.push(f->right);
                }
                if (!visited.front()) {
                    visited.pop();
                    visited.push(nullptr);
                    height++;
                }
            }

            return height;
        }
    };

}

template<typename node_type, typename output_type>
void print_binary_tree(output_type &out, node_type *n, size_t depth = 0, char connector = '+') {
    if (!n) {
        return;
    }

    print_binary_tree(out, n->right, depth + 1, '/');

    for (int i = depth; i--;) {
        out << "    ";
    }
    out << ' ' << connector << "--" << n->value << endl;

    print_binary_tree(out, n->left, depth + 1, '\\');
}

int main() {

    gtlib::binary_tree<int> tree;

    auto *root = tree.add_it(4);

    tree.add_it(2, root);
    tree.add_it(1, root);
    tree.add_it(3, root);
    tree.add_it(6, root);
    tree.add_it(5, root);
    tree.add_it(7, root);
    print_binary_tree(cout, root);

    tree.add(10, root);
    print_binary_tree(cout, root);

    cout << tree.search_it(2, root) << endl;
    cout << tree.search(7, root) << endl;

    cout << tree.search_it(10, root) << endl;

    cout << "root height: " << tree.get_height(root) << " - " << tree.get_height_it(root) << endl;

    return 0;
}
