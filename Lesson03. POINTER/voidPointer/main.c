#include <stdio.h>

void *ptr;

int main(){
    int A = 10;
    float B = 25.4;
    char C = 'c';
    void *ptrArr[] = {&A, &B, &C};

    ptr = &A;



    printf("Dia chi cua A: %p\n",ptr);
    printf("Gia tri cua A: %d\n",*(int*)ptr);

    ptr = &B;
    printf("Dia chi cua B: %p\n",ptr);

    printf("Gia tri cua A: %f\n",*(float*)ptr);


    printf("prtArr[0] = %d\n", *(int*)ptrArr[0]);
    printf("prtArr[1] = %f\n", *(float*)ptrArr[1]);
    printf("prtArr[2] = %c\n", *(char*)ptrArr[2]);
}