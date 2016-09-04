#include <iostream>
#include <functional>

std::string oak(int f, double g, bool h) {
	std::cout << f << ' ' << g << ' ' << h << '\n';
	return "oi";
}

std::string call_with_tuple(
	std::function<std::string(int, double, bool)> callable, 
	std::tuple<int, double, bool> args) {

	return callable(std::get<0>(args), std::get<1>(args), std::get<2>(args));		
}


int main() {

	std::tuple<int, double, bool> t(10, 9.2, true);

	std::cout << call_with_tuple(oak, t) << '\n';

	return 0;
}
