#include <stdio.h>

int main()
{
    int i = 0;
// Đặt nhãn
start:
    printf("%d ", i);
    i++;
    if (i < 5)
    {
        goto start; // Chuyển control đến nhãn "end"
    }
    
    return 0;
}
