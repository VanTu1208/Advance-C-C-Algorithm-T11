#include <stdio.h>

int a = 20;
int b = 1;
int *const ptrA = &a;

int main(){
    ptrA = &b;
    printf("a = %d", *ptrA);
    return 0;

}