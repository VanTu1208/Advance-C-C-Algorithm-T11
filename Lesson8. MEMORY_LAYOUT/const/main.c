#include <stdio.h>

const int a = 10;
int *ptr;
void changeConst(){
    const int b = 20;
    ptr = &b;
    *ptr = 100;
    printf("b = %d", b);
}

int main() {
    
    printf("a: %d\n", a);
    changeConst();
    
    return 0;
}