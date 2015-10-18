#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>


void find_friends(std::vector<std::string> const &friends,
    std::unordered_set<int> &visited, int i)
{
    visited.insert(i);
    for (int j = 0; j < friends[i].size(); ++j) {
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

int friend_circles_it(std::vector<std::string> const &friends) {
    int circles = 0;
    std::unordered_set<int> visited;
    std::stack<int> to_visit;
    for (int i = 0; i < friends.size(); ++i) {
        if (!visited.count(i)) {
            circles++;
            to_visit.push(i);
            while (!to_visit.empty()) {
                int v = to_visit.top();
                to_visit.pop();
                visited.insert(v);
                for (int j = 0; j < friends[v].size(); ++j) {
                    if (!visited.count(j) && friends[v][j] == 'Y')
                        to_visit.push(j);
                }
            }
        }
    }
    return circles;
}

#define TEST(Expected, ...) \
  friends = { __VA_ARGS__ }; \
  result = friend_circles_it(friends); \
  std::cout << "expected: " << Expected << ", actual: " << result << " - " << (Expected == result ? "correct" : "WRONG") << std::endl

int main() {
    std::vector<std::string> friends;
    int result;

    TEST(2, "YYNY", "YYNN", "NNYN", "YNNY");
    TEST(1, "YYYY", "YYYY", "YYYY", "YYYY");
    TEST(0);
	TEST(1, "Y");
    TEST(2,
      "YYNY",
      "YYNN",
      "NNYN",
      "YNNY"
    );
	TEST(2,
	  "YNYNNY",
	  "NYYNNN",
	  "YYYNNY",
	  "NNNYYN",
	  "NNNYYN",
	  "YNYNNY",
	);
	TEST(3,
	  "YNYNNY",
	  "NYNNNN",
	  "YNYNNY",
	  "NNNYYN",
	  "NNNYYN",
	  "YNYNNY",
	);
	TEST(6,
	  "YNNNNN",
	  "NYNNNN",
	  "NNYNNN",
	  "NNNYNN",
	  "NNNNYN",
	  "NNNNNY",
	);

    return 0;
}
