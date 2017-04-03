#include <iostream>

using namespace std;

int min3(int x, int y, int z) {
   return std::min(std::min(x, y), z);
}

int minDistance(string const &A, string const &B) {

    auto m = A.size();
    auto n = B.size();

    // first string is empty, insert all characters from second string
    if (m == 0) {
        return n;
    }
 
    // second string is empty, remove all characters of first string
    if (n == 0) {
        return m;
    }
 
    // last characters of two strings are same: ignore last
    // characters and get count for remaining characters.
    if (A[m-1] == B[n-1]) {
        return minDistance(A.substr(0, m-1), B.substr(0, n-1));
    }
 
    // last characters are different, consider all three
    // operations on last character of first string, recursively
    // compute minimum cost for all three operations and take
    // minimum of three values.
    return 1 + min3(minDistance(A, B.substr(0, n-1)),  // insert
                    minDistance(A.substr(0, m-1), B),  // remove
                    minDistance(A.substr(0, m-1), B.substr(0, n-1)) // replace
                );  
}


int main() {
    string A = "Anshuman";
    string B = "Antihuman";

    cout << minDistance(A, B) << '\n';

    A = "";
    B = "die";

    cout << minDistance(A, B) << '\n';

    A = "foo";
    B = "bar";

    cout << minDistance(A, B) << '\n';

    return 0;
}
