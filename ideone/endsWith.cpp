#include <iostream>

using namespace std;

bool endsWith(string const &s, string const &t) {

	auto i = s.rbegin();
	auto j = t.rbegin();

	for (; (*i && *j) && (*i == *j); ++i, ++j);

	return j == t.rend();
}

int main() {

	cout << std::boolalpha << endsWith("giancarlo", "lo") << '\n';
	cout << std::boolalpha << endsWith("pass", "os") << '\n';
	
	cout << std::boolalpha << endsWith("", "os") << '\n';
	cout << std::boolalpha << endsWith("os", "") << '\n';

	cout << std::boolalpha << endsWith("", " ") << '\n';

	return 0;
}