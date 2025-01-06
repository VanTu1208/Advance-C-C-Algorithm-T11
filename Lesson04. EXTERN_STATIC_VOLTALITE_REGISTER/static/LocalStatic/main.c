#include <stdio.h>

void count(void){
    static int x = 2;
    printf("Tang x len 1: %d\n",x++);
}



int main(){
    
    count();
    count();
    count();
    
    return 0;
}