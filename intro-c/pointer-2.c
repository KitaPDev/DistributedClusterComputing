#include <stdio.h>

int main(int arc, int* argv[]) {
    int i = 123;
    int *p_i = &i;
    printf("addr of i: %p\nvalue of i %d\n\n", &i, i);
    printf("addr of p_i: %p\nvalue at p_i: %d\n", p_i, *p_i);
    return 0;
}