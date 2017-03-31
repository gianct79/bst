#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

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
        node *right = build(array + mid + 1, mid);
        return new node{v, left, right};
    }

    static void reverse(node_type *node) {
        if (!node)
            return;
        reverse(node->left);
        reverse(node->right);
        swap(node->left, node->right);
    }

    static void reverse_i(node_type *node) {
        stack<node_type*> q;
        q.push(node);
        while (!q.empty()) {
            auto tmp = q.top(); q.pop();
            if (!tmp)
                continue;
            q.push(tmp->left);
            q.push(tmp->right);
            swap(tmp->left, tmp->right);
        }
    }

    static bool is_mirror(node_type *a, node_type *b) {
        if (a == nullptr && b == nullptr)
            return true;
        if (a == nullptr || b == nullptr)
            return false;
        return (a->value == b->value && is_mirror(a->left, b->right) && is_mirror(a->right, b->left));
    }

    static bool is_sum(node_type *node) {
        if (!node || (!node->left && !node->right))
            return true;
        T sum = node->value;
        stack<node_type*> q;
        q.push(node->left);
        q.push(node->right);
        while (!q.empty()) {
            auto t = q.top(); q.pop();
            if (t) {
                sum -= t->value;
                q.push(t->left);
                q.push(t->right);
            }
        }
        return (sum == 0);
    }

    template<typename output_type>
    static void in_order(output_type &out, node_type *node) {
        if (!node)
            return;
        in_order(out, node->left);
        out << node->value << ' ';
        in_order(out, node->right);
    }

    template<typename output_type>
    static void in_order_i(output_type &out, node_type *node) {
        auto curr = node;
        stack<node_type*> q;
        do {
            for (; curr; curr = curr->left)
                q.push(curr);
            if (q.empty())
                break;
            curr = q.top(); q.pop();
            out << curr->value << ' ';
            curr = curr->right;
        } while (curr || !q.empty());
    }

    template<typename output_type>
    static void pre_order(output_type &out, node_type *node) {
        if (!node)
            return;
        out << node->value << ' ';
        pre_order(out, node->left);
        pre_order(out, node->right);
    }

    template<typename output_type>
    static void pre_order_i(output_type &out, node_type *node) {
        stack<node_type*> q;
        q.push(node);
        while (!q.empty()) {
            auto curr = q.top(); q.pop();
            out << curr->value << ' ';
            if (curr->right)
                q.push(curr->right);
            if (curr->left)
                q.push(curr->left);
        }
    }

    template<typename output_type>
    static void post_order(output_type &out, node_type *node) {
        if (!node)
            return;
        post_order(out, node->left);
        post_order(out, node->right);
        out << node->value << ' ';
    }

    template<typename output_type>
    static void post_order_i(output_type &out, node_type *node) {
        stack<node_type*> q;
        node_type *curr = node;
        do {
            while (curr) {
                if (curr->right) {
                    q.push(curr->right);
                }
                q.push(curr);
                curr = curr->left;
            }
            curr = q.top(); q.pop();
            if (curr->right && !q.empty() && q.top() == curr->right) {
                q.pop();
                q.push(curr);
                curr = curr->right;
            } else {
                out << curr->value;
                curr = nullptr;
            }
        } while (!q.empty());
    }

    static void diag_order_u(node_type *node, int d, map<T, vector<T>> &dd) {
        if (!node)
            return;
        dd[d].push_back(node->value);
        diag_order_u(node->left, d + 1, dd);
        diag_order_u(node->right, d, dd);
    }


    template<typename output_type>
    static void diag_order(output_type &out, node_type *node) {
        map<T, vector<T>> dd;
        diag_order_u(node, 0, dd);
        for (auto &i : dd) {
            for (auto &j : i.second) {
                cout << j << ' ';
            }
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
};


int main() {
    using int_vector = vector<int>;
    int_vector v = {1, 2, 3, 4, 5, 6, 7};

    using int_tree = binary_tree<int_vector::value_type>;

    int_tree::node_type *a = int_tree::build(&v[0], v.size());
    //int_tree::print(cout, a);
    int_tree::in_order_i(cout, a);
    cout << '\n';
    int_tree::pre_order_i(cout, a);
    cout << '\n';
    int_tree::diag_order(cout, a);
    cout << '\n';

    v = {7, 6, 5, 4, 3, 2, 1};
    int_tree::node_type *b = int_tree::build(&v[0], v.size());
    //int_tree::print(cout, b);

    //int_tree::reverse_i(root);
    //int_tree::print(cout, root);

    cout << int_tree::is_mirror(a, b) << '\n';

    v = {4, 11, 6, 26, 1, 3, 2};
    //v = {1, 3, 2};
    int_tree::node_type *s = int_tree::build(&v[0], v.size());
    cout << int_tree::is_sum(s) << '\n';
}
