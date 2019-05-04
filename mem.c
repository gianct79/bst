#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int init_string(char *s) {
    strcpy(s, "gta");
    return 0;
}

int create_string(char **s) {
    *s = malloc(4 * sizeof(char));
    strcpy(*s, "OIE");
    return 0;
}

int main() {

    char *a = "abcde";
    //memcpy(a, "ABC", 3);

    char b[] = "abcde";//{ 'a', 'b', 'c' };
    memcpy(b, "ABC", 3);

    char *c = malloc(4 * sizeof(char));
    init_string(c);
    
    char *d;
    create_string(&d);

    char e[4] = {0};

    char *pb = b;
    char *pe = e;

    init_string(pe);

    //memcpy(q, p, 3);
    //memcpy(q, p, 3);
    
    printf("%s - %s - %s - %s - %s - %s\n", a, b, c, d, pb, pe);
    printf("0x%x - 0x%x - 0x%x - 0x%x - 0x%x - 0x%x\n", a, b, c, d, pb, pe);
    
    free(c);
    free(d);

    return 0;
}
