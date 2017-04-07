#include <iostream>
#include <stack>
#include <unordered_set>

using namespace std;

/*int Solution::isInterleave(string s1, string s2, string s3) {

    int m = s1.size(), n = s2.size();

    bool il[m+1][n+1];
    std::memset(il, 0, sizeof(il));

    if ((m+n) != s3.size())
       return false;

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            // two empty strings have an empty string as interleaving
            if (i == 0 && j == 0)
                il[i][j] = true;

            // A is empty
            else if (i == 0 && s2[j-1] == s3[j-1])
                il[i][j] = il[i][j-1];

            // B is empty
            else if (j == 0 && s1[i-1] == s3[i-1])
                il[i][j] = il[i-1][j];

            // Current character of C matches with current character of A,
            // but doesn't match with current character of B
            else if (s1[i-1] == s3[i+j-1] && s2[j-1] != s3[i+j-1])
                il[i][j] = il[i-1][j];

            // Current character of C matches with current character of B,
            // but doesn't match with current character of A
            else if (s1[i-1] != s3[i+j-1] && s2[j-1] == s3[i+j-1])
                il[i][j] = il[i][j-1];

            // Current character of C matches with that of both A and B
            else if (s1[i-1] == s3[i+j-1] && s2[j-1] == s3[i+j-1])
                il[i][j] = (il[i-1][j] || il[i][j-1]);
        }
    }
    return il[m][n];
}*/

using point = pair<int, int>;

/*namespace std {
    template <>
    struct hash<point> {
        size_t operator () (point const &f) const {
            return (std::hash<int>()(f.first) << 1) ^ std::hash<int>()(f.second);
        }
    };
}*/

bool isInterleave(string const &s1, string const &s2, string const &s3) {

    if (s1.size() + s2.size() != s3.size()) {
        return false;
    }

    stack<point> q;
    //unordered_set<point> v;
    q.push({ 0, 0 });

    while (!q.empty()) {

        auto p = q.top(); q.pop();
        cout << "DBG:" << p.first << ',' << p.second << '\n';

        // hit bottom-right, done!
        if (p.first == s1.size() && p.second == s2.size()) {
            return true;
        }
        //if (v.count(p)) { // visited?
        //    continue;
        //}
        //v.insert(p);

        auto i = p.first + p.second;

        if (s2[p.second] == s3[i]) { // right
            q.push({ p.first, p.second + 1 });
        }
        if (s1[p.first] == s3[i]) { // down
            q.push({ p.first + 1, p.second });
        }
    }
    return false;
}

int main() {

    cout << isInterleave("kQMi2G2DP4lDVycU2kraW49wnJ5oNQ5szn7tZ7aMA8sM",
        "J2qof422vinqzNsJIylQEZllxeSD",
        "Jk2qof4Q2M2vi2Gi2nDqP4zNsJlDIyVylQEcUZ2llkrxaWe49SwDnJ5oNQ5szn7tZ7aMA8sM") << '\n';

    cout << isInterleave("aab", "abc", "aaabcb") << '\n';
    cout << isInterleave("aab", "abc", "abaacb") << '\n';
    cout << isInterleave("aab", "abc", "abaabd") << '\n';
    cout << isInterleave("aab", "abc", "aaabbc") << '\n';
    cout << isInterleave("aab", "abc", "abacab") << '\n';

    return 0;
}
