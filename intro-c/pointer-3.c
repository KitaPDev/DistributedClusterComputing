#include <stdio.h>

int pass_by_value(int i) {
    i = i * 2;
    return i;
}

int main(int arc, char *argv[]) {
    int i = 123;
    printf("value of i before function call: %d\n", i);
    printf("function returns: %d\n", pass_by_value(i));
    printf("value of i after function call: %d\n", i);
}