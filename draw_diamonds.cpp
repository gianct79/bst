/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>

void drawLine(int spaces, int stars) {
    for (; spaces > 0; spaces--)
        std::cout << ' ';
    for (; stars > 0; stars--)
        std::cout << '*';
    std::cout << '\n';
}

void drawShape(int const &lines) {
    if (lines < 1)
        return;

    int spaces = lines - 1;
    int stars = 1;
    for (; spaces > 0; spaces--, stars += 2)
        drawLine(spaces, stars);
    for (; spaces < lines; spaces++, stars -= 2)
        drawLine(spaces, stars);
}

int main() {
    int lines;
    while (std::cin >> lines)
        drawShape(lines);

    return 0;
}
