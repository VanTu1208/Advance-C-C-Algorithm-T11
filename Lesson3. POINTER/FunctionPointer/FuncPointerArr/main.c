#include <stdio.h>

int sum(int a,int b){
    printf("Ket qua: %d + %d =  %d\n", a, b, a+b);
    return (a+b);
}

int sub(int a, int b){
    printf("Ket qua: %d - %d =  %d\n", a, b, a-b);
    return (a - b);
}

int main(){
  
    int(*ptr[])(int, int) = {sum, sub};
    
    ptr[0](2, 5);
   
    ptr[1](9,7);
    
    return 0;
}