#include <stdio.h>

int main(int argc, char *argv[]) {
    int i = 123;
    printf("addr: %p\nvalue: %d\n", &i, i);
    return 0;
}