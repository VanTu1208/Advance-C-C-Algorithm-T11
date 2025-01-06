#include "print1.h"

void print(char* text) {
    printf("%s", text); // Sử dụng %s để đảm bảo an toàn
}

void println(char* text) {
    printf("%s\n", text); // Sử dụng %s để in chuỗi
}
void println_Int(int text) {
    printf("%d\n", text); // Sử dụng %s để in chuỗi
}