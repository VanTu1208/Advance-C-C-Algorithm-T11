#include <stdio.h>

// Hàm đệ quy tính giai thừa n! = n * (n-1) * (n-2) * ... * 1
int giaiThua(int n) { // 0xa2: 4
    if (n == 0 || n == 1) 
        return 1;
    else
        return n * giaiThua(n - 1); // Đệ quy: n! = n * (n-1)!
}




int main() {
    int n; // 0x01: 53
    printf("Input n: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Error.\n");
    } else {
        printf("%d! = %d\n",n, giaiThua(n));
    }

    return 0;
}