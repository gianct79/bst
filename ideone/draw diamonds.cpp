#include <iostream>

void draw_line(int space, int star) {
    while (space-- > 0)
        std::cout << ' ';
    while (star-- > 0)
        std::cout << '*';
    std::cout << '\n';
}

int main()
{
    int lines;
    std::cin >> lines;

    int star = 1;
    int space = lines - star;

    for (; space > 0; --space, star += 2)
        draw_line(space, star);

    for (; lines-- > 0; ++space, star -= 2)
        draw_line(space, star);

    return 0;
}