#include <iostream>
#include <vector>
#include <unordered_set>


void find_friends(std::vector<std::string> const &friends,
    std::unordered_set<int> &visited, int i) {
    visited.insert(i);
    for (int j = i; j < friends[i].size(); ++j) {
        if (!visited.count(j) && friends[i][j] == 'Y') {
            find_friends(friends, visited, j);
        }
    }
}

int friend_circles(std::vector<std::string> const &friends) {
    int circles = 0;
    std::unordered_set<int> visited;
    for (int i = 0; i < friends.size(); ++i) {
        if (!visited.count(i)) {
            circles++;
            find_friends(friends, visited, i);
        }
    }        
    return circles;
}


int main() {
    std::vector<std::string> friends { "YYNY", "YYNN", "NNYN", "YNNY" };
    std::cout << friend_circles(friends) << '\n';

    friends = { "YYYY", "YYYY", "YYYY", "YYYY" };
    std::cout << friend_circles(friends) << '\n';

    friends = { "NNNN", "NNNN", "NNNN", "NNNN" };
    std::cout << friend_circles(friends) << '\n';

    friends = { "", "", "" };
    std::cout << friend_circles(friends) << '\n';

    friends = {};
    std::cout << friend_circles(friends) << '\n';
}
