#include <stdio.h>

int a = 15;
int *ptrA = &a;

float b = 20;
float *ptrB = &b;

float arr[] = {2,3,4,5,6,7};
float *ptrArr = arr;

int main(){
    printf("Gia tri cua A la: %d\n",*ptrA);
    printf("Gia tri cua B la: %f\n",*ptrB);
    for(int i = 0; i < 6; i++){
        printf("Gia tri cua Arr[%d] la: %f\n",i,*(ptrArr+i)); //ptrArr: 0xA0, //prtArr1: 0xA4, //PtrArr2: 0xA8 (4 byte của float)
    }
    return 0;
}