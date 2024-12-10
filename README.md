# Advance-C-Cpp-Algorithm-T11
## Bài 2: STDARG - ASSERT
### Thư viện STDARG
 > **Cung cấp các phương thức để làm việc với hàm có tham số đầu vào chưa xác định**

**Bao gồm:**
```cpp
va_list: Kiểu dữ liệu cho các đối tượng lưu danh sách có đối số biến đổi

va_start(v,l): Cần được gọi trước khi truy cập các đối số trong danh sách v, hoặc có chức năng tách phần tử đầu tiên l ra khỏi danh sách

va_arg(v,l): Truy cập lần lượt một đối số trong danh sách v và ép kiểu theo l

va_copy(d,s): copy danh sách s và gán vào danh sách d

va_end(v): Kết thúc việc sử dụng danh sách đối số biến đổi, được gọi trước khi kết thúc hàm.
```
**Ví dụ: Tính tổng danh sách đối số biến đổi**
<details><summary>Xem Code và giải thích</summary>
<p>

```cpp
#include <stdio.h>
#include <stdarg.h>

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
```
**Giải thích**

```cpp
+) va_list args1; //Tạo ra một biến args1 chứa chuỗi kỹ tự gồm các đối số của hàm.

+) a_start(args1, count1); //Tách chuỗi count1 ra khỏi args1 và bắt đầu xử lý danh s+ách

+) va_copy(check, args1); //Copy danh sách args1 vào danh sách check1

+) int result1 = count1; //Giá trị đầu của kết quả là tham số thứ nhất

+) while ((va_arg(check, char*)) != (char*)"\n") //Kiểm tra việc kết thúc chuỗi, sử dụng check để tránh việc gọi hai lần dữ liệu của args1 gây ra thiếu kết quả.

+) result += va_arg(args1, int); //Đọc lần lượt từng phần tử của danh sách và ép kiểu về số nguyên sau đó cộng dồn vào kết quả

+) va_end(args); //Thu hồi lại địa chỉ biến args và kết thúc việc xử lý

+) printf("Tong khong xac dinh: %d\n", sumUnDefine(3, 4, 5, 6, 7)); //Gọi hàm thực thi in ra kết quả
```
**Kết quả:**

```cpp
Tong khong xac dinh: 25
```

</p>
</details>

### Thư viện ASSERT
 > **Cung cấp các macro sử dụng để kiểm tra điều kiện, nếu điều kiện sai(false), dừng chương trình và báo lỗi**

> **#define NDEBUG để tắt debug**

**Ví dụ: Tính tổng danh sách đối số biến đổi**
<details><summary>Xem Code và giải thích</summary>
<p>

```cpp
#include <stdio.h>
#include <assert.h>


//Nếu b = 0 thì lỗi và dừng chương trình

float divide(int a, int b){
    assert(b != 0 && "b bang 0");
    return (double)a/b;
}


int main(){
    printf("a = ");
    int a, b;
    scanf("%d", &a);
   
    printf("\nb = ");
    scanf("%d", &b);

    printf("\n%d/%d = %f\n",a,b,divide(a,b));
}
```
**Giải thích**

```cpp
+) assert(b != 0 && "b bang 0"); // Kiểm tra điều kiện nếu b khác 0 (false) thì dừng chương trình và in ra
"b bang 0"
```
**Kết quả:**
```cpp
a = 5  
b = 0  
Assertion failed: b != 0 && "b bang 0", file main.c, line 8
```
</p>
</details>


