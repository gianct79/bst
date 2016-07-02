#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void){

	int N, K;
	cin >> N >> K;
	priority_queue<int> C;
	for (int i = 0; i < N; ++i) {
		int t;
		cin >> t;
		C.push(t);
	}
	vector<int> T(K);
	int result = 0, i = 0;
	while (!C.empty()) {
		result += ++T[i] * C.top();
		C.pop();
		i = (i + 1) % K;    
	}
	cout << result << '\n';

	return 0;
}
