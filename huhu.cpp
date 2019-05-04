#include <iostream>
#include <array>
#include <chrono>
#include <thread>

int main() {

    std::array<const char*, 4> anim { " \\o\\ ", " |o| ", " /o/ ", " |o| " };
    std::chrono::milliseconds ms(250);

    for (unsigned i = 0; ; ++i) {
	std::this_thread::sleep_for(ms);
        std::cout << anim[i % anim.size()] << '\r' << std::flush;
    }

    return 0;

}
