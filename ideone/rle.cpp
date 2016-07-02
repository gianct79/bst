#include <iostream>

void run_length_encoding(const std::string &buffer)
{
	auto read = buffer.begin();
	
	if (read != buffer.end()) {

		size_t count = 1;

		for (auto next = read + 1; next != buffer.end(); ++next) {

			if (*next != *read) {
				std::cout << count << ' ' <<  *read << ", ";
				read = next;
				count = 1;	
			} else {
				count++;
			}
		} 

		std::cout << count << ' ' << *read << '\n';
	}
}


int main() {
	std::string s;
	while (std::cin >> s) {
		run_length_encoding(s);
	}
	return 0;
}