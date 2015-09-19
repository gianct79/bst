/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <queue>


struct customer {
    int id;
    std::string name;
    std::set<int> friends;
};


std::map<int, customer> customer_map;

void add_customer(int id, std::string const &name) {
    customer_map[id] = {id, name, {}};
}

void add_friend(int id1, int id2) {
    customer_map[id1].friends.insert(id2);
    customer_map[id2].friends.insert(id1);
}

std::string lookup_customer(int id) {
    return customer_map[id].name;
}

int get_distance(int id1, int id2) {

    std::map<int, int> d_map;
    for (auto &c : customer_map) {
        d_map[c.first] = -1;
    }

    std::queue<int> q;

    d_map[id1] = 0;
    q.push(id1);

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (auto &n : customer_map[u].friends) {
            if (d_map[n] == -1) {
                d_map[n] = d_map[u] + 1;
                q.push(n);
            }
        }

    }

    return d_map[id2];
}

int main() {
    add_customer(1, "A");
    add_customer(2, "B");
    add_customer(3, "C");
    add_customer(4, "D");
    add_customer(5, "E");
    add_customer(6, "F");
    add_customer(7, "G");

    add_friend(1, 2);
    add_friend(1, 3);
    add_friend(1, 4);
    add_friend(3, 5);
    add_friend(3, 6);
    add_friend(6, 7);

    std::cout << lookup_customer(2) << '\n';

    std::cout << get_distance(7, 7) << '\n';
    std::cout << get_distance(1, 7) << '\n';
    std::cout << get_distance(6, 7) << '\n';
    std::cout << get_distance(4, 7) << '\n';

    return 0;
}
