#include <stdio.h>

int a = 5;
int b = 20;

int *ptrA = &a;
int const *ptrB = &b;

int main(){

    *ptrA = 10;
    printf("a = %d\n", *ptrA);

    b = 8;
    printf("b = %d\n", *ptrB);
    return 0;
}