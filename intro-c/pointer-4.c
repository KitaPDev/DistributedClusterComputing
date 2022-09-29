#include <stdio.h>

int pass_by_ref(int *p_i) {
    *p_i = (*p_i) * 2;
    return *p_i;
}

int main(int arc, char *argv[]) {
    int i = 123;
    printf("value of i before function call: %d\n", i);
    printf("function returns: %d\n", pass_by_ref(&i));
    printf("value of i after function call: %d\n", i);
}