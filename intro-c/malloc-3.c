#include <stdio.h>
#include <stdlib.h>

int main(int arc, char *argv[]) {
    int *ip = (int *)malloc(sizeof(int));
    *ip = 98765;
    printf("%d\n", *ip);
    
    free(ip);
    ip = NULL;
    return 0;
}