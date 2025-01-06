#include <stdio.h>


void swapINCORRECT(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;

}

void swapCORRECT(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a = 10;
    int b = 30;
    swapINCORRECT(a, b);
    printf("a = %d\n",a);
    printf("b = %d\n",b);
    
    swapCORRECT(&a, &b);
    printf("a = %d\n",a);
    printf("b = %d\n",b);

    return 0;
}