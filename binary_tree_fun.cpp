/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>


template<typename T>
struct binary_tree {

    struct node {
        node(T &v, node *l, node *r) : value(v), left(l), right(r) { }

        T value;
        node *left;
        node *right;
    };

    using node_type = node;

    static node *build(T *array, size_t length) {

        if (length == 0)
            return nullptr;

        auto mid = length / 2;
        T v = array[mid];

        node *left = build(array, mid);
        node *right = build(array + mid + 1, (length & 0x1) ? mid : mid - 1);

        return new node{v, left, right};
    }

    static node *build(T v, node_type *root) {
        if (root == nullptr)
            root = new node{v, nullptr, nullptr};
        else if (v < root->value)
            root->left = build(v, root->left);
        else if (v > root->value)
            root->right = build(v, root->right);
        return root;
    }

    static void reverse(node_type *node) {

        if (!node)
            return;

        reverse(node->left);
        reverse(node->right);

        std::swap(node->left, node->right);
    }

    static void reverse_i(node_type *node) {

        std::stack < node_type * > q;
        q.push(node);

        while (!q.empty()) {
            auto tmp = q.top();
            q.pop();

            if (!tmp)
                continue;

            q.push(tmp->left);
            q.push(tmp->right);

            std::swap(tmp->left, tmp->right);
        }
    }

    template<typename output_type>
    static void print(output_type &out, node_type *root, size_t depth = 0, char connector = '+') {

        if (!root)
            return;

        print(out, root->right, depth + 1, '/');

        for (int i = depth; i--;)
            out << "    ";
        out << ' ' << connector << "--" << root->value << '\n';

        print(out, root->left, depth + 1, '\\');
    }

    template<typename output_type>
    static void serialize(output_type &out, node_type *root, T const &term_value) {

        if (!root) {
            out.write(reinterpret_cast<char const *>(&term_value), sizeof(T));
        } else {
            out.write(reinterpret_cast<char *>(&root->value), sizeof(T));
            serialize(out, root->left, term_value);
            serialize(out, root->right, term_value);
        }
    }

    template<typename input_type>
    static node *deserialize(input_type &in, node_type *root, T const &term_value) {

        if (!in)
            return nullptr;

        T v;
        in.read(reinterpret_cast<char *>(&v), sizeof(T));

        if (v == term_value)
            return nullptr;

        root = new node{v, nullptr, nullptr};
        root->left = deserialize(in, root->left, term_value);
        root->right = deserialize(in, root->right, term_value);

        return root;
    }
};


int main() {
    using a_vector= std::vector<int>;
    a_vector v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    using a_tree = binary_tree<a_vector::value_type>;
    auto root = a_tree::build(&v[0], v.size());

    a_tree::print(std::cout, root);

    std::cout << '\n';

    a_tree::reverse_i(root);
    a_tree::print(std::cout, root);

    {
        std::fstream f("test.bin", std::ios::out | std::ios::binary);
        a_tree::serialize(f, root, 0);
    }

    {
        std::fstream f("test.bin", std::ios::in | std::ios::binary);
        root = a_tree::deserialize(f, nullptr, 0);
    }

    a_tree::print(std::cout, root);
}
