#include <stdio.h>

int main(void) {

    int x = 0x78563412;
    printf("x = 0x%x\n", x);

    int y = (x >> 24) | ((x & 0xff0000) >> 8) | ((x & 0xff00) << 8) | (x << 24);
    printf("y = 0x%x\n", y);

    return 0;
}
