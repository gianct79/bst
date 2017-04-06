#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxProduct3(vector<int> &A) {
    std::sort(A.begin(), A.end());
    int n = A.size();
    return std::max(A[0] * A[1] * A[n - 1],
            A[n - 1] * A[n - 2] * A[n - 3]);
}	

/*int maxProduct3(vector<int> &A) {

    int maxA = INT_MIN, maxB = INT_MIN, maxC = INT_MIN;
    int minA = INT_MAX, minB = INT_MAX;
 
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] > maxA) {
            maxC = maxB;
            maxB = maxA;
            maxA = A[i];
        } else if (A[i] > maxB) {
            maxC = maxB;
            maxB = A[i];
        } else if (A[i] > maxC) {
            maxC = A[i];
        }
 
        if (A[i] < minA) {
            minB = minA;
            minA = A[i];
        } else if(A[i] < minB) {
            minB = A[i];
        }
    }

    return std::max(minA * minB * maxA,
            maxA * maxB * maxC);
}*/

int main() {
    std::vector<int> v;
    int i;
    while (cin >> i) {
        v.push_back(i);
    }
    cout << maxProduct3(v) <<  '\n';
    return 0;
}
