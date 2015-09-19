/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <sstream>

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
            destroy(root_);
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

        Node *search(const T &v, Node *parent = nullptr) {
            if (parent != nullptr) {
                if (v < parent->value) {
                    return search(v, parent->left);
                } else if (v > parent->value) {
                    return search(v, parent->right);
                }
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

        size_t get_height(Node *parent = nullptr) {
            if (!parent) {
                return 0;
            } else {
                return 1 + max(get_height(parent->left), get_height(parent->right));
            }
        }

        template<typename output_type>
        void print(output_type &out, Node *n, size_t depth = 0, char connector = '+') {
            if (!n) {
                return;
            }

            print(out, n->right, depth + 1, '/');

            for (int i = depth; i--;) {
                out << "    ";
            }
            out << ' ' << connector << "--" << n->value << '\n';

            print(out, n->left, depth + 1, '\\');
        }

        bool has_subtree(Node *subtree) {

            if (!subtree) return false;

            Node *tree = search(subtree->value, root_);

            return has_subtree(tree, subtree);
        }

    private:
        bool has_subtree(Node *tree, Node *subtree) {

            if (!tree) return false;

            bool ret = (tree->value == subtree->value);

            if (ret) {
                if (subtree->left) {
                    ret = has_subtree(tree->left, subtree->left);
                }

                if (ret) {
                    if (subtree->right) {
                        ret = has_subtree(tree->right, subtree->right);
                    }
                }
            }

            return ret;
        }
    };

}


int main() {

    int n;
    string input;

    gtlib::binary_tree<int> treeA, treeB;

    cout << "enter 1st tree: ";
    getline(cin, input);

    stringstream first(input);
    first >> n;

    auto *rootA = treeA.add(n);
    while (first >> n) {
        treeA.add(n, rootA);
    }

    cout << endl;

    cout << "enter 2nd tree: ";
    getline(cin, input);

    stringstream second(input);
    second >> n;

    auto *rootB = treeB.add(n);
    while (second >> n) {
        treeB.add(n, rootB);
    }

    treeA.print(cout, rootA);
    treeB.print(cout, rootB);

    cout << "2nd tree is subtree? ";
    treeA.has_subtree(rootB) ? cout << "yes" : cout << "no";
    cout << endl;

    return 0;
}
