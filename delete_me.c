#include <stdio.h>

#define MAX_LEN 10

typedef struct
{
    int a;
    int b;
} test;


int main() {
    test t = {
        .a = 10,
        .b = 20
    };
    test tests[MAX_LEN];
    test *x = &tests[0];
    
    x->a = 10;
    x->b = 20;
    printf("%d %d\n", tests[0].a,tests[0].b);
    return 0;
}