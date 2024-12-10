#include <stdio.h>
#include <stdarg.h>

// Hàm tính tổng nhiều số, có truyền tham số số lượng phần tử
int sumDefineCount(int count, ...)
{
    va_list args;
    /*typedef char* va_list
        Biến va_list sẽ lưu chuỗi "int count, a, b, c, d, e, f" với a,b,c được thay cho dấu ...
    */
    va_start(args, count); // So sánh từng ký tự và tách chuỗi từ "count" về trước ra khỏi chuỗi char* args, còn lại chuỗi cần theo tác "a, b, c, d, e"
    // Lúc này args = "a, b, c, d, e"

    /*Hàm va_arg(args, int)
    Mỗi lần gọi hàm sẽ tách ra một chuỗi trong mảng và trả về số được kép kiểu
    Gọi i lần sẽ tách được i số liên tiếp trong chuỗi đó
    */

    int result = 0;

    for (int i = 0; i < count; i++)
    {
        // printf("Value %d: %d\n", i,va_arg(args, int));
        result += va_arg(args, int);
    }
    va_end(args); // Sử dụng để thu hồi lại địa chỉ của biến args

    return result;
}

// Hàm có nhược điểm khi có 0 ở giữa
#define sumUnDefine(...)  sum(__VA_ARGS__,"\n")

int sum(int count1,...)
{
    va_list args1;
    va_list check;

    va_start(args1, count1);
    va_copy(check, args1);

    int result1 = count1;

    while ((va_arg(check, char*)) != (char*)"\n")
    {
        result1 += va_arg(args1, int);
    }
    va_end(args1);

    return result1;
}

int main()
{
    printf("Tong khong xac dinh: %d\n", sumUnDefine(3, 4, 5, 6, 7));
    printf("Tong xac dinh: %d\n", sumDefineCount(5, 3, 4, 5, 6, 7));

    
    
    return 0;
}