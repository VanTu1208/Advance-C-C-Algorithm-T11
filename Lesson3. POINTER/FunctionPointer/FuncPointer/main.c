#include <stdio.h>

int sum(int Arr[], int num){
    int result = 0;
    for(int i = 0; i < num; i++){
        result += Arr[i];
    }
    return result;
}

float sub(float a, int b){
    printf("Ket qua: %f - %d =  %f\n", a, b, a-b);
    return (a - b);
}

int main(){
    int Array[] = {3,1,2,5,6};
    
    int (*ptr)(int*, int) = sum ;
    printf("Tong mang la: %d\n", ptr(Array, 5));

    float (*ptr1)(float,int) = sub;
    ptr1(9.8, 6.9);

    return 0;

}