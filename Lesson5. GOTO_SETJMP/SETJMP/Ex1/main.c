#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

int main(){
    int i = 2;
   printf("exception = ");
    int exception = setjmp(buf);

    if(exception < 10){
        printf("%d ",exception);
        i+= 2;
        longjmp(buf,i);
    }
    return 0;
}