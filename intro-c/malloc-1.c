#include <stdio.h>
#include <stdlib.h>

int main(int arc, char *argv[]) {
    void *p = malloc(4);
    int *ip = (int *)p;
    *ip = 98765;
    printf("%d\n", *ip);
    return 0;
}