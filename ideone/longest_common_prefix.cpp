#include <iostream>
#include <vector>

using namespace std;

int findMinLength(vector<string> const &A) {
    int min = A[0].size();
    for (int i = 1; i < A.size(); ++i) {
        if (A[i].size() < min)
            min = A[i].size();
    }
    return min;
}

string commonPrefix(vector<string> const &A) {
    int min = findMinLength(A);
    string res;
    for (int i = 0; i < min; ++i) {
        char curr = A[0][i];
        for (int j = 1; j < A.size(); ++j) {
            if (A[j][i] != curr)
                return res;
        }
        res.push_back(curr);
    }
    return res;
}

int main() {
    cout << commonPrefix({"apple", "ape", "april"});
    return 0;
}
