# Advance-C-Cpp-Algorithm-T11
## Bài 2: STDARG - ASSERT
<details><summary>Xem</summary>
 
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

</details>

## Bài 3: POINTER
<details><summary>Xem</summary>
 
**Pointer** là một biến chứa địa chỉ của một đổi tượng khác (biến, mảng, hàm), giúp chúng ta xử lý các thao tác trên bộ nhớ linh hoạt hơn.

**Ví dụ:**  
Biến bình thường: ```int A = 5```;
- Có Address giả sử ```0xA1```;
- Giá trị 5
Thì biến con trỏ ```int *ptrA = &A```; 
- Có Address giả sử ```0x42```;
- Có giá trị là địa chỉ của biến A: ```0xA1```
Cách giải tham chiếu để lấy ra giá trị của A từ ptrA  
Ta có:
- ```ptrA = 0xA1```
- ```&ptrA = 0x42``` (lấy địa chỉ của con trỏ)
- ```*prtA = *(0xA1) = 5``` (giải tham chiếu)
Vì thế nếu 
```
int *ptr = &X; //ptr trỏ đến địa chỉ của x 
int y = *ptr; // y = giá trị tại địa chỉ ptr trỏ tới
```
Thì ```y = x```  

**Kích thước của con trỏ** phụ thuộc vào **kiến trúc máy tính** và **trình biên dịch**. Ví dụ STM32 thì con trỏ có kích thước 32bits

Ví dụ ```int *ptrA``` và ```char *ptrB``` đều có kích thước như nhau. **Khác nhau** là khi đọc dữ liệu từ địa chỉ của con trỏ sẽ đọc số byte bằng với kiểu dữ liệu của con trỏ đó. Như y = *ptrA, y sẽ là dữ liệu 4 byte sau địa chỉ của con trỏ

**Mảng** có các phần tử với địa chỉ liền kề với nhau, cách nhau số bit phụ thuộc vào kiểu dữ liệu của mảng. Mảng mặc định sẽ trỏ đến phần tử đầu tiên.

**Ví dụ:** cho mảng 
```int A[] = {3,1,2};
int *ptrA = A; // Lúc này ptrA trỏ tới A[0] ví dụ 0x02

```
Thì ```prtA+1``` sẽ trỏ tới ```0x06```  tức trỏ tới ```A[1]``` hoặc ```prtA+2``` sẽ trỏ tới ```A[2]```

Muốn lấy giá trị ```A[2]``` tức là ```*(ptrA+2)```

### Ví dụ đọc dữ liệu của biến và mảng:
```cpp
#include <stdio.h>

int a = 15;
int *ptrA = &a;

float b = 20;
float *ptrB = &b;

float arr[] = {2,3,4,5,6,7};
float *ptrArr = arr;

int main(){
    printf("Gia tri cua A la: %d\n",*ptrA);
    printf("Gia tri cua B la: %f\n",*ptrB);
    for(int i = 0; i < 6; i++){
        printf("Gia tri cua Arr[%d] la: %f\n",i,*(ptrArr+i)); //ptrArr: 0xA0, //prtArr1: 0xA4, //PtrArr2: 0xA8 (4 byte của float)
    }
    return 0;
}

```
Kết quả:
```cpp
Gia tri cua A la: 15
Gia tri cua B la: 20.000000    
Gia tri cua Arr[0] la: 2.000000
Gia tri cua Arr[1] la: 3.000000
Gia tri cua Arr[2] la: 4.000000
Gia tri cua Arr[3] la: 5.000000
Gia tri cua Arr[4] la: 6.000000
Gia tri cua Arr[5] la: 7.000000
```
Ta có ptrA và ptrB trỏ đến địa chỉ của A và B. Nên khi giải tham chiếu sẽ được giá trị của A và B là 15 và 20.

Với mảng arr ta có ptrArr trỏ tới arr[0]. Muốn đọc các phần tử tiếp theo thì sẽ cộng số thứ tự phần tử tưởng ứng và được kết quả như trên.


Ví dụ hoán đổi hai giá trị:
```cpp
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
```
Kết quả:
```cpp
a = 10
b = 30
a = 30
b = 10
```

Ta có với hàm ```swapINCORRECT(int a, int b)``` tham số truyền vào là hai biến a và b, và trình biên dịch khi chạy hàm này sẽ tạo ra hai biến a, b với địa chỉ khác sau đó hoán đổi và thu hồi khi hoàn thành hàm, nên sau khi hàm này được thực thi thì hai biến a = 10 và b = 30 không thay đổi vị trí cho nhau, dẫn đến kết quả không chính xác

Với hàm ```swapCORRECT(int *a, int *b)``` tham số truyền vào là hai con trỏ và khi gọi hàm thực thi ```swapCORRECT(&a, &b)``` sẽ truyền vào địa chỉ của hai biến a và b nên giá trị của hai biến này có thể truy cập và thay đổi được
```cpp
    int temp = *a; // Temp = 10
    *a = *b; // giá trị của a = giá trị của b
    *b = temp; // giá trị của b = temp
```
### Các loại con trỏ
#### 1. Void Pointer
- Là biến có thể trỏ tới bất kỳ kiểu dữ liệu nào mà không cần biết kiểu dữ liệu của giá trị tại địa chỉ đó
- Cú pháp ```void *ptr;``` 
**Ví dụ:**
```cpp
#include <stdio.h>

void *ptr;

int main(){
    int A = 10;
    float B = 25.4;

    ptr = &A;

    printf("Dia chi cua A: %p\n",ptr);
    printf("Gia tri cua A: %d\n",*(int*)ptr);

    ptr = &B;
    printf("Dia chi cua B: %p\n",ptr);

    printf("Gia tri cua A: %f",*(float*)ptr);
}
```
Kết quả
```cpp
Dia chi cua A: 0000008EF87FFBAC
Gia tri cua A: 10
Dia chi cua B: 0000008EF87FFBA8
Gia tri cua A: 25.400000
```
Ta không thể đọc giá trị của A qua ptr trực tiếp vì trình biên dịch không biết ptr cần đọc bao nhiêu byte, vì thế ta phải ép kiểu con trỏ sang kiểu con trỏ số nguyên phù hợp với A```(int*)ptr```. Sau đó giải tham chiếu để được giá trị ```*(int*)ptr```. Tương tự với float B.

#### 2. Function Pointer
- Con trỏ hàm là một biến giữ địa chỉ của một hàm, nó trỏ đến vị trí bộ nhớ chứa mã máy của hàm
- Con trỏ hàm cho phép truyền một hàm như một đối số cho một hàm khác, lưu trữ địa chỉ của hàm trong một cấu trúc dữ liệu, hoặc thậm chí truyền hàm như một giá trị trả về tự một hàm khác.
- Để trỏ đến hàm, con trỏ hàm phải có cùng kiểu dữ liệu trả về và các tham số truyền vào cũng phải có cùng kiểu dữ liệu với hàm đó.
- Có hai cách để lấy địa chỉ hàm: Lấy trực tiếp tên hoặc thêm dấu ```&``` phía trước hàm
**Ví dụ:**
```cpp
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
```
- Để tạo con trỏ hàm trỏ tới hàm sub: ```float (*ptr1)(float,int) = sub;```
- Tạo con trỏ hàm trỏ tới hàm sum: ```int (*ptr)(int*, int) = sum;```. Tham số đầu tiên truyền vào là con trỏ số nguyên vì với hàm, tham số là một mảng sẽ được biến đổi thành con trỏ khi biên dịch, thành con trỏ trỏ tới địa chỉ đầu tiên của mảng.
- Sau đó gọi hàm thực thi
    - ```ptr(Array, 5);```
    - ```ptr1(9.8, 6.9);```
Kết quả:
```
Tong mang la: 17
Ket qua: 9.800000 - 6 =  3.800000
```
Kết quả của phép trừ bị sai vì khi thực thi ta truyền vào hai số kiểu float nhưng khai báo kiểu (float, int) nên sẽ tự động ép kiểu thành int nên 6.9 sẽ thành 6 và thực hiện phép trừ. 

**Ví dụ: Mảng con trỏ hàm**
```cpp
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
```
Kết quả: 
```
Ket qua: 2 + 5 =  7
Ket qua: 9 - 7 =  2
```
- ```int(*ptr[])(int, int) = {sum, sub};``` Khai báo mảng con trỏ trả về kiểu dữ liệu int, hai tham số truyền vào là int, gồm hai phần tử là địa chỉ của hai hàm sum và sub. Tức ```ptr[0]``` trỏ tới địa chỉ hàm ```sum``` và ```ptr[1]``` trỏ tới địa chỉ hàm ```sub```
- Gọi hàm thực thi 
```    
ptr[0](2, 5);
ptr[1](9,7);
```

**Ví dụ truyền con trỏ cho hàm khác**
```cpp
#include <stdio.h>

int sum(int a,int b){
    printf("Ket qua: %d + %d =  %d\n", a, b, a+b);
    return (a+b);
}

int sub(int a, int b){
    printf("Ket qua: %d - %d =  %d\n", a, b, a-b);
    return (a - b);
}

void caculate(int(*ptr)(int,int), int a,int b){
    ptr(a, b);
}


int main(){

    caculate(sum, 6, 7);
    caculate(sub, 8, 2);
    
    return 0;
}
```
Kết quả:    
```
Ket qua: 6 + 7 =  13
Ket qua: 8 - 2 =  6
```
- Hàm ```void caculate(int(*ptr)(int,int), int a,int b)``` sẽ truyền vào ba tham số gồm một con trỏ hàm và hai biến số nguyên để tính toán. Và sẽ địa chỉ hàm ứng với con trỏ được truyền vào ```ptr(a, b);```


#### 3. Pointer to Constant (Con trỏ hằng)
- Là con trỏ không thể thay đổi giá trị mà nó trỏ đến thông qua giải tham chiếu nhưng giá trị tại địa chỉ đó có thể thay đổi thông qua biến gốc
- Khai báo: ```int const *ptr;``` hoặc ```const int *ptr;``` 

**Ví dụ: Con trỏ hằng**
```cpp
#include <stdio.h>

int a = 5;
int b = 20;

int *ptrA = &a;
int const *ptrB = &b;

int main(){

    *ptrA = 10;
    printf("a = %d", *ptrA);

    *ptrB = 8;
    printf("b = %d", *ptrB);
    return 0;
}
```
- Ta có hai con trỏ ptrA và con trỏ hằng ptrB, ta chỉ có thể thay đổi giá trị của a bằng giải tham chiếu nhưng không thể thay đổi giá trị của b vì con trỏ hằng không được phép thay đổi giá trị tại địa chỉ mà nó trỏ đến
Kết quả:
```
main.c:14:11: error: assignment of read-only location '*ptrB'
   14 |     *ptrB = 8;
      |           ^
``` 
Nếu muốn thay đổi giá trị của A ta chỉ có thể thay đổi trực tiếp bằng biến theo cú pháp ```b = 8;``` thay cho ```*ptrB = 8;```
Kết quả: 
```
a = 10
b = 8
```
Con trỏ hằng vẫn có thể đổi địa chỉ trỏ đến khi muốn thay đổi.
Sử dụng con trỏ hằng khi không muốn đổi tượng của mình thay đổi giá trị (read only).

#### 4. Constant Pointer (Hằng con trỏ)
- Con trỏ chỉ trỏ đến một địa chỉ không thể thay đổi. Tức là sau khi khởi tạo sẽ không thể trỏ tới địa chỉ của con trỏ khác
- Cú pháp khai báo: ```int *const ptr = &a```
**Ví dụ:**
```cpp
#include <stdio.h>

int a = 20;
int b = 1;
int *const ptrA = &a;

int main(){
    ptrA = &b;
    printf("a = %d", *ptrA);
    return 0;

}
```
Vì  hằng con trỏ không thể thay đổi địa chỉ mà nó trỏ tới nên sẽ báo lỗi 
```
main.c:8:10: error: assignment of read-only variable 'ptrA'
    8 |     ptrA = &b;
      |          ^    
```

#### 5. NULL Pointer
- Khi khai báo con trỏ nhưng chưa sử dụng, mặc đinh cho giá trị con trỏ là NULL (0x00) để không trỏ tới địa chỉ khác. Hoặc sau khi sử dụng xong con trỏ thì gán NULL.
Cú pháp: ``` int *ptr = NULL;```

#### 6. Pointer to Pointer 
- Con trỏ cấp 1: ```*ptr = &a```
- Con trỏ cấp 2: ```**ptr1 = &ptr```
</details>

## Bài 4: Extern - Static - Volatile - Register
<details><summary>Xem</summary>

### Extern
- Extern được sử dụng để thông báo rằng một biến hoặc hàm đã được khai báo ở một nơi khác trong chương trình hoặc trong một file nguồn khác. Điều này giúp chương trình hiểu rằng biến hoặc hàm đã được định nghĩa và sẽ được sử dụng từ một vị trí khác, giúp quản lý sự liên kết giữa các phần khác nhau của chương trình hoặc giữa các file nguồn.

- Chỉ được khai báo chứ không được phép định nghĩa hay gán giá trị. Cú pháp: ```extern int A; ```

- Các hàm có thể không cần sử dụng Extern nhưng File khác vẫn có thể sử dụng được bình thường.

- Các File phải liên kết với nhau theo lệnh:   
```gcc main.c File1.c File2.c -o main```: Liên kết ba file .c và tạo ra file main.exe

Ví dụ:  
File1.h
```cpp
#ifndef FILE1_H
#define FILE1_H

#include <stdio.h>

extern int externVariable;

int add(int a, int b);

#endif
```
File1.c
```cpp
#include "File1.h"

int externVariable = 20;

int add(int a, int b){
    return a + b;
}

```
main.c
```cpp
#include <stdio.h>
#include "File1.h"

int main(){
    
    printf("Extern Variable: %d\n",externVariable); 

    int result = add(3,5);
    print("Result: %d\n", result)
    
    return 0;
}
```
Kết quả:
```
Extern Variable: 20
Result: 8
```

### Static
#### Static Global
Khi static được sử dụng với global variables ( biến toàn cục - khai báo biến bên ngoài hàm), nó hạn chế phạm vi của biến đó **chỉ trong file nguồn hiện tại**. Ví dụ file File1.c sử dụng ```static int x = 2;``` thì file main.c không thể nào truy cập được. Tượng tự đối với các Static Function.  
**Ứng dụng**: dùng để thiết kế các file thư viện, tránh việc sử dụng các hàm ở những File khác gây lỗi thư viện.

#### Static Local
Ví dụ:
```cpp
#include <stdio.h>

void count(void){
    int x = 2;
    printf("Tang x len 1: %d\n",x++);
}

int main(){
    
    count();
    count();
    count();
    
    return 0;
}
```
Tại hàm ```count()``` ta khai báo biến cục bộ ```int x = 2```, với mỗi lần gọi hàm, trình biên dịch sẽ khởi tạo cho biến x một địa chỉ trong bộ nhớ Stack và khi kêt thúc hàm sẽ thu hồi lại địa chỉ này. Sau đó lại cấp một địa chỉ mới có thể trùng địa chỉ cũ khi gọi lại hàm một lần nữa. Vì thế giá trị của x mỗi khi gọi hàm sẽ luôn bằng 2 và không tăng  
Kết quả:
```
Tang x len 1: 2
Tang x len 1: 2
Tang x len 1: 2
```
Để khắc phục lỗi này ta sẽ sử dụng biến kiểu static local.
Khi static được sử dụng với local variables (biến cục bộ - khai báo biến trong một hàm), nó giữ giá trị của biến qua các lần gọi hàm và giữ phạm vi của biến chỉ trong hàm đó.  

Thay đổi hàm ```count();```
```cpp
void count(void){
    static int x = 2;
    printf("Tang x len 1: %d\n",x++);
}
```
Ta sẽ khai báo biến x là biến static cục bộ. Khi lần đầu gọi hàm, trình biên dịch sẽ khởi tạo địa chỉ cho biến x này và sẽ luôn giữ giá trị xuyên suốt chương trình, khi kết thúc một lần gọi hàm hàm x sẽ được cộng lên 1. Với lần thứ 2 trở đi, khi gọi hàm trình biên dịch sẽ bỏ qua lệnh khai báo biến và trực tiếp thực thi lệnh ```printf``` và ```x++``` 
Kết quả:
```
Tang x len 1: 2
Tang x len 1: 3
Tang x len 1: 4
```
#### Static trong Class
Khi một thành viên của lớp được khai báo là static, nó thuộc về lớp chứ không thuộc về các đối tượng cụ thể của lớp đó. Các đối tượng của lớp sẽ chia sẻ cùng một bản sao của thành viên static, và nó có thể được truy cập mà không cần tạo đối tượng. Nó thường được sử dụng để lưu trữ dữ liệu chung của tất cả đối tượng.

### Volatile
Từ khóa volatile trong ngôn ngữ lập trình C được sử dụng để báo hiệu cho trình biên dịch rằng một biến có thể thay đổi ngẫu nhiên, ngoài sự kiểm soát của chương trình. Việc này ngăn chặn trình biên dịch tối ưu hóa hoặc xóa bỏ các thao tác trên biến đó, giữ cho các thao tác trên biến được thực hiện như đã được định nghĩa.

Nghĩa là trình biên dịch không có quyền xóa biến kiểu Volatile mặc dù biến này không thực thi bất kỳ công việc hoặc thay đổi nào.

Ví dụ: Khi một biến chứa giá trị Sensor có điều kiện không thay đổi. Với một biến bình thường, trình biên dịch sẽ xem xét và tối ưu hóa biến này làm cho sensor không thể cập nhật giá trị. Nhưng với một biến Volatile sẽ không bị trình biên dịch xóa và luôn có thể active.

### Register

Đối với một cấu trúc xử lý bình thường sẽ có luồng dữ liệu như sau:
![Luồng](https://i.imgur.com/soZieSR.png)
- Khi khai báo một biến ```int i = 5```, trình biên dịch sẽ cấp phát một địa chỉ trong RAM để chưa i. 
- Khi muốn xử lý giá trị i, ví dụ cộng lên một. RAM sẽ đẩy giá trị i đến một thanh ghi nào đó và gửi phép cộng một đến một thanh ghi khác.
- Sau đó hai thanh ghi này sẽ được truyền vào khối ALU (Arithmetic Logic Unit - Khối xử lý những phép toán logic trong vi điều khiển) để xử lý phép cộng này. 
- Sau đó kết quả sẽ được truyền lại thanh ghi và cuối cùng sẽ gán vào địa chỉ của biến i trong RAM 

Việc này sẽ mất nhiều tài nguyên khi xử lý những biến thường xuyên thay đổi giá trị.

**Hạn chế**
- Với từ khóa Register, biến được khởi tạo sẽ không có địa chỉ, sẽ làm giảm tính linh hoạt của biến. Nên không thể khai báo ở biến toàn cục (có nhiều hàm sẽ truy cập)
- Số thanh ghi trong vi điều khiển là giới hạn. Khi khai báo biến toàn cục thì sẽ luôn lưu biến tại vị trí thanh ghi đó, làm mất một ô thanh ghi. Làm giảm tính linh hoạt của thanh ghi.
Trong ngôn ngữ lập trình C, từ khóa register được sử dụng để chỉ ra ý muốn của lập trình viên rằng một biến được sử dụng thường xuyên và có thể được lưu trữ trong một thanh ghi máy tính, chứ không phải trong bộ nhớ RAM. Việc này nhằm tăng tốc độ truy cập. 

Tuy nhiên, lưu ý rằng việc sử dụng register chỉ là một đề xuất cho trình biên dịch và không đảm bảo rằng biến sẽ được lưu trữ trong thanh ghi. Trong thực tế, trình biên dịch có thể quyết định **không** tuân thủ lời đề xuất này.  
**Ví dụ:**
```cpp
#include <stdio.h>
#include <time.h>

int main() {
    // Lưu thời điểm bắt đầu
    clock_t start_time = clock();
    int i;

    // Đoạn mã của chương trình
    for (i = 0; i < 2000000; ++i) {
        // Thực hiện một số công việc bất kỳ
    }

    // Lưu thời điểm kết thúc
    clock_t end_time = clock();

    // Tính thời gian chạy bằng miligiây
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Thoi gian chay cua chuong trinh: %f giay\n", time_taken);

    return 0;
}

```
Chương trình trên với chức năng in ra màn hình thời gian thực thi hàm for đếm 2.000.0000 lần. Nó sẽ lấy thời gian trước khi thực thi và thời gian sau khi thực thi bằng hàm ```clock()``` cung cấp bởi thư viện ```time.h```. Và tính tổng số thời gian thực hiện của vòng lặp for.
Với đoạn mã trên, ta khai báo biến i theo cách cơ bản thì sẽ thực thi với thời gian lâu hơn
Kết quả:
```
Thoi gian chay cua chuong trinh: 0.006000 giay
```

Và khi ta đổi biến i thành kiểu ```register int i;``` thì thời gian được rút ngắn đáng kể
Kết quả:
```
Thoi gian chay cua chuong trinh: 0.001000 giay
```

</details>
    
## Bài 5: goto & setjmp 
<details><summary>Xem</summary>
 
### 1. goto
goto là một từ khóa trong ngôn ngữ lập trình C, cho phép chương trình nhảy đến một nhãn (label) đã được đặt trước đó **trong cùng một hàm**. 

Mặc dù nó cung cấp khả năng kiểm soát flow của chương trình, nhưng việc sử dụng goto thường được xem là không tốt vì nó có thể làm cho mã nguồn trở nên khó đọc và khó bảo trì.

Cú pháp: 
```cpp
label:
...
goto label;
```
Ví dụ:
```cpp
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

```
Ở ví dụ trên: chúng ta sẽ cho đếm i tăng dần, nếu i < 5 thì nhảy đến nhãn ```start``` và tiếp tục đếm. Nếu i >= 5 thì bỏ qua lệnh nhảy và kết thúc chương trình  
Kết quả
```
0 1 2 3 4 
```
Trong trường hợp có nhiều vòng lặp chồng lên nhau:
```cpp
while(1){
    for(){
        for(){
            if(){
                break;
            }
        break;
        }
    break;
    }
}
```
Việc thoát khỏi hàm ```while(1)``` ngoài cùng ngay lập tức cần phải có nhiều hàm ```break``` ở ```if()``` và các vòng ```for()``` Nhưng ta chỉ cần một lệnh ```goto``` là có thể thoát khỏi ```while(1) ```này:
```cpp
while(1){
    for(){
        for(){
            if(){
                goto out;
            }
        }
    }
}
out:
```

### 2. setjmp.h
- setjmp.h là một thư viện trong ngôn ngữ lập trình C, cung cấp hai hàm chính là setjmp và longjmp. Cả hai hàm này thường được sử dụng để thực hiện xử lý ngoại lệ trong C.
- Nhưng nó không phải là một cách tiêu biểu để xử lý ngoại lệ trong ngôn ngữ này.

**Ví dụ**
```cpp
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception_code;

#define TRY if ((exception_code = setjmp(buf)) == 0) 
#define CATCH(x) else if (exception_code == (x)) 
#define THROW(x) longjmp(buf, (x))


double divide(int a, int b) {
    if (b == 0) {
        THROW(1); // Mã lỗi 1 cho lỗi chia cho 0
    }
    return (double)a / b;
}

int main() {
    int a = 10;
    int b = 0;
    double result = 0.0;

    TRY {
        result = divide(a, b);
        printf("Result: %f\n", result);
    } CATCH(1) {
        printf("Error: Divide by 0!\n");
    }


    // Các xử lý khác của chương trình
    return 0;
}
```
- Biến ```jmp_buf buf;``` có chức năng lưu trạng thái hiện tại của chương trình
- Hàm ```setjmp(buf)``` khi lần đầu được gọi, mặc định sẽ bằng 0
- Hàm ```longjmp(buf,value)``` sẽ nhảy về địa chỉ được gọi ```setjmp(buf)``` và đặt hàm này thành giá trị ```value```

Ví dụ:
```cpp
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

int main(){
    int i = 2;
    printf("exception = ");
    int exception = setjmp(buf);
    printf("%d ",exception);

    if(exception < 10){
        i+= 2;
        longjmp(buf,i);
    }
    return 0;
}
```
- Khi lần đầu được gọi ```int exception = setjmp(buf)```; thì biến ```exception = 0```.
- Sau đó hàm ```longjmp(buf,i)``` sẽ được gọi nếu ```exception < 10``` nên ```longjmp``` sẽ được gọi lần lượt với i là 4,6,8 (i được khởi tạo là 2 và bắt đầu gọi với giá trị ```i+2```).
Kết quả:
```
exception = 0 4 6 8
```
**Hàm longjmp **không được** truyền vào tham số giá trị bằng 0

#### Sử dụng setjmp cho xử lý ngoại lệ
Ví dụ:
```cpp
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception_code;

#define TRY if ((exception_code = setjmp(buf)) == 0) 
#define CATCH(x) else if (exception_code == (x)) 
#define THROW(x) longjmp(buf, (x))


double divide(int a, int b) {
    if (b == 0) {
        THROW(1); // Mã lỗi 1 cho lỗi chia cho 0
    }
    return (double)a / b;
}

int main() {
    int a = 10;
    int b = 0;
    double result = 0.0;

    TRY {
        result = divide(a, b);
        printf("Result: %f\n", result);
    } CATCH(1) {
        printf("Error: Divide by 0!\n");
    }


    // Các xử lý khác của chương trình
    return 0;
}
```
Tại định nghĩa  
```cpp
#define TRY if ((exception_code = setjmp(buf)) == 0) 
```
sẽ gán giá trị của ```exception_code``` bằng với ```setjmp(buf)``` và kiểm tra điều kiện bằng 0 để thực thi khối TRY

Định nghĩa: 
```cpp
#define CATCH(x) else if (exception_code == (x)) 
```
Nếu khối TRY xảy ra lỗi thì thực thi hàm CATCH và kiểm tra điều kiện```exception_code == x``` và thực thi

Định nghĩa
```cpp
#define THROW(x) longjmp(buf, (x))
```
Khi gặp THROW chương trình sẽ ngừng thực thi khối TRY, gọi hàm longjmp(buf, (x)) và chuyển sang khối CATCH.

Hàm chia hai số
```cpp
double divide(int a, int b) {
    if (b == 0) {
        THROW(1); // Mã lỗi 1 cho lỗi chia cho 0
    }
    return (double)a / b;
}
```
Kiểm tra nếu mẫu bằng 0 thì xảy ra ngoại lệ và gọi THROW(1) để nhảy về setjmp(buf) đồng thời set exception = 1.

Tại hàm main:
```cpp
TRY {
    result = divide(a, b);
    printf("Result: %f\n", result);
} CATCH(1) {
    printf("Error: Divide by 0!\n");
}
```
Khi thực thi khối TRY mà mẫu bằng 0 thì sẽ chạy khối CATCH và in ra lỗi
Kết quả:
```
Error: Divide by 0!
```

ASSERT cũng có chức năng xử lý lỗi nhưng khi phát hiện lỗi thì ASSERT dừng chương trình và in ra lỗi trong khi đó thì TRY, CATCH vẫn tiếp tục thực thi chương trình.
</details>

## Bài 6: BitMask  
<details><summary>Xem</summary>
 
- Bitmask là một kỹ thuật sử dụng các bit để lưu trữ và thao tác với các cờ (flags) hoặc trạng thái. Có thể sử dụng bitmask để đặt, xóa và kiểm tra trạng thái của các bit cụ thể trong một từ (word).

- Bitmask thường được sử dụng để tối ưu hóa bộ nhớ, thực hiện các phép toán logic trên một cụm bit, và quản lý các trạng thái, quyền truy cập, hoặc các thuộc tính khác của một đối tượng.

### Bitwise Operatiors
![Bitwise](https://i.imgur.com/HZs7vbg.png)
#### NOT: 
- 0 thành 1, 1 thành 0
- Cú pháp: ```~b``` 
#### AND:
- Khi tất cả intput bằng 1 thì output bằng 1, ngược lại bằng 0
- Cú pháp: ```a&b```
#### OR:
- Khi có ít nhất một input bằng 1 thì output bằng 1, ngược lại bằng 0
- Cú pháp: ```a|b```
### XOR:
- Khi có một ngõ vào khác các ngõ vào còn lại thì bằng 1, ngược lại bằng 0.
- Cú pháp: ```a^b```
#### Shift Left, Shift Right
- Dùng để di chuyển bit sang trái hoặc sang phải.
    - Trong trường hợp <<, các bit ở bên phải sẽ được dịch sang trái, và các bit trái cùng sẽ được đặt giá trị 0.
    - Trong trường hợp >>, các bit ở bên trái sẽ được dịch sang phải, và các bit phải cùng sẽ được đặt giá trị 0 hoặc 1 tùy thuộc vào giá trị của bit cao nhất (bit dấu).


**Ví dụ**
```cpp
#include <stdint.h>
#include <stdio.h>

int main(){

    const uint8_t init  = 0b01001011; // 75
    const uint8_t init1 = 0b01101001; // 105
    
    uint8_t notInit = ~init; //0b10110100: 180
    printf("NOT: %d\n", notInit);
    
    uint8_t AND = init&init1; //0b01001001: 73  
    printf("AND: %d\n", AND);

    uint8_t OR = init|init1; //0b01101011: 107
    printf("OR: %d\n", OR); 

    uint8_t XOR = init^init1; //0b00100010: 34
    printf("XOR: %d\n", XOR);

    uint8_t shiftLeft = init<<3; //0b01011000: 88
    printf("ShiftLeft 3 bit Init: %d\n", shiftLeft);

    uint8_t shiftRight = init>>4 ; //0b00000100: 4
    printf("ShiftRight 4 bit Init: %d\n", shiftRight);


    return 0;
}
```
Kết quả:
```
NOT: 180
AND: 73
OR: 107
XOR: 34
ShiftLeft 3 bit Init: 88
ShiftRight 4 bit Init: 4
```
**Ví dụ sử dụng bitmask**
```cpp
#define GENDER        1 << 0  //0000 0001
#define TSHIRT        1 << 1  //0000 0010
#define HAT           1 << 2  //0000 0100
#define SHOES         1 << 3  //0000 1000

#define FEATURE1      1 << 4  // Bit 4: Tính năng 1
#define FEATURE2      1 << 5  // Bit 5: Tính năng 2
#define FEATURE3      1 << 6  // Bit 6: Tính năng 3
#define FEATURE4      1 << 7  // Bit 7: Tính năng 4
```
Thay vì khai báo mỗi đối tượng với kiểu uint8_t sẽ mất 4 bytes thì ta chỉ cần khai báo 8 đối tượng mà chỉ mất 1 byte.
- Hàm bật một bit:
```cpp
void enableFeature(uint8_t *features, uint8_t change) {
    *features |= change;
}
```
- Giả sử ta có 
```
features:    10001000
change  :    00000100
______________________
features:    10001100
```
- Như ví dụ trên, ta chỉ cần bật bit 2 và sử dụng phép OR để khi ```feature|change``` thì bit tại vị trí cần bật lên sẽ luôn bằng 1. Và những bit tại ví trị khác của ```features``` OR với bit 0 của ```change``` sẽ luôn là chính nó (Không làm thay đổi các bit khác).

- Hàm tắt một bit:
```cpp
void disableFeature(uint8_t *features, uint8_t change) {
    *features &= ~change;
}
```
- Giả sử ta có  ```change: 00000010``` thì ```~change=11111101```
Kết quả:
```
features:    10001010
change  :    11111101
______________________
features:    10001000
```
Phép AND với 1 sẽ tắt bit của features tại vị trí bit 0 của change và các vị trí khác sẽ không đổi.

- Hàm đọc giá trị một bit
```cpp
int isFeatureEnabled(uint8_t features, uint8_t change) {
    return (features & change) != 0;
}
```
Giả sử ta muốn kiểm tra bit 5
```
features:    10001010
change  :    00100000
______________________
features:    00000000
```
Ta sẽ AND biến cần kiểm tra với mặt nạ mạng có giá trị 0 ở tất cả các bit (Kết quả luôn bằng 0) ngoại trừ vị trí cần kiểm tra sẽ có bit 1, nếu bit tại đó bằng 1 thì kết quả bằng 1, ngược lại bằng 0.
Cả hai hàm bật/tắt bit trên sẽ truyền vào con trỏ để xác định được vị trí đang lưu của đổi tượng cần thay đổi bit. Nhưng với hàm đọc chúng ta chỉ cần biết giá trị chứ không cần đổi nên sẽ truyền vào tham số là một biến bình thường. Lúc này, biến sẽ được khởi tạo ở một địa chỉ khác và không thay đổi giá trị của biến gốc.

Full Code:
```cpp
#include <stdio.h>
#include <stdint.h>


#define GENDER        1 << 0  // Bit 0: Giới tính (0 = Nữ, 1 = Nam)
#define TSHIRT        1 << 1  // Bit 1: Áo thun (0 = Không, 1 = Có)
#define HAT           1 << 2  // Bit 2: Nón (0 = Không, 1 = Có)
#define SHOES         1 << 3  // Bit 3: Giày (0 = Không, 1 = Có)
// Tự thêm tính năng khác
#define FEATURE1      1 << 4  // Bit 4: Tính năng 1
#define FEATURE2      1 << 5  // Bit 5: Tính năng 2
#define FEATURE3      1 << 6  // Bit 6: Tính năng 3
#define FEATURE4      1 << 7  // Bit 7: Tính năng 4

void enableFeature(uint8_t *features, uint8_t feature) {
    *features |= feature;
}

void disableFeature(uint8_t *features, uint8_t feature) {
    *features &= ~feature;
}


int isFeatureEnabled(uint8_t features, uint8_t feature) {
    return (features & feature) != 0;
}

void listSelectedFeatures(uint8_t features) {
    printf("Selected Features:\n");

    if (isFeatureEnabled(features, GENDER)) {
        printf("- Gender\n");
    }
    if (isFeatureEnabled(features, TSHIRT)) {
        printf("- T-Shirt\n");
    }
    if (isFeatureEnabled(features, HAT)) {
        printf("- Hat\n");
    }
    if (isFeatureEnabled(features, SHOES)) {
        printf("- Shoes\n");
    }
    printf("Feature Binary:\n");
    for (int i = 7; i >= 0 ; i--)
    {
        printf("%d", (features >> i) & 1);
    }
}

int main() {
    uint8_t options = 0;

    // Thêm tính năng 
    enableFeature(&options, GENDER | TSHIRT | HAT);

    disableFeature(&options, TSHIRT);

    // Liệt kê các tính năng đã chọn
    listSelectedFeatures(options);
    
    return 0;
}

```

Kết quả:
```
Selected Features:
- Gender
- Hat
Feature Binary:
00000101
```
Tại hàm main ta bật 3 bit ```GENDER | TSHIRT | HAT``` sau đó tắt một bit ```TSHIRT```, nên sẽ chỉ còn 2 bit được bật tại vị trí 0 và 2 như ta đã khai báo ở đầu.

</details>



## Bài 7: Struct - Union
<details><summary>Xem</summary>

### Struct
- Trong ngôn ngữ lập trình C, struct là một cấu trúc dữ liệu cho phép lập trình viên tự định nghĩa một kiểu dữ liệu mới bằng cách nhóm các biến có các kiểu dữ liệu khác nhau lại với nhau. struct cho phép tạo ra một thực thể dữ liệu lớn hơn và có tổ chức hơn từ các thành viên (members) của nó.

- Cú pháp
```cpp
struct TenStruct {
    kieuDuLieu1 thanhVien1;
    kieuDuLieu2 thanhVien2;
    // ...
};

struct TenStruct Struct1, Struct2, Struct3[50];
```
Hoặc
```cpp
typedef struct TenStruct {
    kieuDuLieu1 thanhVien1;
    kieuDuLieu2 thanhVien2;
    // ...
} TenStruct;

TenStruct Struct1, Struct2, *Struct4;
```

- **Địa chỉ của Struct** là địa chỉ của **member đầu tiên**.

- Truy cập sử dụng thành phần của Struct
```cpp
Struct1.thanhvien1 = ...;
Struct1.thanhvien2 = ...;
```
- Nếu biến Struct là một con trỏ. Ví dụ ```*Struct4``` thì muốn truy cập vào phần tử phải sử dụng cú pháp:
```cpp
Struct4->thanhvien1 = ...;
Struct4->thanhvien2 = ...;
```

- **Data Alignment**: Quá trình sắp xếp các thành phần của struct, sao cho địa chỉ của những thành phần này phù hợp với yêu cầu căn chỉnh của CPU.
Ví dụ: thành phần có kiểu dữ liệu Double thì nó phải bắt đầu ở những địa chỉ chia hết cho 8 như ```0xA0```, ```0xA8```
- **Data Padding**: Những byte địa chỉ trống không chứa dữ liệu. Khi xắp xếp dữ liệu phù hợp, sẽ thừa ra nhưng byte trống ở giữa
**Ví dụ:**
```cpp
#include <stdio.h>
#include <stdint.h>

typedef struct{
    uint8_t  mem1;
    uint16_t mem2;
    uint32_t mem3;
} Container;

int main(int argc, char const *argv[])
{
    printf("Size of Container: %d\n",sizeof(Container));
    return 0;
}
```
- Ở vị dụ trên, ta sẽ có một Struct tên Container chưa ba phần tử, tổng kích thước của chúng là 7 bytes
- Nhưng kết quả:
```
Size of Container: 8
```
Thay đổi so với lý thuyết do **Data Alignment**
- Trình biên dịch sẽ dựa vào thành phần có kích thước lớn nhất để cấp phát địa chỉ. Ở đây là mem3 với 4 bytes. Vì thế mỗi lần cấp thêm địa chỉ phải cấp 4 bytes
- Đầu tiên, cấp 4 bytes để lưu trữ mem1, ví dụ:```0xA0 0xA1 0xA2 0xA3``` mem1 chỉ có một bytes nên được lưu ở ```0xA0```.
- Sau đó mem2 có 2 byte nên phải lưu ở ô nhớ chia hết cho 2 nên sẽ lưu ở địa chỉ ```0xA2 0xA3```
- Vì không còn đủ ô nhớ nên sẽ cấp phát thêm 4 bytes để lưu mem3. Vì thế sẽ mất 8 bytes để lưu được Struct này.
![Mem](https://i.imgur.com/FKj6wSu.png)

- Nếu chúng ta thay đổi vị trí của thành phần
```cpp
typedef struct{
    uint8_t  mem1;
    uint32_t mem3;
    uint16_t mem2;
} Container;
```
Thì kết quả sẽ là
```
Size of Container: 12
```
Vì địa chỉ của các thành phần được xếp như sau
![Mem1](https://i.imgur.com/JZKgJpJ.png)
Với **padding** là những vị trí địa chỉ có giá trị rỗng. 

**Ví dụ với các thành phần là mảng**
```cpp
typedef struct{
    uint8_t arr1[5];
    uint32_t arr2[4]; 
    uint16_t arr3[1]; 

} ContainerArr;
```
Vị trí ô nhớ được căn chỉnh như sau:
![can chinh](https://i.imgur.com/Ov2E0Rg.png)

- Mỗi lần cấp phát địa chỉ sẽ cấp 4 bytes theo ```arr2``` và được cấp phát 7 lần như hình.
Kết quả:
```
Size of ContainerArr: 28
```

### Union
- Trong ngôn ngữ lập trình C, union là một cấu trúc dữ liệu giúp lập trình viên kết hợp nhiều kiểu dữ liệu khác nhau vào cùng một vùng nhớ. Mục đích chính của union là tiết kiệm bộ nhớ bằng cách chia sẻ cùng một vùng nhớ cho các thành viên của nó. 
- Điều này có nghĩa là, trong một thời điểm, chỉ một thành viên của union có thể được sử dụng. Điều này được ứng dụng nhằm tiết kiệm bộ nhớ.

- Vì thế **Kích thước** của Union là kích thước của thành phần có kích thước lớn nhất.
- Cú pháp:
```cpp
union TenUnion {
    kieuDuLieu1 thanhVien1;
    kieuDuLieu2 thanhVien2;
    // ...
};
```
Hoặc
```cpp
tyupedef union  {
    kieuDuLieu1 thanhVien1;
    kieuDuLieu2 thanhVien2;
    // ...
} TenUnion;
```
**Ví dụ**
```cpp
#include <stdio.h>
#include <stdint.h>

typedef union {
    uint8_t  mem1;
    uint32_t mem3;
    uint16_t mem2;
} Container;

int main(int argc, char const *argv[])
{
    printf("Size of Container: %d\n",sizeof(Container));

    return 0;
}
```
Vì kích thước kiểu dữ liệu lớn nhất là 4 bytes nên vùng nhớ của Union sẽ là 4 bytes và sử dụng chung cho tất cả các thành phần. Kết quả:
```
Size of Container: 4
```
- Nếu union có phần từ là các mảng 
```cpp
typedef union {
    uint8_t arr1[5];
    uint32_t arr2[4]; 
    uint16_t arr3[1]; 
} Container;
```
Union cũng sẽ lấy kích thước của phần tử lớn nhất là arr2[4]: Tức sẽ là 4x4 = 16 bytes

- Một trường hợp khác:
```cpp
typedef union {
    uint8_t arr1[5];
    uint32_t arr2[4]; 
    uint16_t arr3[10]; 
} Container;
```
Ta có mảng ```arr2``` có **kích thước kiểu dữ liệu lớn** nhất là 4 bytes nhưng tổng kích thước của mảng chỉ có 16 bytes trong khi arr3 có kiểu dữ liệu nhỏ hơn là 2 bytes nhưng **tổng kích thước mảng lớn nhất** lên đến 2x10 = 20 bytes nên Union sẽ lấy vùng địa chỉ với kích thước là 20 bytes

**Ví dụ:**
```cpp
#include <stdio.h>
#include <stdint.h>

typedef union {
    uint8_t  val1;
    uint32_t val2; 
    uint16_t val3; 
} Container;

int main()
{
    Container group1;
    group1.val2 = 726832469;// 00101011 01010010 10010101 01010101;

    printf("Dia chi bien 1: %p        Gia tri bien 1: %d\n",&group1.val1 ,group1.val1);
    printf("Dia chi bien 2: %p        Gia tri bien 2: %d\n",&group1.val2 ,group1.val2);
    printf("Dia chi bien 3: %p        Gia tri bien 3: %d\n",&group1.val3 ,group1.val3);
    return 0;
}
```
Ta có ```726832469 = 00101011 01010010 10010101 01010101```
Giả sử Union lưu giá trị tại địa chỉ 0xA0. Nó sẽ lưu byte có trọng số thấp trước. Như hình bên
![memm](https://i.imgur.com/n6icjSD.png)

Vì Union sử dụng chung vùng nhớ nên khi gán biến 2 vào Union thì sẽ gán cả 4 byte vào cùng nhớ đó và các thành phần khác lưu giá trị trong vùng nhớ đó tại ô nhớ đầu tiên.
- Với ```val1``` có 1 byte dữ liệu nên sẽ đọc 1 byte từ địa chỉ đầu nên sẽ có giá trị 85
- Với ```val2``` có 4 bytes nên sẽ đọc tất cả, nên kết quả là 726832469
- ```val3``` có 2 bytes nên sẽ là 38229
Kết quả:
```
Dia chi bien 1: 0000006B557FF74C        Gia tri bien 1: 85
Dia chi bien 2: 0000006B557FF74C        Gia tri bien 2: 726832469
Dia chi bien 3: 0000006B557FF74C        Gia tri bien 3: 38229   
```

</details>


## Bài 8: Memory Layout
<details><summary>Xem</summary>
 
Chương trình main.exe (trên window) được lưu ở bộ nhớ **SSD**, main.hex (nạp vào vi điều khiển) được lưu ở **FLASH** . Khi nhấn run chương trình trên window (cấp nguồn cho vi điều khiển) thì những chương trình này sẽ được copy vào bộ nhớ  **RAM** để thực thi.

### Phân vùng bộ nhớ (5 vùng)
![5 vùng](https://i.imgur.com/vHDjQuS.png)

#### Text segment (Code Segment)
- Phân vùng có địa chỉ thấp nhất.
- Chứa mã máy: tập hợp các lệnh thực thi
- Quyền truy cập: Text Segment thường có quyền đọc và thực thi, nhưng không có quyền ghi **(Read Only)**.
- Tất cả các biến lưu ở phần vùng Text đều không thể thay đổi giá trị mà chỉ được đọc.

#### Data Segment (Initialized Data Segment - Dữ liệu đã được khởi tạo)
- Chứa các biến toàn cục được khởi tạo với giá trị khác 0.
- Chứa các biến static được khởi tạo với giá trị khác 0.
- Quyền truy cập là **đọc và ghi**, tức là có thể đọc và thay đổi giá trị của biến.
- Tất cả các biến sẽ được thu hồi sau khi chương trình kết thúc.

#### BSS Segment (Uninitialized Data Segment - Dữ liệu chưa được khởi tạo)
- Chứa các biến toàn cục khởi tạo với giá trị bằng 0 hoặc không gán giá trị.
- Chứa các biến static với giá trị khởi tạo bằng 0 hoặc không gán giá trị.
- Quyền truy cập là **đọc và ghi**, tức là có thể đọc và thay đổi giá trị của biến.
- Tất cả các biến sẽ được thu hồi sau khi chương trình kết thúc.

**Lưu ý:** Các hằng số và con trỏ kiểu char tùy thuộc vào trình biên dịch sẽ được lưu vào những phân vùng bộ nhớ khác nhau. Ví dụ:
- MinGW (gcc/g++): lưu vào data segment (kiểu **Read Only**)
- Clan: lưu vào phân vùng text
Khi khao báo
```cpp
char *str = "text"
```
Thì con trỏ str sẽ lưu vào vùng nhớ data/text và chỉ được phép đọc, không thể thay đổi giá trị. Vì thế, muốn thay đổi giá trị chuỗi, khởi tạo bằng mảng ký tự.

**Ví dụ**
```cpp
#include <stdio.h>

const int a = 10;
char arr[] = "Hello";
char *arr1 = "Hello";

int main() {
   
    printf("a: %d\n", a);

    arr[3] = 'W';
    printf("arr: %s", arr);
    
    arr1[3] = 'E';
    printf("arr1: %s", arr1);

    
    return 0;
}
```
Với ví dụ trên, ta khởi tạo hằng số nguyên a được lưu tại data với kiểu Read Only và không thể thay đổi giá trị, tương tự với con trỏ kiểu char *arr1. Nhưng mảng ký từ arr được lưu tại data (vì được khởi tạo giá trị "Hello") và có khả năng đọc ghi.
Kết quả:
```
a: 10
arr: HelWo
```
In ra được a và arr đã được thay đổi ký tự ở vị trí 3 nhưng khi thay đổi arr1 bị lỗi và kết thúc chương trình nên không in được arr1 ra màn hình.

#### Stack 
- Chứa các **biến cục bộ, tham số truyền vào** (ngoại trừ các biến Static cục bộ).
- Quyền truy cập: đọc và ghi, nghĩa là có thể đọc và thay đổi giá trị của biến trong suốt thời gian chương trình chạy.
- Sau khi **ra khỏi hàm**, sẽ thu hồi vùng nhớ.
- LIFO (Last In - First Out)

**So sánh hằng toàn cục và hằng cục bộ**: 
- Hằng toàn cục được lưu tại text hoặc rdata (chỉ đọc) nên không thể thay đổi dữ liệu
- Hằng cục bộ được lưu vào stack (đọc và ghi) nên có thể thay đổi dữ liệu nhưng không thể trực tiếp mà phải thông qua con trỏ.

Ví dụ:
```cpp
#include <stdio.h>

const int a = 10;
int *ptr;
void changeConst(){
    const int b = 20;
    ptr = &b;
    *ptr = 100;
    printf("b = %d", b);
}

int main() {
    
    printf("a: %d\n", a);
    changeConst();
    
    return 0;
}
```
Kết quả: 
```
main.c: In function 'changeConst':
main.c:7:9: warning: assignment discards 'const' qualifier from pointer target type [-Wdiscarded-qualifiers]
    7 |     ptr = &b;
      |         ^
a: 10
b = 100
```
Vì thay đổi b (một hằng số) nên sẽ phát sinh warning nhưng chương trình vẫn hoạt động bình thường.

**Lưu ý** Trong quá trình hoạt động. Nếu một mảng được khai báo nhiều phần tử gây tràn bộ nhớ hoặc không sử dụng hết số phần tử được khai báo thì sẽ gây lãng phí, thiếu linh hoạt. Vì thế, sử dụng các hàm khai báo bộ nhớ động như **malloc, calloc, realloc** trong thư viện ``` <stdlib.h>```. Ví dụ: ```malloc(10*sizeof(int))```: cấp 10 ô nhớ, mỗi ô 4 byte 
- malloc, calloc: cấp phát bộ nhớ động (lưu trong heap)
- realloc: thay đổi kích thước vùng nhớ động cho mảng được cấp phát bởi calloc hoặc malloc, giữ nguyên giá trị và vị trí ô nhớ đã được khởi tạo.

#### Heap (Cấp phát động)
- Heap được sử dụng để cấp phát bộ nhớ động trong quá trình thực thi của chương trình.
- Điều này cho phép chương trình tạo ra và giải phóng bộ nhớ theo nhu cầu, thích ứng với sự biến đổi của dữ liệu trong quá trình chạy.
- Các hàm như malloc(), calloc(), realloc(), và free() được sử dụng để cấp phát và giải phóng bộ nhớ trên heap.
- Quyền truy cập: có quyền đọc và ghi, nghĩa là có thể đọc và thay đổi giá trị của biến trong suốt thời gian chương trình chạy.
**So sánh STACK và HEAP**
- Lưu trữ:    
    - Bộ nhớ Stack được dùng để lưu trữ các biến cục bộ trong hàm, tham số truyền vào... Truy cập vào bộ nhớ này rất nhanh và được thực thi khi chương trình được biên dịch.
    - Bộ nhớ Heap được dùng để lưu trữ vùng nhớ cho những biến được cấp phát động bởi các hàm malloc - calloc - realloc (trong C).
- Quản lý:
    - Vùng nhớ Stack được quản lý bởi hệ điều hành, dữ liệu được lưu trong Stack sẽ tự động giải phóng khi hàm thực hiện xong công việc của mình.
    - Vùng nhớ Heap được quản lý bởi lập trình viên (trong C hoặc C++), dữ liệu trong Heap sẽ không bị hủy khi hàm thực hiện xong, điều đó có nghĩa bạn phải tự tay giải phóng vùng nhớ bằng câu lệnh free (trong C), và delete hoặc delete [] (trong C++), nếu không sẽ xảy ra hiện tượng rò rỉ bộ nhớ.
- Tràn
    - Bộ nhớ Stack cố định nên nếu chương trình bạn sử dụng quá nhiều bộ nhớ vượt quá khả năng lưu trữ của Stack chắc chắn sẽ xảy ra tình trạng tràn bộ nhớ Stack (Stack overflow), các trường hợp xảy ra như bạn khởi tạo quá nhiều biến cục bộ, hàm đệ quy vô hạn,...
    - Nếu bạn liên tục cấp phát vùng nhớ mà không giải phóng thì sẽ bị lỗi tràn vùng nhớ Heap (Heap overflow). Nếu bạn khởi tạo một vùng nhớ quá lớn mà vùng nhớ Heap không thể lưu trữ một lần được sẽ bị lỗi khởi tạo vùng nhớ Heap thất bại.

**Ví dụ: Sử dụng MALLOC**
```cpp
#include <stdio.h>
#include <stdlib.h>

int *arr = NULL;

int main(int argc, char const *argv[])
{
    int size = 10;

    arr = (int*)malloc(size*sizeof(int));

    for(int i = 0; i < size-3; i++){
        *(arr+i) = i + i*4;
    }
    for(int i = 0; i < size; i++){
        printf("Gia tri %d = %d\n",i , *(arr+i));
    }

    printf("\n\n\n");

    size = 15;
    arr = realloc(arr, size*sizeof(int));
    
    for(int i = 0; i < size; i++){
        printf("Gia tri %d = %d\n",i , *(arr+i));
    }

    free(arr);
    return 0;
}
```
Câu lệnh ```arr = (int*)malloc(size*sizeof(int));``` cấp phát mảng arr với số lượng phần tử size = 10, mỗi phần tử 4 byte int
Sau đó gán giá trị vào mảng và in ra 10 phần tử.

Để thay đổi kích thước mảng, sử dụng hàm ```realloc```
```
size = 15;
arr = realloc(arr, size*sizeof(int));
```
Thay đổi kích thước mảng arr thành 15 phần tử và in ra màn hình
Kết quả: 
```
Gia tri 0 = 0
Gia tri 1 = 5 
Gia tri 2 = 10
Gia tri 3 = 15
Gia tri 4 = 20
Gia tri 5 = 25
Gia tri 6 = 30
Gia tri 7 = 7798895
Gia tri 8 = 7471205
Gia tri 9 = 6815827



Gia tri 0 = 0
Gia tri 1 = 5
Gia tri 2 = 10
Gia tri 3 = 15
Gia tri 4 = 20
Gia tri 5 = 25
Gia tri 6 = 30
Gia tri 7 = 7798895
Gia tri 8 = 7471205
Gia tri 9 = 6815827
Gia tri 10 = 0
Gia tri 11 = 0
Gia tri 12 = 0
Gia tri 13 = 0
Gia tri 14 = 0
```
Cấp phát bộ nhớ động và khởi tạo giá trị cho 7 phần từ đầu, nên ba phần tử cuối sẽ có giá trị rác.Sau đó thay đổi số lượng phần tử và những phần tử chưa được gán giá trị từ trước (5 phần từ được khởi tạo sau) sẽ không có giá trị là 0 (khác với malloc là giá trị rác)

**Ví dụ: Sử dụng CALLOC**
```cpp
#include <stdio.h>
#include <stdlib.h>

int *arr = NULL;

int main(int argc, char const *argv[])
{
    int size = 10;

    arr = (int*)calloc(size,sizeof(int));

    for(int i = 0; i < size-3; i++){
        *(arr+i) = i + i*4;
    }
    for(int i = 0; i < size; i++){
        printf("Gia tri %d = %d\n",i , *(arr+i));
    }

    free(arr);
    return 0;
}
```
Kết quả:
```
Gia tri 0 = 0
Gia tri 1 = 5
Gia tri 2 = 10
Gia tri 3 = 15
Gia tri 4 = 20
Gia tri 5 = 25
Gia tri 6 = 30
Gia tri 7 = 0
Gia tri 8 = 0
Gia tri 9 = 0
```
Khác với Malloc, những giá trị không được khởi tạo là giá trị rác nhưng Calloc phải khởi tạo các giá trị bằng 0

**So sánh MALLOC và CALLOC**
- Tham số  truyền vào hàm Malloc là kích thước bộ nhớ cần cấp phát, Còn Malloc là số lượng phần tử và kích thước của mỗi phần tử
- Malloc không khởi tạo giá trị, Calloc và Realloc khởi tạo giá trị 0


</details>

## Bài 9: Stack - Queue

<details><summary>Xem</summary>  

### Stack
Stack (ngăn xếp) là một cấu trúc dữ liệu tuân theo nguyên tắc **Last In, First Out** (LIFO), nghĩa là phần tử cuối cùng được thêm vào stack sẽ là phần tử đầu tiên được lấy ra.

![sach](https://i.imgur.com/5qgqdOd.png)

Giống như khi xếp các cuốn sách vào trong thùng, quyển sách số 5 được để vào cuối cùng sẽ được lấy ra đầu tiên, còn quyển sách số 1 sẽ được lấy ra sau cùng

Các thao tác cơ bản trên stack bao gồm:

- **push** để thêm một phần tử vào đỉnh của stack
- **pop** để xóa một phần tử ở đỉnh stack.
- **top** để lấy giá trị của phần tử ở đỉnh stack.

Stack có **chỉ số bắt đầu bằng 0** tức phần tử đầu tiên được đưa vào có chỉ số 0, phần tử đưa vào cuối cùng có chỉ số **size - 1**(top). Vì thế:
- Stack đầy khi **top(max) = size - 1**
- Stack rỗng khi **top = -1**

**Ví dụ mô phỏng hoạt động của Stack**
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct {
    int* items;
    int size; 
    int top; 
} Stack;

void initialize( Stack *stack, int size) { 
    stack->items = (int*) calloc(size,sizeof(int));
    stack->size = size;
    stack->top = -1; 
}

bool is_empty( Stack stack) { // Kiểm tra Stack rỗng?
    return stack.top == -1;
}

bool is_full( Stack stack) { // Kiểm tra Stack đầy?
    return stack.top == stack.size - 1;
}

void push( Stack *stack, int value) { //Thêm phần tử vào Stack
    if (!is_full(*stack)) {
        stack->items[++stack->top] = value;
        printf("Push stack value: %d\n", value);
    } else {
        printf("Stack overflow\n");
    }
}

int pop( Stack *stack) { // Xóa 1 phần tử khỏi stack
    if (!is_empty(*stack)) {
        return stack->items[stack->top--];
    } else {
        printf("Stack underflow\n");
        return -1;
    }
}

int top( Stack stack) { // Đọc phần tử top, chỉ đọc nên không truyền vào con trỏ
    if (!is_empty(stack)) {
        return stack.items[stack.top];
    } else {
        printf("Stack is empty\n");
        return -1;
    }
}

int main() {
    Stack stack1; // Tao Stack
    initialize(&stack1, 3); //Truyen vao dia chi de cau hinh truc tiep Stack


    push(&stack1, 10);
    push(&stack1, 20);
    push(&stack1, 30);
    push(&stack1, 40);

    printf("Top element: %d\n", top(stack1));

    printf("Pop element: %d\n", pop(&stack1));
    printf("Pop element: %d\n", pop(&stack1));

    printf("Top element: %d\n", top(stack1));
    printf("Pop element: %d\n", pop(&stack1));
    printf("Pop element: %d\n", pop(&stack1));
    

    return 0;
}
```
Giải thích:
```cpp
typedef struct {
    int* items; //mảng lưu giá trị các phần tử
    int size; // số lượng phần tử tối đa của stack
    int top; // chỉ số phần tử ở đỉnh Stack
} Stack;
```
Khởi tạo Stack gồm có 3 thuộc tính: ```items``` lưu giá trị, ```size``` lưu số lượng phần tử tối đa của Stack, ```top lưu chỉ số đỉnh của Stack

```cpp
void initialize( Stack *stack, int size) { 
    stack->items = (int*) calloc(size,sizeof(int)); 
    stack->size = size;
    stack->top = -1; 
}
```
Hàm khởi tạo một Stack, đưa vào tham số con trỏ để cấu hình trực tiếp tại địa chỉ lưu Stack, cấp bộ nhớ động bằng hàm calloc để khởi tạo các phần tử của mảng là 0 và đặt giá trị top = -1 (rỗng)
```cpp
bool is_empty( Stack stack) { // Kiểm tra Stack rỗng?
    return stack.top == -1;
}

bool is_full( Stack stack) { // Kiểm tra Stack đầy?
    return stack.top == stack.size - 1;
}
```
Hai hàm kiểm tra Stack có đầy hay rỗng hay không. Nếu đầy thì ```top == size - 1```, nếu rỗng thì ```top == -1```

```cpp
void push( Stack *stack, int value) { //Thêm phần tử vào Stack
    if (!is_full(*stack)) {
        stack->items[++stack->top] = value;
        printf("Push stack value: %d\n", value);
    } else {
        printf("Stack overflow\n");
    }
}
```
Hàm thêm phần từ vào Stack **push** sẽ kiểm tra nếu Stack chưa đầy thì cộng chỉ số top lên 1 và gán giá trị vào mảng tại vị trí top, nếu Stack đầy thì báo lỗi.

```cpp
int pop( Stack *stack) { // Xóa 1 phần tử khỏi stack
    if (!is_empty(*stack)) {
        return stack->items[stack->top--];
    } else {
        printf("Stack underflow\n");
        return -1;
    }
}
```
Hàm đọc và xóa phần từ **pop** kiểm tra nếu Stack không rỗng thì đọc giá trị và giảm chỉ số của top xuống 1, nếu stack rỗng thì báo lỗi và trả về -1.


```cpp
int top( Stack stack) { // Đọc phần tử top, chỉ đọc nên không truyền vào con trỏ
    if (!is_empty(stack)) {
        return stack.items[stack.top];
    } else {
        printf("Stack is empty\n");
        return -1;
    }
}
```
Hàm đọc giá trị top (không xóa) **top** tương tự với hàm **push** nhưng không giảm chỉ số của top.

```cpp
int main() {
    Stack stack1; // Tao Stack
    initialize(&stack1, 3); //Truyen vao dia chi de cau hinh truc tiep Stack


    push(&stack1, 10);
    push(&stack1, 20);
    push(&stack1, 30);
    push(&stack1, 40);

    printf("Top element: %d\n", top(stack1));  // [1[]

    printf("Pop element: %d\n", pop(&stack1)); // [2]
    printf("Pop element: %d\n", pop(&stack1)); // [3]

    printf("Top element: %d\n", top(stack1));  // [4]
    printf("Pop element: %d\n", pop(&stack1)); // [5]
    printf("Pop element: %d\n", pop(&stack1)); // [6]
    

    return 0;
}
```
Với hàm main() sẽ kiểm tra tính đúng đắn trong cách hoạt động của Stack.
- Khởi tạo ```stack1``` có 3 phần tử. 
- Sau đó thêm vào 4 phần tử ở top, tức sẽ có 1 phần tử bị lỗi là giá trị 40. Nên Stack chỉ chứa 30 20 và 10
- Sau đó đọc nhưng không xóa top, được giá trị 30 **[1]**
- Đọc và xóa liên tiếp 2 lần: 30 và 20 (Stack còn lại 10) **[2]** **[3]**
- Đọc nhưng không xóa giá trị 10 **[4]**
- Đọc và xóa giá trị 10 (stack1 rỗng) **[5]**
- Đọc và xóa -> Lỗi stack1 rỗng (trả về -1) **[6]**

Kết quả đúng với lý thuyết:
```
Push stack value: 10
Push stack value: 20
Push stack value: 30
Stack overflow
Top element: 30
Pop element: 30
Pop element: 20
Top element: 10
Pop element: 10
Stack underflow
Pop element: -1
```

**Ứng dụng Stack vào đệ quy**
```cpp
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

```
Kết quả
```
Input n: 5
5! = 120
```
Với hàm ```giaiThua(int n)``` sẽ tính giai thừa của n ví dụ 5! = 120. Hàm này khi hoạt động sẽ gọi lại chính nó (gọi là đệ quy). 

Các bước khi tính n!:
- Lưu địa chỉ của n vào Stack trước khi tính giaiThua(n - 1)
- Sau đó khi thực thi giaiThua(n - 1) sẽ tiếp tục lưu giaiThua(n - 1) vào Stack bây giờ trong hàm được xem là n.
- Lặp lại đến khi ```(n == 0 || n == 1)``` và trả về 1.
- Sau đó sẽ gọi tất cả các giá trị trong Stack ra để nhân và tính giai thừa (1x1x2x3x4x5 = 120)


### Queue

Queue là một cấu trúc dữ liệu tuân theo nguyên tắc "First In, First Out" (FIFO), nghĩa là phần tử đầu tiên được thêm vào hàng đợi sẽ là phần tử đầu tiên được lấy ra.   
Các thao tác cơ bản trên hàng đợi bao gồm:
- **enqueue** thêm phần tử vào cuối hàng đợi.
- **dequeue** lấy phần tử từ đầu hàng đợi.  
- **front** để lấy giá trị của phần tử đứng đầu hàng đợi.
- **rear** để lấy giá trị của phần tử đứng cuối hàng đợi.
- **isFull** và **isEmpty** kiểm tra hàng đợi đầy hoặc rỗng.

Các loại hàng đợi: Linear Queue (hàng đợi tuyến tính), Circle Queue (Hàng đợi tròn), Priority Queue,...

#### Linear Queue (Hàng đợi tuyến tính)
Tính chất:
- Khi khởi tạo: cả front và rear đều bằng -1 (rỗng)
- Enqueue -> rear++
- Dequeue -> front++
- rear == -1 || front == -1 thì Queue rỗng
- rear == size - 1 thì Queue đầy
**Nhược điểm**: Nếu rear == size - 1 thì queue sẽ được coi là đầy dù cho phía trước vẫn còn khoảng trống vì các phần tử bị Dequeue, không thể thêm phần tử mới.
Chỉ có thể thêm phần tử mới khi đã Dequeue toàn bộ phần tử hiện có, tức là hàng đợi rỗng hoàn toàn và front được reset về vị trí ban đầu front = -1

Ví dụ:
```cpp
typedef struct Queue {
    int* items;
    int size;
    int front;
    int rear;
} Queue;
```
Tạo hàng đợi với 4 thuộc tính được giải thích ở truyền
```cpp
void initialize(Queue *queue, int size) 
{
    queue->items = (int*) calloc(size,sizeof(int));
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
}
```
Khởi tạo hàng đợi với front = rear = -1 và cấp bộ nhớ động cho mảng chứa giá trị của hàng đợi và khởi tạo về 0.
```cpp
int is_empty(Queue queue) {
    return (queue.front == -1 || queue.rear == -1);
}

int is_full(Queue queue) {
    return queue.rear == queue.size - 1;
}
```
Hai hàm để kiểm tra hàng đợi rỗng khi  ```(queue.front == -1 || queue.rear == -1)``` và hàng đợi đầy khi ```queue.rear == queue.size - 1``` không quan tâm đến front.

```cpp
void enqueue(Queue *queue, int value) {
    if (!is_full(*queue)) {
        if (is_empty(*queue)) {
            queue->front = queue->rear = 0;
        } else {
            queue->rear++   ;
        }
        queue->items[queue->rear] = value;
        printf("Enqueue element %d\n",value);
    } else {
        printf("Can't Enqueue. Queue overflow\n");
    }
}
```
Hàm thêm phần tử vào cuối hàng đợi. Nếu hàng đợi không đầy thì kiểm tra hàng đợi có rỗng hay không để đặt ```queue->front = queue->rear = 0```, nếu không rỗng thì tăng rear lên 1 và gán giá trị vào vị trí rear
```cpp
int dequeue(Queue *queue) {
    if (!is_empty(*queue)) {
        int dequeued_value = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        } else {
            queue->front++;
        }
        return dequeued_value;
    } else {
        printf("Can't Dequeue. Queue underflow\n");
        return -1;
    }
}
```
Hàm xóa phần từ đầu hàng đợi, kiểm tra hàng đợi có rỗng hãy không sau đó kiểm tra ```queue->front == queue->rear``` để xem hàng đợi có phải còn 1 phần tử hay không để sau khi xóa thì hàng đợi rỗng, nếu hàng đợi còn lớn hơn 1 phần tử thì tăng front.

```cpp
int front(Queue queue) {
    if (!is_empty(queue)) {
        return queue.items[queue.front];
    } else {
        printf("Queue is empty\n");
        return -1;
    }
}


int rear(Queue queue) {
    if (!is_empty(queue)) {
        return queue.items[queue.rear];
    } else {
        printf("Queue is empty\n");
        return -1;
    }
}

``` 
Hai hàm đọc giá trị tại front và rear

```cpp
void displayQueue(Queue queue){
    if(is_empty(queue)){
        printf("Queue is empty\n");
    } else {
        printf("------Queue: ");
        for(int i = queue.front; i <= queue.rear; i++){
            printf(" %d", queue.items[i]);
        }
        printf("\n");
    }
}
```
Hàm in ra toàn bộ giá trị của hàng đợi, ta luôn có **front <= real** 

Hàm main() để kiểm tra cách thức hoạt động
```cpp
int main() {
    Queue queue;
    initialize(&queue, 3);

    enqueue(&queue, 10); displayQueue(queue);
    enqueue(&queue, 20); displayQueue(queue);
    enqueue(&queue, 30); displayQueue(queue);
    enqueue(&queue, 40); displayQueue(queue);

    printf("Front element: %d\n", front(queue));

    printf("Dequeue element: %d\n", dequeue(&queue)); displayQueue(queue);
    printf("Rear element: %d\n", rear(queue));
    printf("Dequeue element: %d\n", dequeue(&queue)); displayQueue(queue);

    printf("Front element: %d\n", front(queue));

    enqueue(&queue, 40); displayQueue(queue);
    
    printf("Dequeue element: %d\n", dequeue(&queue)); displayQueue(queue);
    enqueue(&queue, 40); displayQueue(queue);

    return 0;
}
```
Kết quả:
```
Enqueue element 10
------Queue:  10
Enqueue element 20
------Queue:  10 20
Enqueue element 30
------Queue:  10 20 30
Can't Enqueue. Queue overflow
------Queue:  10 20 30
Front element: 10
Dequeue element: 10
------Queue:  20 30
Rear element: 30
Dequeue element: 20
------Queue:  30
Front element: 30
Can't Enqueue. Queue overflow
------Queue:  30
Dequeue element: 30
Queue is empty
Enqueue element 40
------Queue:  40
```
Sau khi thêm ba phần tử 10 20 30 thì hàng đợi đầy, không thể thêm được phần tử mới 
```
Enqueue element 10
------Queue:  10
Enqueue element 20
------Queue:  10 20
Enqueue element 30
------Queue:  10 20 30
Can't Enqueue. Queue overflow
```
Khi hàng đợi còn phần tử chưa được xóa thì không thể Enqueue 
```
------Queue:  30
Front element: 30
Can't Enqueue. Queue overflow
```
Phải xóa toàn bộ hàng đợi thì mới thêm được phần tử mới 
```
Dequeue element: 30
Queue is empty
Enqueue element 40
------Queue:  40
```


#### Circle Queue (Hàng đợi tròn)
Với Circle Queue, sẽ khác phục được nhược điểm của Linear Queue khi hàng đợi trống nhưng không thể thêm phần tử mới bằng cách đưa giá trị rear về 0 để thêm phần tử vào khoảng trống
Với Circle Queue, rear có thể nhỏ hơn front vì hàng đợi có thể xoay vòng 
```cpp
#include <stdio.h>
#include <stdlib.h>


typedef struct Queue {
    int* items;
    int size;
    int front, rear;
} Queue;

void initialize(Queue *queue, int size) 
{
    queue->items = (int*) malloc(sizeof(int)* size);
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
}

int is_empty(Queue queue) {
    return queue.front == -1;
}

int is_full(Queue queue) {
    return (queue.rear + 1) % queue.size == queue.front;
}

void enqueue(Queue *queue, int value) {
    if (!is_full(*queue)) {
        if (is_empty(*queue)) {
            queue->front = queue->rear = 0;
        } else {
            queue->rear = (queue->rear + 1) % queue->size;
        }
        printf("Enqueue element %d\n",value);
        queue->items[queue->rear] = value;
    } else {
        printf("Can't Enqueue. Queue overflow\n");
    }
}

int dequeue(Queue *queue) {
    if (!is_empty(*queue)) {
        int dequeued_value = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        } else {
            queue->front = (queue->front + 1) % queue->size;
        }
        return dequeued_value;
    } else {
        printf("Can't Dequeue. Queue underflow\n");
        return -1;
    }
}

int front(Queue queue) {
    if (!is_empty(queue)) {
        printf("Front: %d", queue.front);
        return queue.items[queue.front];
    } else {
        printf("Queue is empty");
        return -1;
    }
}

int rear(Queue queue) {
    if (!is_empty(queue)) {
        printf("Rear: %d", queue.rear);
        return queue.items[queue.rear];
    } else {
        printf("Queue is empty");
        return -1;
    }
}


int main() {
    Queue queue;
    
    int num = 3;

    initialize(&queue, num);

    printf(" -- element: %d\n", front(queue));           
    printf(" -- element: %d\n", rear(queue));

    enqueue(&queue, 10);                                    
    enqueue(&queue, 25);                                    
    enqueue(&queue, 37);  
    enqueue(&queue, 27);                                   

    printf(" -- element: %d\n", front(queue));
    printf(" -- element: %d\n", rear(queue));

    printf("Dequeue element: %d\n", dequeue(&queue));       
    printf("Dequeue element: %d\n", dequeue(&queue));       

    printf(" -- element: %d\n", front(queue));
    printf(" -- element: %d\n", rear(queue));

    enqueue(&queue, 40);                                    
    enqueue(&queue, 50);     
    enqueue(&queue, 60);                                

    printf(" -- element: %d\n", front(queue));           
    printf(" -- element: %d\n", rear(queue));

    printf("Dequeue element: %d\n", dequeue(&queue));      
    
    printf(" -- element: %d\n", front(queue));           
    printf(" -- element: %d\n", rear(queue));

    printf("Dequeue element: %d\n", dequeue(&queue));    
    printf("Dequeue element: %d\n", dequeue(&queue));    
    printf("Dequeue element: %d\n", dequeue(&queue));    
    
    return 0;
}
```
Kết quả:
```
Queue is empty -- element: -1
Queue is empty -- element: -1
Enqueue element 10
Enqueue element 25
Enqueue element 37
Can't Enqueue. Queue overflow
Front: 0 -- element: 10
Rear: 2 -- element: 37
Dequeue element: 10
Dequeue element: 25
Front: 2 -- element: 37
Rear: 2 -- element: 37
Enqueue element 40
Enqueue element 50
Can't Enqueue. Queue overflow
Front: 2 -- element: 37
Rear: 1 -- element: 50
Dequeue element: 37
Front: 0 -- element: 40
Rear: 1 -- element: 50
Dequeue element: 40
Dequeue element: 50
Can't Dequeue. Queue underflow
Dequeue element: -1
```
Giải thích trên video

</details>


## Bài 10: Linked List

<details><summary>Xem</summary> 
 
Các bước để xóa 1 phần tử trong mảng
 - Đặt giá trị NULL tại vị trí cần xóa
 - Dịch trái các phần tử phía sau vị trí đã xóa để lấp đi ô nhớ trống
 - Thu hồi những ô nhớ trống ở cuối mảng.  
 
 Vì vậy nếu mảng có nhiều phần tử sẽ phải mất nhiều lần để dịch trái các giá trị
Tương tự với thêm phần tử vào mảng, phải dịch phải các phần tử phía sau vị trí đó và thêm giá trị mới vào giữa  
Với mảng có nhiều phần tử thì việc thêm, xóa rất mất thời gian và phức tạp. Vì thế, **Linked List (Danh sách liên kết)** sẽ khắc phục vấn đề này.

**Linked list** là một cấu trúc dữ liệu trong lập trình máy tính, được sử dụng để tổ chức và lưu trữ dữ liệu. Một linked list bao gồm một chuỗi các **nút** (nodes) được lưu ở những địa chỉ rời rạc, mỗi nút chứa **một giá trị dữ liệu** và **một con trỏ (pointer) đến nút tiếp theo** trong chuỗi để liên kết chúng lại với nhau. Vì thế, node cuối cùng có con trỏ là địa chỉ NULL
![Linked List](https://i.imgur.com/7Ia2xwL.png)

Có hai loại linked list chính:
- Singly Linked List (Danh sách liên kết đơn): Mỗi nút chỉ chứa một con trỏ đến nút tiếp theo trong chuỗi.
- Doubly Linked List (Danh sách liên kết đôi): Mỗi nút chứa hai con trỏ, một trỏ đến nút tiếp theo và một trỏ đến nút trước đó.

Một linked list cung cấp một cách linh hoạt để thêm, xóa và chèn các phần tử mà không cần phải di chuyển toàn bộ dãy số như mảng. Tuy nhiên, nó cũng có một số nhược điểm, như việc cần thêm một con trỏ cho mỗi nút, tăng độ phức tạp của bộ nhớ và có thể dẫn đến hiệu suất kém hơn trong một số trường hợp so với mảng.


Các hàm Linked List  
Ở bài này, mình sẽ lập trình các hàm liên quan đến Singly linked List nên struct sẽ chỉ chứa hai thuộc tính là Data và Next
```cpp
typedef struct Node
{
    int data;          // Dữ liệu của nút
    struct Node *next; // Con trỏ đến nút tiếp theo trong danh sách, node đó cũng chứa dữ liệu và địa chỉ của con trỏ kết tiếp
} Node;
```
1. Khởi tạo List
```cpp
Node *createNode(int value) // Trả về địa chỉ node cấp phát từ hàm malloc (các địa chỉ được khởi tạo khác nhau)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node; // trả về địa chỉ
}
```
Tạo mảng động để chức một Struct của Node gồm Data và Next, khởi tạo giá trị cho node và next = NULL vì chưa liên kết với node tiếp theo. Hàm này sẽ trả về địa chỉ Node.

2. In List

```cpp
void printList(Node *head)
{
    Node *temp = head;
    int i = 0;
    while (temp != NULL)
    {
        printf("Node %d, Data = %d, Addr = %p_______nextAddr = %p\n", i, temp->data, temp, temp->next);
        temp = temp->next;
        i++;
    }
    printf("\n\n\n");
}
```
Hàm in ra danh sách các Node. Mình sẽ tạo một Struct Temp để chứa tạm giá trị của các node được duyệt qua. Sau đó sẽ duyệt và in ra giá trị của node cho đến khi node trở thành rỗng.

3. Thêm Node vào cuối list
```cpp
void push_back(Node **head, int value)
{
    Node *newNode = createNode(value);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        printf("Push back node, Data: %d\n",value);
        Node *p = *head;
        while (p->next != NULL)
            p = p->next;
        p->next = createNode(value);
    }
}
```
Tham số truyền vào là con trỏ cấp hai để có khả năng thay đổi địa chỉ cũng như giá trị Node trong List.
- Tạo một Node mới với giá trị truyền vào. 
- Kiểm tra nếu List rỗng thì Node mới sẽ được gán vào Node đầu tiên của danh sách
- Nếu không rỗng thì tạo một Node tạm ```p``` chứa giá trị các Node để khi duyệt qua các Node ```p = p->next;``` không xóa đị giá trị của List.
- Duyệt đến khi chạm đến giá trị cuối thì tạo một Node mới
4. Thêm Node mới vào đầu List
```cpp
void push_front(Node **head, int value) // Con trỏ cấp 2 cho phép thay đổi địa chỉ trỏ tới của Node, thay đổi địa chỉ của Node
{
    printf("Push front node, Data: %d\n",value);
    Node *newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
}
```
Tạo Node mới và gán newNode phía trước node đầu tiên của List, sau đó đặt newNode là node đầu của List đó
5. Thêm Node vào vị trí bất kỳ
```cpp
void insert(Node **head, int value, int position)
{
    Node *newNode = createNode(value);
    Node *temp = *head;
    int i = 0;

    while (temp->next != NULL && i != position - 1)
    {
        temp = temp->next;
        i++;
    }
    if (i == position - 1)
    {
        printf("Insert node %d, Data: %d\n",i+1,value);
        newNode->next = temp->next;
        temp->next = newNode;
    }
    else
        return;
}
```
- Tạo Node mới và tạo một Node tạm để tránh ảnh hưởng đến List khi duyệt qua các phần tử
- Kiểm tra nếu vị trí cần thêm lớn hơn số phần tử có trong danh sách thì bỏ qua.
- Nếu vị trí cần thêm nằm trong danh sách thì đặt địa chỉ Node sau cho Node mới và đặt địa chỉ Node mới cho Node trước đó.
6. Xóa Node cuối của danh sách
```cpp
void pop_back(Node **head) // Con trỏ cấp 2 cho phép thay đổi địa chỉ trỏ tới của Node, thay đổi địa chỉ của Node
{
    if (*head == NULL)
        printf("Node is not available\n");

    else
    {
        Node *temp = *head;
        Node *preTemp = temp;
        while (temp->next != NULL)
        {
            preTemp = temp;
            temp = temp->next;
        }
        printf("Pop back node\n");
        preTemp->next = NULL;
        free(temp);
    }
}
```
Kiểm tra List có rỗng hay không. Sau đó:
- Tạo Node tạm temp chứa Node hiện tại và một preNode chứa node phía trước
- Duyệt cho đến phần tử cuối cùng
- Xóa phần tử cuối cùng và đặt next của phần tử kề cuối là ```NULL``` để đặt thành BACK.
7. Xóa Node đầu danh sách
```cpp
void pop_front(Node **head) // Con trỏ cấp 2 cho phép thay đổi địa chỉ trỏ tới của Node, thay đổi địa chỉ của Node
{
    if (*head == NULL)
        printf("Node is not available\n");
    else
    {
        printf("Pop front node\n");
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
```
Kiểm tra List có rỗng hay không
- Đặt Node tạm bằng với Node đầu tiên trước khi xóa
- Chuyển Node tiếp theo thành Node đầu tiên của List
- Xóa Node tại địa chỉ temp (Node đầu cần xóa).

8. Xóa Node tại vị trí bất kỳ 
```cpp
void erase(Node **head, int position)
{
    if (*head == NULL)
        printf("Node is not available\n");

    Node *temp = *head;
    int k = 0;
    while (temp->next != NULL && k != position - 1)
    {
        k++;
        temp = temp->next;
    }

    if (k == position - 1)
    {
        printf("Erase node %d\n",k+1);
        temp->next = temp->next->next;
        free(temp->next);
    }
}
```
Kiểm tra List có rỗng hay không
- Tạo biến tạm để Duyệt
- Duyệt qua các Node cho đến khi tới Node cần Xóa
- Đặt next của Node trước Node cần xóa thành địa chỉ của Node sau Node cần xóa.
- Xóa Node.
9. Hàm đọc vị trí đầu
```cpp
void front(Node *head)
{
    if (head == NULL)
        printf("Node is not available\n");
    else
    {
        printf("Front Node: Data = %d, Addr = %p_______nextAddr = %p\n", head->data, head, head->next);
    }
}
```
Kiểm tra Head có tồn tại hay không và đọc
10. Hàm đọc vị trí cuối
```cpp
void back(Node *head)
{
    if (head == NULL)
        printf("Node is not available\n");
    else
    {
        while (head->next != NULL)
            head = head->next;
        printf("Back Node: Data = %d, Addr = %p_______nextAddr = %p\n", head->data, head, head->next);
    }
}
```
Duyệt đến vị trí cuối cùng và đọc

11. Hàm đọc vị trí bất kỳ
```cpp
void get(Node *head, int position)
{
    int i = 0;
    if (head == NULL)
        printf("Node is not available\n");
    else
    {
        while (head->next != NULL && i != position - 1)
        {
            head = head->next;
            i++;
        }
        if (i == position - 1)
        {
            printf("Print Node %d: Data = %d, Addr = %p_______nextAddr = %p\n",i, head->data, head, head->next);
        }     
    }
}
```
Duyệt đến vị trí ```position``` và đọc nếu position nằm trong danh sách

12. Hàm kiểm tra List rỗng
```
int isEmpty(Node *head)
{
    if (head == NULL){
        printf("Node is not available\n");
        return 1;
    }
    return 0;
    
}
```
13. Hàm kiểm tra kích thước mảng
```cpp
void size(Node *head)
{
    
    if (head == NULL)
        printf("Node is not available\n");
    else
    {
        int i = 0;
        while (head != NULL)
        {
            head = head->next;
            i++;
        }
        printf("Size of Linked List: %d\n",i);    
    }
}
```
**Các hàm không cần tác động đến List như chỉ đọc, kiểm tra thì tham số truyền vào là con trỏ cấp 1 để chặn khả năng làm thay đổi danh sách khi không cần thiết**

Hàm main() kiểm tra hoạt động:
```cpp
int main(int argc, char const *argv[])
{
    Node *emptyList = NULL;
    if(isEmpty(emptyList))
        printf("List 1 is empty!\n");
    
    Node *head = createNode(2);
    if(isEmpty(head))
        printf("List 2 is empty!\n");
    else {
        Node *second = createNode(4);
        Node *third = createNode(6);
        
        head->next = second;
        second->next = third;

        printList(head);

        push_front(&head, 7);  printList(head);

        push_back(&head, 10);  printList(head);

        insert(&head, 3, 3);  printList(head);

        insert(&head, 8, 1);  printList(head);

        pop_back(&head);  printList(head);

        pop_front(&head);  printList(head);

        erase(&head, 2);  printList(head);

        front(head);
        back(head);
        size(head);
    }

    return 0;
}
```

Kết quả:
```
Node is not available
List 1 is empty!
Node 0, Data = 2, Addr = 0000019B831CCFD0_______nextAddr = 0000019B831CCFF0 
Node 1, Data = 4, Addr = 0000019B831CCFF0_______nextAddr = 0000019B831CD070 
Node 2, Data = 6, Addr = 0000019B831CD070_______nextAddr = 0000000000000000 



Push front node, Data: 7
Node 0, Data = 7, Addr = 0000019B831CD090_______nextAddr = 0000019B831CCFD0 
Node 1, Data = 2, Addr = 0000019B831CCFD0_______nextAddr = 0000019B831CCFF0 
Node 2, Data = 4, Addr = 0000019B831CCFF0_______nextAddr = 0000019B831CD070 
Node 3, Data = 6, Addr = 0000019B831CD070_______nextAddr = 0000000000000000 



Push back node, Data: 10
Node 0, Data = 7, Addr = 0000019B831CD090_______nextAddr = 0000019B831CCFD0 
Node 1, Data = 2, Addr = 0000019B831CCFD0_______nextAddr = 0000019B831CCFF0 
Node 2, Data = 4, Addr = 0000019B831CCFF0_______nextAddr = 0000019B831CD070 
Node 3, Data = 6, Addr = 0000019B831CD070_______nextAddr = 0000019B831CCD90 
Node 4, Data = 10, Addr = 0000019B831CCD90_______nextAddr = 0000000000000000



Insert node 3, Data: 3
Node 0, Data = 7, Addr = 0000019B831CD090_______nextAddr = 0000019B831CCFD0 
Node 1, Data = 2, Addr = 0000019B831CCFD0_______nextAddr = 0000019B831CCFF0 
Node 2, Data = 4, Addr = 0000019B831CCFF0_______nextAddr = 0000019B831CCF70 
Node 3, Data = 3, Addr = 0000019B831CCF70_______nextAddr = 0000019B831CD070 
Node 4, Data = 6, Addr = 0000019B831CD070_______nextAddr = 0000019B831CCD90
Node 5, Data = 10, Addr = 0000019B831CCD90_______nextAddr = 0000000000000000



Insert node 1, Data: 8
Node 0, Data = 7, Addr = 0000019B831CD090_______nextAddr = 0000019B831CCDD0
Node 1, Data = 8, Addr = 0000019B831CCDD0_______nextAddr = 0000019B831CCFD0
Node 2, Data = 2, Addr = 0000019B831CCFD0_______nextAddr = 0000019B831CCFF0
Node 3, Data = 4, Addr = 0000019B831CCFF0_______nextAddr = 0000019B831CCF70
Node 4, Data = 3, Addr = 0000019B831CCF70_______nextAddr = 0000019B831CD070
Node 5, Data = 6, Addr = 0000019B831CD070_______nextAddr = 0000019B831CCD90
Node 6, Data = 10, Addr = 0000019B831CCD90_______nextAddr = 0000000000000000



Pop back node
Node 0, Data = 7, Addr = 0000019B831CD090_______nextAddr = 0000019B831CCDD0
Node 1, Data = 8, Addr = 0000019B831CCDD0_______nextAddr = 0000019B831CCFD0
Node 2, Data = 2, Addr = 0000019B831CCFD0_______nextAddr = 0000019B831CCFF0
Node 3, Data = 4, Addr = 0000019B831CCFF0_______nextAddr = 0000019B831CCF70
Node 4, Data = 3, Addr = 0000019B831CCF70_______nextAddr = 0000019B831CD070
Node 5, Data = 6, Addr = 0000019B831CD070_______nextAddr = 0000000000000000



Pop front node
Node 0, Data = 8, Addr = 0000019B831CCDD0_______nextAddr = 0000019B831CCFD0
Node 1, Data = 2, Addr = 0000019B831CCFD0_______nextAddr = 0000019B831CCFF0
Node 2, Data = 4, Addr = 0000019B831CCFF0_______nextAddr = 0000019B831CCF70
Node 3, Data = 3, Addr = 0000019B831CCF70_______nextAddr = 0000019B831CD070
Node 4, Data = 6, Addr = 0000019B831CD070_______nextAddr = 0000000000000000



Erase node 2
Node 0, Data = 8, Addr = 0000019B831CCDD0_______nextAddr = 0000019B831CCFD0
Node 1, Data = 2, Addr = 0000019B831CCFD0_______nextAddr = 0000019B831CCF70
Node 2, Data = 3, Addr = 0000019B831CCF70_______nextAddr = 0000019B831CD070
Node 3, Data = 6, Addr = 0000019B831CD070_______nextAddr = 0000000000000000



Front Node: Data = 8, Addr = 0000019B831CCDD0_______nextAddr = 0000019B831CCFD0
Back Node: Data = 6, Addr = 0000019B831CD070_______nextAddr = 0000000000000000
Size of Linked List: 4
```

</details>


## Bài 11: JSON

<details><summary>Xem</summary>  

JSON là viết tắt của "JavaScript Object Notation" (Ghi chú về Đối tượng JavaScript). Đây là một định dạng truyền tải dữ liệu phổ biến trong lập trình và giao tiếp giữa các máy chủ và trình duyệt web, cũng như giữa các hệ thống khác nhau.

JSON là một **chuỗi** được thiết kế để dễ đọc và dễ viết cho con người, cũng như dễ dàng để phân tích và tạo ra cho máy tính. Nó sử dụng một cú pháp nhẹ dựa trên cặp key - value, tương tự như các đối tượng và mảng trong JavaScript. Mỗi đối tượng JSON bao gồm một tập hợp các cặp "key" và "value", trong khi mỗi mảng JSON là một tập hợp các giá trị và **không có kích thước cố định**

Ví dụ một Object
```cpp
char *json = “ 
{ 
  "name": "John Doe",
  "age": 30,
  "city": "New York",
  "isStudent": false,
  "grades": [85, 90, 78]
}

“

```
- ```name``` , ```age```,... được gọi là key, mặc định là dạng chuỗi
- ```John Doe```, ```New York``` là value, có thể là số, ký tự hoặc một Object khác


Sử dụng JSON với những trường hợp xử lý những chuỗi phức tạp, không có kích thước cố định

**Các hàm xử lý chuỗi JSON**

#### Tạo kiểu dữ liệu JSON
```cpp
typedef enum
{
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;
```
Các kiểu dữ liệu như int, double, float đều được đại diện bằng kiểu ```JSON_NUMBER```. Tương tự với các kiểu dữ liệu khác.

```cpp
typedef struct JsonValue
{
    JsonType type;
    union
    {
        int boolean;
        double number;
        char *string;
        struct
        {  
            struct JsonValue *values;
            size_t count;
        } array;
        struct
        {
            char **keys; 
            struct JsonValue *values;
            size_t count; 
        } object;
    } value;
} JsonValue;
```

Dữ liệu được phân tích từ Json được lưu trong các biến đặt trong Union vì một thời điểm chỉ khởi tạo 1 biến và lưu vào vùng nhớ có kích thước tùy theo ``` JsonType type``` nên nếu tạo Struct thì các biến không liên quan sẽ bị lãng phí vùng nhớ

Với mảng thì sẽ được lưu trong một Struct Array gồm ba thông số 
- ```JsonValue *values```: Với Json, mỗi phần tử trong mảng sẽ có kiểu dữ liệu khác nhau nên phải đệ quy lại JsonValue, mảng ```value``` này sẽ chứa kiểu dữ liệu và giá trị của từng phần tử.
- ```Count``` để tính số lượng phần tử

Tương tự với mảng nhưng Object trong Json sẽ có thêm một thông số khác là ```char **keys```. Mỗi *keys là một chuỗi, được tập hợp bởi 1 mảng khác nên phải sử dụng con trỏ cấp 2 (mảng các chuỗi). Ví dụ: ```keys = ["name", "age", "city"];```

#### Hàm phân tích JSON
```cpp
JsonValue *parse_json(const char **json)
{
    while (isspace(**json))
    {
        (*json)++;
    }
    switch (**json)
    {
    case 'n':
        return parse_null(json);
    case 't':
    case 'f':
        return parse_boolean(json);
    case '\"':
        return parse_string(json);
    case '[':
        return parse_array(json);
    case '{':
        return parse_object(json);
    default:
        if (isdigit(**json) || **json == '-')
        {
            return parse_number(json);
        }
        else
        {
            printf("Cấu trúc Json không chính xác!");
            return NULL;
        }
    }
}
```
Truyền vào con trỏ cấp 2 để có khả năng thay đổi địa chỉ mà con trỏ Json trỏ tới, để phục vụ duyệt qua các ký tự trong chuỗi.
- Các hàm phân tích sẽ luôn kiểm tra khoảng trống để bỏ qua, chử xử lý các ký tự. Nếu gặp khoảng trống, sẽ tăng địa chỉ được trỏ tới để phân tích ký tự tiếp theo ```(*json)++```
- Sau đó lấy giá trị tại địa chỉ được trỏ tới bằng cách giải tham chiếu 2 lần con trỏ Json ```**json``` và so sánh các ký tự bắt đầu của các kiểu dữ liệu để thực thi các hàm xử lý liên quan
```cpp
else
  {
      printf("Cấu trúc Json không chính xác!");
      return NULL;
  }
```
- Nếu không thể phân tích kiểu dữ liệu trong chuỗi Json (Ví dụ: %$^#) thì báo lỗi và trả NULL dừng chương trình.
#### Hàm bỏ qua khoảng trắng
```cpp
static void skip_whitespace(const char **json)
{
    while (isspace(**json))
    {
        (*json)++;
    }
}
```


#### Hàm xử lý giá trị NULL
```cpp
JsonValue *parse_null(const char **json)
{
    skip_whitespace(json);
    JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
    if (strncmp(*json, "null", 4) == 0)
    {
        value->type = JSON_NULL; 
        *json += 4; 
        return value;          
    }
    free(value);
    return NULL;
}
```
Bỏ qua giá trị khoảng trắng để xử lý các phần tử khác
- Tạo trước một con trỏ trỏ tới vùng nhớ được cấp phát động bởi malloc có kích thước JsonValue để lưu giá trị.
- So sánh 4 byte tiếp theo tính tự địa chỉ hiện tại của con trỏ Json để so sánh chuỗi đó có bằng với ```"null"``` hay không
  - Nếu không phải null thì xóa bộ nhớ vừa cấp phát và trả về NULL (dừng chương trình)
  - Nếu đúng là null thì đặt kiểu dữ liệu cho value là ```JSON_NULL``` và công địa chỉ Json lên 4 byte để tiếp tục đọc chuỗi tiếp theo. Trả về giá trị value gồm kiểu dữ liệu và giá trị(rỗng).

#### Xử lý dữ liệu kiểu boolean
```cpp
JsonValue *parse_boolean(const char **json)
{
    skip_whitespace(json);
    JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
    if (strncmp(*json, "true", 4) == 0)
    {
        value->type = JSON_BOOLEAN;
        value->value.boolean = true;
        *json += 4;
    }
    else if (strncmp(*json, "false", 5) == 0)
    {
        value->type = JSON_BOOLEAN;
        value->value.boolean = false;
        *json += 5;
    }
    else
    {
        free(value);
        return NULL;
    }
    return value;
}
```
Bỏ bước xóa khoảng trắng. Sau đó sẽ tạo một vùng nhớ để chứa dữ liệu được trỏ tới bởi ```value```
Biến Boolean sẽ có hai giá trị là ```true``` hoặc ```false```
- Nếu là ```true``` thì đặt kiểu dữ liệu là ```JSON_BOOLEAN``` và gán giá trị là ```true``` và cộng 4 ký tự để tiếp tục xử lấy
- Tương tự với ```true``` nhưng ```false``` sẽ khởi tạo giá trị là ```false``` và tăng lên 5 ký thực
Nếu giá trị phân tích sai cú pháp. Ví dụ ```fasle``` hoặc ```trul``` thì xóa vùng nhớ được tạo và trả về NULL

#### Xử lý dữ liệu kiểu số
```cpp
JsonValue *parse_number(const char **json)
{
    skip_whitespace(json);
    char *end;         
    double num = strtod(*json, &end); 
    if (end != *json)
    {
        JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
        value->type = JSON_NUMBER;
        value->value.number = num;
        *json = end;
        return value;
    }
    return NULL;
}
```
Hàm ```strtod(const char *str, char **endptr)``` có hai tham số 
- str: chuỗi cần xử lý
- end: Vị trí đầu tiên của chuỗi chứa giá trị khác số 0,1,2,...9. Ví dụ "123ab" thì end ở vị trí a
Hàm sẽ trả về giá trị là một số double chứa số được xử lý từ chuỗi
Sau đó sẽ kiểm tra vị trí của end so với vị trí hiện tại của Json.  

Nếu không có số nào trong chuỗi thì vị trí của hai con trỏ là như nhau trả về NULL   
Nếu có số trong chuỗi được xử lý: 
- Tạo vùng nhớ để lưu giá trị
- Gán kiểu dữ liệu ```JSON_NUMBER``` và giá trị vào vùng nhớ
- Đặt địa chỉ json vào địa chỉ được trỏ tới của end

#### Hàm xử lý chuỗi string
```cpp
JsonValue *parse_string(const char **json)
{
    skip_whitespace(json);

    if (**json == '\"')
    {
        (*json)++;
        const char *start = *json;
        while (**json != '\"' && **json != '\0')
        {
            (*json)++;
        }
        if (**json == '\"')
        {
            size_t length = *json - start;                           // 3
            char *str = (char *)malloc((length + 1) * sizeof(char));
            strncpy(str, start, length);
            str[length] = '\0';

            JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
            value->type = JSON_STRING;
            value->value.string = str;
            (*json)++;
            return value;
        }
    }
    return NULL;
}
```
- Kiểm tra ký tự tiếp theo là dấu ```\"``` tức bắt đầu 1 chuỗi và cộng thêm 1 ký tự nữa để xử lý
- Tạo một con trỏ chứa địa chỉ bắt đầu của chuỗi đó
- Sau đó, duyệt đến hết chuỗi 
```
while (**json != '\"' && **json != '\0')
  { // Dich đến hết chuỗi
      (*json)++;
  }
```
- Lấy độ dài chuỗi duyệt được bằng địa chỉ đầu trừ địa chỉ cuối
- Cấp phát bộ nhớ động theo độ dài vừa tìm được
- Copy chuỗi vào vùng nhớ và thêm giá trị ```\0```(null) vào cuối chuỗi.
- Sau cùng, khởi tạo kiểu dữ liệu và gán giá trị vào biến JsonValue

Trả về NULL nếu xử lý lỗi

#### Xử lý kiểu dữ liệu mảng
```cpp
JsonValue *parse_array(const char **json)
{
    skip_whitespace(json);
    if (**json == '[')
    {
        (*json)++;
        skip_whitespace(json);

        JsonValue *array_value = (JsonValue *)malloc(sizeof(JsonValue));
        array_value->type = JSON_ARRAY;
        array_value->value.array.count = 0;
        array_value->value.array.values = NULL;

        while (**json != ']' && **json != '\0')
        {
            JsonValue *element = parse_json(json);
            if (element)
            {
                array_value->value.array.count++;
                array_value->value.array.values = (JsonValue *)realloc(array_value->value.array.values, array_value->value.array.count * sizeof(JsonValue));
                array_value->value.array.values[array_value->value.array.count - 1] = *element;
                free(element);
            }
            else
            {
                break;
            }
            skip_whitespace(json);
            if (**json == ',')
            {
                (*json)++;
            }
        }
        if (**json == ']')
        {
            (*json)++;
            return array_value;
        }
        else
        {
            free_json_value(array_value);
            return NULL;
        }
    }
    return NULL;
}
```
Mảng sẽ bắt đầu bằng ký tự ```[``` và kết thúc ```]```
```cpp
JsonValue *array_value = (JsonValue *)malloc(sizeof(JsonValue));
array_value->type = JSON_ARRAY;
array_value->value.array.count = 0;
array_value->value.array.values = NULL;
```
Khởi tạo vùng nhớ chứa dữ liệu và số phần từ bằng 0 cũng như giá trị NULL

Tiếp theo duyệt qua toàn bộ mảng và phân tích mảng bằng hàm xử lý Json ```parse_json(json)``` vì mảng có nhiều phần tử có kiểu dữ liệu khác nhau

- Nếu phần tử tồn tại thì tăng số phần tử của mảng, tăng vùng nhớ của mảng theo số phần tử và gán giá trị của phần tử đó vào mảng JsonValue. Cuối cùng là xóa vùng nhớ tạm chứa phần tử khi duyệt.
- Nếu phần tử không tồn tại thì thoát khỏi vòng lặp

Sau cùng kiểm tra xem đã duyệt hết mảng hay chưa và trả về kiểu dữ liệu và giá trị của mảng. Nếu chưa duyệt hết mảng (Tức trong mảng chứa giá trị lỗi) thì xóa vùng nhớ được khởi tạo và trả về NULL.

#### Xử lý Object 
```cpp
JsonValue *parse_object(const char **json)
{
    skip_whitespace(json);
    if (**json == '{')
    {
        (*json)++;
        skip_whitespace(json);

        JsonValue *object_value = (JsonValue *)malloc(sizeof(JsonValue));
        object_value->type = JSON_OBJECT;
        object_value->value.object.count = 0;
        object_value->value.object.keys = NULL;
        object_value->value.object.values = NULL;

        while (**json != '}' && **json != '\0')
        {
            JsonValue *key = parse_string(json);
            if (key)
            {
                skip_whitespace(json);
                if (**json == ':')
                {
                    (*json)++;
                    JsonValue *value = parse_json(json);
                    if (value)
                    {
                        object_value->value.object.count++;
                        object_value->value.object.keys = (char **)realloc(object_value->value.object.keys, object_value->value.object.count * sizeof(char *));
                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string;

                        object_value->value.object.values = (JsonValue *)realloc(object_value->value.object.values, object_value->value.object.count * sizeof(JsonValue));
                        object_value->value.object.values[object_value->value.object.count - 1] = *value;
                        free(value);
                    }
                    else
                    {
                        free_json_value(key);
                        break;
                    }
                }
                else
                {
                    free_json_value(key);
                    break;
                }
            }
            else
            {
                break;
            }
            skip_whitespace(json);
            if (**json == ',')
            {
                (*json)++;
            }
        }
        if (**json == '}')
        {
            (*json)++;
            return object_value;
        }
        else
        {
            free_json_value(object_value);
            return NULL;
        }
    }
    return NULL;
}
```
Tương tự như mảng nhưng bắt đầu và ký thúc bằng ký tự ```{}```

Bỏ qua phần tử trống và khởi tạo một vùng nhớ chứa Object, thêm một thông số ```keys = NULL``` so với mảng
```cpp
JsonValue *object_value = (JsonValue *)malloc(sizeof(JsonValue));
object_value->type = JSON_OBJECT;
object_value->value.object.count = 0;
object_value->value.object.keys = NULL;
object_value->value.object.values = NULL;
```

Kiểm tra keys trực tiếp bằng hàm xử lý chuỗi, vì keys trong Json mặc định là một String ```JsonValue *key = parse_string(json)```

Kiểm tra các ký tự ```:``` như cấu trúc của Object. Nếu sai thì trả về NULL

Nếu hợp lệ thì tiếp tục xử lý kiểu dữ liệu của value ứng với từng key. Và nếu values hợp lệ thì 
- Tăng vùng nhớ cho keys với kiểu dữ liệu *char
- Tăng vùng nhớ chứa values ứng với mỗi key theo kiểu dữ liệu JsonValue.

#### Hàm xóa JsonValue
```cpp
void free_json_value(JsonValue *json_value)
{
    if (json_value == NULL)
    {
        return;
    }

    switch (json_value->type)
    {
    case JSON_STRING:
        free(json_value->value.string);
        break;

    case JSON_ARRAY:
        for (size_t i = 0; i < json_value->value.array.count; i++)
        {
            free_json_value(&json_value->value.array.values[i]);
        }
        free(json_value->value.array.values);
        break;

    case JSON_OBJECT:
        for (size_t i = 0; i < json_value->value.object.count; i++)
        {
            free(json_value->value.object.keys[i]);
            free_json_value(&json_value->value.object.values[i]);
        }
        free(json_value->value.object.keys);
        free(json_value->value.object.values);
        break;

    default:
        break;
    }
}
```
Tùy theo kiểu dữ liệu mà JsonValue chứa sẽ có các phương pháp xóa khác nhau

</details>



## Bài 12: Binary Search & File Operations

<details><summary>Xem</summary>  

### Linear Search

Duyệt qua từng phần tử của mảng để xác định phần tử cần tìm.
- Sử dụng nhiều vòng lặp để duyệt.
- Tiêu hao thời gian khi số phần tử lớn.

Để khắc phục nhược điểm này, **Binary Search** được tạo ra.


### Binary Search

- **Xắp xếp** mảng ban đầu theo thứ tự **tăng dần** hoặc giảm dần.
- Dựa vào vị trí phần tử đầu và cuối của mảng, ta sẽ tìm vị trí ở giữa mảng để chia đôi mảng chứa phần tử cần tìm.
- So sánh giá trị tại vị trí giữa với giá trị cần tìm, nếu giá trị cần tìm lớn hơn thì tiếp tục tìm kiếm mảng bên phải, ngược lại tìm kiếm mảng bên trái (với trường hợp sắp xếp mảng tăng dần).
- Tiếp tục tìm vị trí giữa của mảng nhỏ vừa chia được và so sánh với giá trị cần tìm để đưa ra kết quả hoặc tiếp tục chia 2 mảng.

Khi so sánh phần tử giữa nếu không phải giá trị cần tìm, mảng được chia sẽ bắt đầu bằng vị trí **LEFT=MID+1** hoặc kết thúc tại **RIGHT=MID-1** tùy theo hướng của mảng mới để tránh việc so sánh lại giá trị của MID.

MID được tính bằng cách lấy trung bình vị trí đầu với vị trí cuối của mảng cần chia và **làm tròn xuống** nếu giá trị lẻ.

**Nhược điểm**: Khi lần đầu tìm kiếm, cần phải qua bước sắp xếp mảng làm mất thời gian hơn so với Linear Search nhưng với lần thứ hai trở đi, không cần phải sắp xếp nên thời gian tìm kiếm sẽ rất nhanh.

Ứng dụng trong các hoạt động cần sự đáp ứng nhanh như quản lý nhân viên,...

```cpp
int binarySearch(int *arr, int left, int right, int x)
{
    if (right >= left)
    {
        int mid = (right + left) / 2;

        if (arr[mid] == x)
            return mid;

        if (x < arr[mid])
            return binarySearch(arr, left, mid - 1, x);

        return binarySearch(arr, mid + 1, right, x);
    }
    return -1;
}
```
- Kiểm tra nếu ```right > left``` thì mảng lỗi, ngược lại thì sẽ tìm vị trí mid và so sánh để lựa chọn việc chia mảng ở bên trái hoặc bên phải để tiếp tục tìm kiếm.

### Thao tác với File CSV

File CSV (Comma-Separated Values) là một loại văn bản được sử dụng để lưu trữ và truyền tải dữ liệu có cấu trúc dưới dạng bảng, trong đó các dữ liệu của các cột được phân tách bằng dấu (,) hoặc một ký tự ngăn cách khác.

![Ảnh 1](https://i.imgur.com/AJ0eIby.png)

![Ảnh 2](https://i.imgur.com/ju2zHLK.png)

Các hàm đọc File

![Ảnh 3](https://i.imgur.com/vXQM9Kp.png)

![Ảnh 4](https://i.imgur.com/IXgS2Xc.png)

Ví dụ:
```cpp
#include <stdio.h>
#include <stdlib.h>

// Hàm tạo file CSV
void createCSV(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Cannot create file.csv %s.\n", filename);
        return;
    }
    fprintf(file, "ID,Name,Age\n"); // Ghi dòng tiêu đề vào file
    fclose(file);
}

// Hàm ghi dữ liệu vào file CSV
void writeDataToCSV(const char *filename, int id, const char *name, int age) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Cannot open file %s.\n", filename);
        return;
    }
    fprintf(file, "%d,%s,%d\n", id, name, age); // Ghi dữ liệu vào file
    fclose(file);
}

// Hàm đọc dữ liệu từ file CSV
void readCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file %s.\n", filename);
        return;
    }

    char line[100]; // Bộ đệm để đọc từng dòng
    printf("Data file %s:\n", filename);
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line); // In từng dòng ra màn hình
    }
    fclose(file);
}

int main() {
    const char *file = "data.csv";

    // Tạo file CSV
    createCSV(file);

    // Ghi dữ liệu vào file CSV
    writeDataToCSV(file, 5, "John", 25);
    writeDataToCSV(file, 2, "Alice", 30);
    writeDataToCSV(file, 3, "Bob", 22);

    // Đọc dữ liệu từ file CSV
    readCSV(file);

    return 0;
}
```

Kết quả:

![kq](https://i.imgur.com/5oQ01IH.png)
</details>

## AUTOSAR Classic

<details><summary>Xem</summary>  


**AUTOSAR** (**AUT**omotive **O**pen **S**ystem **AR**chitecture) là một tiêu chuẩn toàn cầu cho phát triển phần mềm ô tô với mục tiêu là chuẩn hóa kiến trúc phần mềm cho các hệ thống điều khiển điện tử (ECU) trong ô tô, nhằm tăng tính khả chuyển, khả mở rộng và giảm chi phí phát triển.

![Architechure](https://i.imgur.com/Cd7S24G.png)

Các Task sẽ chạy song song với nhau và trong một thời điểm chỉ có 1 task được thực thi để tránh việc làm sai xót dữ liệu, tất cả các Task được quản lý thông qua hệ điều hành (Operating System).

**So sánh**
![Sosanh](https://i.imgur.com/FwJT071.png)

- Các Task được viết song song nên có sự đồng nhất và khả năng tái sử dụng cao. Đồng thời việc bảo trì cũng dễ dàng hơn so với việc chương trình hoạt động tuần tự vì các Task được cấu hình riêng biệt.

### Kiến trúc AUTOSAR

Được chia làm 4 tầng
- **Application Layer**: Bao gồm các thành phần phần mềm ứng dụng, thực hiện các chức năng cụ thể của xe (như kiểm soát động cơ, phanh, v.v).
- **Runtime Environment(RTE)**: Là lớp trung gian giữa phần mềm ứng dụng và phần mềm cơ bản, giúp phần mềm ứng dụng có thể giao tiếp với nhau một cách chuẩn hóa (liên kết SWC và BSW).
- **Basic Software (BSW)**: Là phần mềm cơ bản, bao gồm các thành phần phần mềm tiêu chuẩn để quản lý các chức năng hệ thống, giao tiếp và điều khiển phần cứng.
- **Microcontroller** 

#### Application Layer

Bao gồm nhiều khối phần mềm ứng dụng (Software Component - SWC). **Mỗi SWC thực hiện 1 chức năng cụ thể** trong hệ thống ECU. Ví dụ: điều khiển động cơ, phanh, túi khí,...

![anh](https://i.imgur.com/ECiUKwP.png)

SWC chỉ quan tâm đến **logic** (tính toán số học, khởi động thế nào), không cần quan tâm đến phần cứng. Tuy nhiên, SWC vẫn có thể giao tiếp với nhau và giao tiếp với phần cứng thông qua RTE.

#### Runtime Environment(RTE)

RTE đóng vai trò trung gian, quan trọng trong việc kết nối các Software Components (SWC) trền tâng Application Layer và Basic Software (BSW) thông qua một kiến trúc trừu tượng.

Chức năng:
- **Truyền thông tin giữa các SWCs**: RTE cung cấp cơ chế truyền thông để các thành phần phần mềm (SWCs) có thể trao đổi dữ liệu hoặc gọi dịch vụ với nhau mà không cần biết chi tiết về các phần còn lại của hệ thống. 
- **Kết nối SWCs với BSW**: RTE cung cấp giao diện để các SWCs có thể tương tác với BSW. Điều này giúp các SWCs có thể sử dụng các dịch vụ hoặc điều khiển phần cứng một cách dễ dàng.
- Hỗ trợ việc lập lịch và điều phối thực thi của các SWCs theo các sự kiện hoặc chu kỳ định sẵn. 

#### Basic Software
Basic Software (BSW) là một trong ba thành phần chính của kiến trúc AUTOSAR, đóng vai trò nền tảng để hỗ trợ phần mềm ứng dụng (SWC) hoạt động trên phần cứng. BSW cung cấp các dịch vụ cơ bản như quản lý phần cứng, giao tiếp, chẩn đoán, và các dịch vụ hệ thống.

BSW được chia thành 3 tầng:
- Service Layer.
- ECU Abstraction Layer.
- Microcontroller Abstraction Layer - MCAL.

**Service Layer**:
Đây là lớp cao nhất trong BSW, cung cấp các dịch vụ hệ thống và tiện ích cho các phần mềm ứng dụng (SWC) và các lớp khác của BSW.
Là nơi **lưu trữ hệ điều hành của hệ thống tại lớp (System Services)**. Các dịch vụ khác bao gồm quản lý thời gian thực, chẩn đoán, quản lý lỗi, quản lý nguồn, bộ nhớ v.v.

**ECU Abstraction Layer**:
Lớp này cung cấp một giao diện trừu tượng cho tất cả các thiết bị ngoại vi và phần cứng cụ thể của ECU. Nó ẩn đi sự khác biệt về phần cứng của các thiết bị ngoại vi khác nhau và cung cấp một giao diện tiêu chuẩn cho các lớp bên trên (Service Layer và SWC). **Là nơi giao tiếp BSW với tầng Application thông qua RTE**

**MCAL (Microcontroller Abstraction Layer):**
Đây là lớp thấp nhất trong BSW, cung cấp giao diện trừu tượng để tương tác trực tiếp với các thành phần phần cứng của vi điều khiển, chẳng hạn như bộ xử lý trung tâm (CPU), các thiết bị ngoại vi tích hợp (như ADC, PWM, UART), và các bộ định thời (timer).



</details>


## Bài 13: Class

<details><summary>Xem</summary>  

Trong C++, từ khóa "class" được sử dụng để định nghĩa một lớp, là một cấu trúc dữ liệu tự định nghĩa có thể chứa dữ liệu và các hàm thành viên liên quan. 

### Khai báo Class
```cpp
#include <iostream>
using namespace std;

class Test
{

private:
    int thuocTinh_A;
    float thuocTinh_B;

public:
    // Constructor có tham số, thực thi khi khởi tạo một đối tượng của Class, thường dùng để khởi tạo giá trị ban đầu của các thuộc tính

    int age;
    char *name;
    float score;

    Test(int init_A, float init_B, int init_age, char *init_name, float init_score)
    {
        thuocTinh_A = init_A;
        thuocTinh_B = init_B;
        age = init_age;
        name = init_name;
        score = init_score;
    }

    // Thiết lập giá trị các thuộc tính gián tiếp
    void setThuocTinh_A(int value)
    {
        thuocTinh_A = value;
    }

    void setThuocTinh_B(int value)
    {
        thuocTinh_B = value;
    }

    // Lấy giá trị thuộc tính gián tiếp thông qua hàm
    int getThuocTinh_A()
    {
        return thuocTinh_A;
    }

    float getThuocTinh_B()
    {
        return thuocTinh_B;
    }

    // Hiển thị giá trị hai thuộc tính của Class
    void display()
    {
        cout << "Giá trị của A: " << thuocTinh_A
             << "\nGiá trị của B: " << thuocTinh_B
             << "\nTuổi: " << age
             << "\nTên: " << name
             << "\nĐiểm: " << score << endl;
    }
};

int main()
{
    // Tạo đối tượng và khởi tạo giá trị cho hai thuộc tính
    Test Test1(0, 0, 0, "", 0);

    // Gọi phương thức in ra giá trị
    Test1.display();

    cout << endl
         << endl;

    // Thay đổi giá trị thuộc tính thông qua các hàm Public
    Test1.setThuocTinh_A(1);
    Test1.setThuocTinh_B(1);

    Test1.age = 20;
    Test1.name = "Van Tu";
    Test1.score = 8.2;

    Test1.display();

    return 0;
}
```

Các hàm trong Class được gọi là **phương thức**, các biến thì được gọi là **thuộc tính**. Các phương thức và thuộc tính có các mức độ triển khai khác nhau như:
- Public: Các hàm khác có thể truy cập được các phương thức, thuộc tính từ bên ngoài lớp.
- Private: Chỉ có khả năng truy cập từ bên trong lớp, bên ngoài muốn truy cập thì phải gián tiếp thông qua các hàm get, set.
- Protected: Truy cập cục bộ trong Class hoặc các Class kế thừa.
Các cách triển khai này nhằm mục đích đảm báo tính bảo mật cho các thuộc tính, phương thức trong Class bằng cách hạn chế quyền truy cập từ bên ngoài.

Cấu trúc khai báo một Class
```cpp
class ClassName {
private:
    int thuoctinh1;
    void phuongthuc1();
protected:
    int thuoctinh2;
public:
    ClassName() {}

    ~ClassName(){}
    
    int thuoctinh3;
    void phuongthuc2();
};
```
Ngoài ra còn hai khái niệm khác của Class là **Constructor** và **Destructor**

- Constructor được gọi khi một đối tượng của Class được khởi tạo, thường có chức năng cấu hính thông số ban đầu cho các thuộc tính của Class đó. Constructor là hàm có tên trùng với tên của Class Ví dụ trên ```ClassName() {}```
- Ngược lại, Destructor sẽ được gọi khi một đối tượng được giải phóng. Tên hàm trùng với Class và có dấu ```~``` ở trước. Ví dụ ```~ClassName(){}```

Để truy cập một thuộc tính thuộc kiểu Public:
```cpp
Test1.age = 20;
Test1.name = "Van Tu";
Test1.score = 8.2;
```
Ta sẽ trực tiếp lấy giá trị của thuộc tính đó thông qua cú pháp ```tenClass.tenThuocTinh```.

Tương tự với các phương thức được gọi cũng có cú pháp ```tenClass.tenPhuongThuc()```.

Nếu các phương thức và thuộc tính ở kiểu private mà các hàm bên ngoài muốn truy cập vào thì phải thông qua hàm set và get. Với ví dụ trên, có hai thuộc tính Private là ```thuocTinh_A``` và ```thuocTinh_B```

Để cập nhật giá trị thuộc tính thì hàm khác bên ngoài Class phải gọi hàm 
```cpp
void setThuocTinh_A(int value)
{
    thuocTinh_A = value;
}
```
để gián tiếp gán giá trị value vào giá trị của ```thuocTinh_A``` thông qua phương thức ```setThuocTinh_A```

Tương tự với việc lấy giá trị của thuộc tính phải thông qua hàm ```get```
```
int getThuocTinh_A()
{
    return thuocTinh_A;
}
```
Hàm này sẽ trả về giá trị của ```thuoctinh_A``` để gán vào một biến nào đó.



### Truy cập Class thông qua con trỏ

```cpp
#include <iostream>
using namespace std;

class Test {
public:
    int value;

    void display() {
        cout << "Giá trị của Value: " << value << endl;
    }
};

int main() {
    Test Test1;
    Test* ptr = &Test1;  // Tạo con trỏ trỏ đến đối tượng Test1

    ptr->value = 100;  // Thay đổi giá trị thuộc tính thông qua con trỏ

    ptr->display();  // Gọi phương thức in ra giá trị value thông qua con trỏ

    return 0;
}
```
Với ví dụ trên, ta sẽ tạo một đối tượng tên ```Test1``` và tạo một đối tượng con trỏ ```ptr``` trỏ đến Test1.
Khi đó để truy cập các thuộc tính của ```Test1``` thông qua ```ptr``` ta phải thay dấu ```.``` thành ```->```


















### Static

### 5.1. Static property

Khi một property trong class được khai báo với từ khóa static, thì tất cả các object sẽ dùng chung địa chỉ của property này.

- Các đối tượng sử dụng dung một địa chỉ của thuộc tính, nên thuộc tính này có giá trị như nhau với các đối tượng khác nhau
- Cần phải khởi tạo bên ngoài Class
- Bạn có thể truy cập static property bằng cách sử dụng tên class hoặc thông qua một đối tượng của class.
```cpp
#include <iostream>
using namespace std;

class HinhChuNhat {

public:
    double chieuDai;
    double chieuRong;
    
    static int var;
};

int HinhChuNhat::var;

int main()
{
    HinhChuNhat hinh1;
    HinhChuNhat hinh2;
    HinhChuNhat hinh3;

    HinhChuNhat::var = 2;

    cout << "address of chieu dai: " << &hinh1.chieuDai << '\n'; 
    cout << "address of chieu dai: " << &hinh2.chieuDai << '\n'; 
    cout << "address of chieu dai: " << &hinh3.chieuDai << endl << endl; 

    cout << "address of var hinh1: " << &hinh1.var << '\n'; 
    cout << "address of var hinh2: " << &hinh2.var << '\n'; 
    cout << "address of var hinh3: " << &hinh3.var << endl << endl; 


    cout << "value of var hinh1: " << hinh1.var << '\n'; 
    cout << "value of var hinh2: " << hinh2.var << '\n'; 
    cout << "value of var hinh3: " << hinh3.var << endl << endl; 

    hinh1.var = 3;

    cout << "value of var hinh1: " << hinh1.var << '\n'; 
    cout << "value of var hinh2: " << hinh2.var << '\n'; 
    cout << "value of var hinh3: " << hinh3.var << endl << endl; 

    return 0;
}
```
Kết quả:
```
address of chieu dai: 0xd887fffa90
address of chieu dai: 0xd887fffa80
address of chieu dai: 0xd887fffa70

address of var hinh1: 0x7ff622ca7030
address of var hinh2: 0x7ff622ca7030
address of var hinh3: 0x7ff622ca7030

value of var hinh1: 2
value of var hinh2: 2
value of var hinh3: 2

value of var hinh1: 3
value of var hinh2: 3
value of var hinh3: 3
```
Với kết quả trên ta thấy, địa chỉ của biến static var là như nhau giữa các đối tượng khác nhau và có thể thay đổi bằng hai cách giống với lý thuyết.


Với thuộc tính Static, ta không thể khởi tạo trực tiếp bên trong Class, nhưng có một ngoại lệ đối với thuộc tính kiểu const.
```cpp
class MyClass {
public:
    static const int constValue = 10;  // Khởi tạo trực tiếp trong class
};
```

### Static method

Khi một method trong class được khai báo với từ khóa static:
- Method này độc lập với bất kỳ đối tượng nào của lớp.
- Method này có thể được gọi ngay cả khi không có đối tượng nào của class tồn tại.
- Method này có thể được truy cập bằng cách sử dụng tên class thông qua toán tử ```::```.
- Method này có thể truy cập các static property và các static method bên trong hoặc bên ngoài class.
- Method có phạm vi bên trong class và không thể truy cập con trỏ đối tượng hiện tại.

```cpp
#include <iostream>

using namespace std;

class HinhChuNhat
{
public:
    double chieuDai;
    double chieuRong;
    static int count;

    HinhChuNhat(int dai, int rong)
    {
        chieuDai = dai;
        chieuRong = rong;
        count++;
    }

    ~HinhChuNhat(){
        cout << "Dien tich: " << chieuDai * chieuRong << endl;
    }

    static void display()
    {
        cout << "Number of object: " << count << endl;
    }
};

int HinhChuNhat::count = 0;

int main()
{
    HinhChuNhat::display();

    HinhChuNhat Hinh1(5, 3);
    HinhChuNhat Hinh2(6, 1);

    HinhChuNhat::display();

    return 0;
}



```

Kết quả:

```
Number of object: 0
Number of object: 2
Dien tich: 6
Dien tich: 15
```
Với kết quả ta thấy, khi chưa khởi tạo đối tượng nào thì phương thức display có thể được gọi bởi Class.
Đồng thời, Static Method có thể truy cập vào các thuộc tính dùng chung như biến ```count``` trên ví dụ

</details>



## Bài 14: Object Oriented Programming - Lập trình hướng đối tượng (OOP)

<details><summary>Xem</summary>  

Lập trình hướng đối tượng là một phương pháp để giải quyết bài toán lập trình mà khi áp dụng thì code sẽ trở nên dễ phát triển và dễ bảo trì hơn. 
Phương pháp này sẽ chia nhỏ chương trình thành các đối tượng và các mối quan hệ, mỗi đối tượng sẽ có các thuộc tính và phương thức. 
OOP có 4 tính chất là là tính đóng gói, tính kế thừa, tính đa hình và tính trừu tượng.

### Tính đóng gói

Đây là kỹ thuật giúp bạn che giấu đi những thông tin bên trong đối tượng bằng cách sử dụng phạm vi truy cập private cho các thuộc tính, muốn giao tiếp hay lấy ra các thông tin của đối tượng thì phải thông qua các phương thức public, từ đó sẽ hạn chế được các lỗi khi phát triển chương trình.  

Điều này giúp hạn chế được các truy xuất không hợp lệ tới các thuộc tính của đối tượng.  
Giúp ẩn đi những thông tin không cần thiết về đối tượng.
Cho phép bạn thay đổi cấu trúc bên trong lớp mà không ảnh hưởng tới lớp khác.

Có ba mức đóng gói: Private, Protected và Public. Để các Class hoặc hàm khác truy cập vào các thuộc tính và phương thức kiểu Private phải thông qua các Getter và Setter đẫ được để cập ở bài trước

Ví dụ:
```cpp
#include <iostream>
#include <string>
using namespace std;

class SinhVien{
    private:
        string name;
        int id;
        float score;
   
    public:
        SinhVien(){
            static int ID = 1;
            id = ID;
            ID++;
        }

        void setName(string newName){   // setter method
            // kiểm tra điều kiện
            name = newName;
        }

        string getName(){   // getter method
            return name;
        }

        void setScore(float newScore){   // setter method
            // kiểm tra điều kiện
            score = newScore;
        }

        float getScore(){   // getter method
            return score;
        }

        int getID(){
            return id;
        }

        void display(){
            cout << "ID: " << getID() << endl;
            cout << "Ten: " << getName() << endl;
            cout << "Score: " << getScore() << endl;
        }
};

int main(int argc, char const *argv[])
{
    SinhVien sv1, sv2;

    sv1.setName("Trung");
    sv1.setScore(9.2);
    sv1.display();

    cout << endl;

    sv2.setName("Anh");
    sv2.setScore(7.6);
    sv2.display();
    return 0;
}

```
Với ví dụ trên, các thuộc tính về ```name```, ```ID```, ```score``` được đóng gói mức độ private và hàm main phải truy cập thông qua hàm setName, setScore tại public để thay đổi giá trị của từng đối tượng.

### Tính kế thừa

Tính kế thừa ( Inheritance) là khả năng sử dụng lại các property và method của một class trong một class khác. Ta chia chúng làm 2 loại là class cha và class con. Để kế thừa từ class khác, ta dùng ký tự ```:```.

Có 3 kiểu kế thừa là public, private và protected. Những property và method được kế thừa từ class cha sẽ nằm ở quyền truy cập của class con tương ứng với kiểu kế thừa.

#### Tính chất

- Các member public của class cha vẫn sẽ là public trong class con.
- Các member protected của class cha vẫn sẽ là protected trong class con.
- Các member private của class cha không thể truy cập trực tiếp từ class con nhưng có thể được truy cập gián tiếp qua các phương thức public hoặc protected của class cha.

#### Ví dụ
```cpp
#include <iostream>
#include <string>

using namespace std;

class DoiTuong{
    protected:
        string ten;
        int id;

    public:
        DoiTuong(){  
            static int ID = 1;
            id = ID;
            ID++;
        }

        void setName(string _ten){
            // check chuỗi nhập vào
            ten = _ten;
        }

        void display(){
            cout << "Tên: " << ten << endl;
            cout << "ID: " << id << endl;
        }
};

class SinhVien : public DoiTuong{
    protected:
        string chuyenNganh;

    public:
        void setChuyenNganh(string _nganh){
            chuyenNganh = _nganh;
        }

        void display(){ // override
            cout << "Tên: " << ten << endl;
            cout << "ID: " << id << endl;
            cout << "Chuyên ngành: " << chuyenNganh << endl;
        }
};

class HocSinh : public DoiTuong{
    protected:
        string lop;
   
    public:
        void setLop(string _lop){
            lop = _lop;
        }

        void display(){ // override
            cout << "Tên: " << ten << endl;
            cout << "ID: " << id << endl;
            cout << "Lớp: " << lop << endl;
        }
};

class GiaoVien : public DoiTuong{
    protected:
        string chuyenMon;

    public:
        void setChuyenMon(string _mon){
            chuyenMon = _mon;
        }

        void display(){ // override
            cout << "Tên: " << ten << endl;
            cout << "ID: " << id << endl;
            cout << "Chuyên môn: " << chuyenMon << endl;
        }
};

int main(int argc, char const *argv[])
{

    SinhVien sv1;
    sv1.setName("Trung");
    sv1.setChuyenNganh("Computer Engineering");
    sv1.display();

    cout << endl;

    HocSinh hs1;
    hs1.setName("Tuấn");
    hs1.setLop("12A1");
    hs1.display();

    cout << endl;

    GiaoVien gv1;
    gv1.setName("Hải");
    gv1.setChuyenMon("Lý");
    gv1.display();
    return 0;
}
```

Với ví dụ trên, các Class SinhVien, HocSinh và GiaoVien kế thừa các thuộc tính ```ten``` và ```id``` kiểu protected của Class DoiTuong và các thuộc tính này chỉ có thể sử dụng nội bộ trong Class cha và các Class kế thừa.

Ngoài ra, hàm set cũng có thể kế thừa thông qua các Class con và Constructor vẫn được gọi ra khi các đối tượng của Class kế thừa được khởi tạo.

Kết quả:
``` 
Tên: Trung
ID: 1
Chuyên ngành: Computer Engineering

Tên: Tuấn
ID: 2
Lớp: 12A1

Tên: Hải
ID: 3
Chuyên môn: Lý
```

Khái niệm: Overwriting (Ghi đè phương thức)
Định nghĩa: Trong C++, overwriting xảy ra khi lớp con định nghĩa lại một phương thức đã được khai báo trong lớp cha với cùng tên, cùng tham số và kiểu trả về.
- Mục đích: Tùy chỉnh hoặc mở rộng hành vi của phương thức lớp cha trong lớp con.
- Cú pháp:
Phương thức của lớp cha phải được khai báo với từ khóa ```virtual``` để hỗ trợ ghi đè.
Nếu muốn lớp con không cho phép tiếp tục ghi đè thêm nữa, có thể sử dụng từ khóa ```final```.

Khái niệm này sẽ được hiểu rõ hơn trong bài sau

### Tính đa hình

Tính đa hình ( Polymorphism) có nghĩa là "nhiều dạng" và nó xảy ra khi chúng ta có nhiều class có liên quan với nhau thông qua tính kế thừa.  

Tính đa hình có thể được chia thành hai loại chính:
- Đa hình tại thời điểm biên dịch (Compile-time Polymorphism): Thực hiện nhờ cơ chế nạp chồng (OverLoading)
    - Nạp chồng hàm (Function Overloading): Nhiều hàm có cùng tên nhưng khác tham số.
    - Nạp chồng toán tử (Operator Overloading): Thay đổi cách hoạt động của các toán tử.
- Đa hình tại thời điểm chạy (Run-time Polymorphism): Thực hiện nhờ cơ chế ghi đè phương thức (Overwriting).

#### Đa hình tại thời điểm biên dịch

**Nạp chồng hàm (Function Overloading)**
```cpp
#include <iostream>
using namespace std;

class AreaCalculator {
public:
    // Hàm tính diện tích hình vuông
    int area(int side) {
        return side * side;
    }

    // Hàm tính diện tích hình chữ nhật
    int area(int length, int width) {
        return length * width;
    }

    // Hàm tính diện tích hình tròn
    double area(double radius) {
        return 3.14159 * radius * radius;
    }
};

int main() {
    AreaCalculator s;

    // Gọi các hàm nạp chồng
    cout << "Diện tích hình vuông: " << s.area(5) << endl; // Gọi hàm area(int)
    cout << "Diện tích hình chữ nhật: " << s.area(4, 6) << endl; // Gọi hàm area(int, int)
    cout << "Diện tích hình tròn: " << s.area(3.5) << endl; // Gọi hàm area(double)

    return 0;
}
```
Với ví dụ về Function OverLoading, ta có ba hàm với cùng tên ```area``` nhưng kiểu dữ liệu trả về và tham số khác nhau. Vì thế, ta có thể từ một hàm mà tính toán được cả ba giá trị về diện tích của hình vuông, chữ nhật và hình tròn.

**Nạp chồng toán tử (Operator Overloading): 
```cpp
#include <iostream>
using namespace std;

class Complex {
private:
    double real;   // Phần thực
    double imag;   // Phần ảo
public:
    // Constructor
    Complex(double r, double i){
        real = r;
        imag = i;
    }

    // Nạp chồng toán tử +
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) {
        return Complex(real - other.real, imag - other.imag);
    }

    // Hàm hiển thị số phức
    void display() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1(5.0, 9.0); // Số phức c1 = 3 + 4i
    Complex c2(1.5, 3.5); // Số phức c2 = 1.5 + 2.5i

    // Sử dụng toán tử + đã nạp chồng
    Complex c3 = c1 + c2;
    Complex c4 = c1 - c2;
    // Hiển thị kết quả
    cout << "C1 = ";
    c1.display();
    cout << "C2 = ";
    c2.display();
    cout << "C1 + C2 = ";
    c3.display();
    cout << "C1 - C2 = ";
    c4.display();

    return 0;
}
```
Kết quả:
```
C1 = 5 + 9i
C2 = 1.5 + 3.5i
C1 + C2 = 6.5 + 12.5i
C1 - C2 = 3.5 + 5.5i
```
Cú pháp ```Complex operator+(const Complex& other)``` sẽ định nghĩa lại cách hoạt động của toán tử ```+``` khi áp dụng cho hai đối tượng của Class Complex để cộng hai số ảo. Kết quả sẽ trả về cộng hai phần thực và hai phần ảo lại với nhau ```Complex(real + other.real, imag + other.imag)```. Tương tự với phép trừ.

### Đa hình tại thời điểm chạy - Ghi đè phương thức (OverWriting)

```cpp
#include <iostream>
using namespace std;

class Dad {
public:
    virtual void display() { // Phương thức ảo
        cout << "Display từ lớp Dad" << endl;
    }
};

class ConA : public Dad {
public:
    void display() override { // Ghi đè phương thức của lớp cha
        cout << "Display từ lớp conA" << endl;
    }
};

class Mom {
public:
    void display() { // Phương thức ảo
        cout << "Display từ lớp Mom" << endl;
    }
};


class ConB : public Mom {
public:
    void display() { // Ghi đè phương thức của lớp cha
        cout << "Display từ lớp conB" << endl;
    }
};

int main() {
    
    Dad* D;
    ConA A;
    D = &A;
    
    D->display(); 

    Mom* M;
    ConB B;
    M = &B;

    M->display();

    return 0;
}
```

Kết quả:
```
Display từ lớp conA
Display từ lớp Mom
```

### Tính trừu tượng
Tính trừu tượng đề cập đến việc ẩn đi các chi tiết cụ thể của một đối tượng và chỉ hiển thị những gì cần thiết để sử dụng đối tượng đó. Nó tập trung vào những gì đối tượng làm được (chức năng) thay vì cách nó làm (triển khai cụ thể).

Tính trừu tượng giúp:
- Đơn giản hóa thiết kế và tổ chức chương trình.
- Tập trung vào các khía cạnh quan trọng và loại bỏ các chi tiết phức tạp.
- Dễ bảo trì và mở rộng mã nguồn.

```cpp
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class GiaiPhuongTrinh{
    private:	// a,b,c,x1,x2,delta: tính đóng gói
        double a;
        double b;
        double c;
        double x1;
        double x2;
        double delta;
        void tinhNghiem(){	// tính trừu tượng
            delta = b*b - 4*a*c;
            if (delta < 0){
                delta = -1;
            }
            else if (delta == 0){
                x1 = x2 = -b/ (2*a);
            }
            else if (delta > 0){
                x1 = (-b + sqrt(delta))/(2*a);
                x2 = (-b - sqrt(delta))/(2*a);
            }
        }
       
    public:
        void enterNumber(double num_a, double num_b, double num_c);
        void printResult();

};

void GiaiPhuongTrinh::enterNumber(double num_a, double num_b, double num_c){
    a = num_a;
    b = num_b;
    c = num_c;
}

void GiaiPhuongTrinh::printResult(){
    tinhNghiem();
    if (delta == -1){
        cout << "PT vo nghiem" << endl;
    }
    else if (delta == 0){
        cout << "PT co nghiem chung: " << x1 << endl;
    }
    else if (delta > 0){
        cout << "PT co 2 nghiem: \n";
        cout << "x1: " << x1 << endl;
        cout << "x2: " << x2 << endl;
    }
}
int main()
{
  GiaiPhuongTrinh phuongtrinh1;
  phuongtrinh1.enterNumber(1,5,4);
  phuongtrinh1.printResult();
  return 0;
}
```
Với ví dụ trên, Class đã đóng gói các bước giải phương trình vào Private và ẩn đi chúng. Chỉ để cập đến hai chức năng là nhập giá trị đầu vào và in ra kết quả nghiệm của phương trình. Đơn giản hóa quá trình hoạt động của chương trình.


</details>



## Bài 15: Virtual Function
<details><summary>Xem</summary>  

Hàm ảo là một hàm thành viên được khai báo trong class cha với từ khóa virtual.  
Khi một hàm là virtual, nó có thể được ghi đè (override) trong class con để cung cấp cách triển khai riêng.
Khi gọi một hàm ảo thông qua một con trỏ hoặc tham chiếu đến lớp con, hàm sẽ được quyết định dựa trên đối tượng thực tế mà con trỏ hoặc tham chiếu đang trỏ tới chứ không dựa vào kiểu của con trỏ.
- Override là việc ghi đè hàm ảo ở class con bằng cách định nghĩa lại nó. 
- Khi một hàm ảo được ghi đè, hành vi của nó sẽ phụ thuộc vào kiểu của đối tượng thực tế, chứ không phải kiểu của con trỏ hay tham chiếu.
- Tính đa hình Run-time xảy ra khi quyết định gọi hàm nào (phiên bản của class cha hay class con) được đưa ra tại thời điểm chạy, không phải lúc biên dịch, giúp mở rộng chức năng. Điều này giúp chương trình linh hoạt hơn, cho phép việc mở rộng chức năng mà không cần sửa đổi mã nguồn hiện tại.

Ví dụ
```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    virtual void makeSound() { // Hàm ảo
        cout << "Animal makes a sound" << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() override {
        cout << "Dog gaugau" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        cout << "Cat meows" << endl;
    }
};

void playSound(Animal* a) {
    a->makeSound(); // Gọi hàm ảo
}

int main() {
    Dog d;
    Cat c;
    
    playSound(&d); // Dog barks
    playSound(&c); // Cat meows

    return 0;
}
```
Kết quả
```
Dog barks
Cat meows
```

### Hàm thuần ảo (Pure Virtual Function)

Hàm thuần ảo là một hàm ảo không có phần định nghĩa trong class cha, được khai báo với cú pháp = 0 và khiến class cha trở thành **lớp trừu tượng(abstract class)**, nghĩa là **không thể tạo đối tượng từ class** này.  
Cú pháp
```cpp
class Base {
public:
    virtual void functionName() = 0; // Hàm ảo thuần túy
};
```

Tính chất
- Lớp có ít nhất một hàm ảo thuần túy trở thành "lớp trừu tượng" (abstract class).
- Lớp trừu tượng không thể tạo đối tượng trực tiếp.
-   Lớp con bắt buộc phải ghi đè (override) hàm ảo thuần túy, nếu không cũng trở thành lớp trừu tượng.
- Lớp trừu tượng không nhất thiết phải chỉ chứa hàm ảo thuần túy, nó cũng có thể có hàm thông thường với phần thân.

Ví dụ
```cpp
#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0; // Hàm ảo thuần túy
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing Circle" << endl;
    }
};

class Square : public Shape {
public:
    void draw() override {
        cout << "Drawing Square" << endl;
    }
};

int main() {
    
    //Shape shapeA; Không thể tạo đối tượng cho lớp trừu tượng
    
    Shape* shape1;
    Square h1;
    shape1 = &h1;

    Shape* shape2 = new Circle();

    shape1->draw(); // Drawing Circle
    shape2->draw(); // Drawing Square

    delete shape2;

    return 0;
}
```
Kết quả: 
```
Drawing Circle
Drawing Square
```

Class Shape là một Class trừu tượng nên không thể khai báo đối tượng mà chỉ tạo được con trỏ để trỏ đến địa chỉ của những lớp kế thừa. Các lớp này phải định nghĩa lại hàm draw() để không trở thành một Class trừu tượng khác.

Ví dụ 2:
```cpp
#include <iostream>
#include <string>

using namespace std;

class Xe
{
    protected:
        string model;
        int namSanXuat;

    public:
        Xe(string m, int nam): model(m), namSanXuat(nam){}

        virtual void hienThiThongTin() = 0;
};

class Toyota : public Xe
{
    private:
        string dongCo;

    public:
        Toyota(string m, int nam, string dongCo): Xe(m,nam), dongCo(dongCo){}

        void hienThiThongTin() override
        {
            cout << "Hang xe: Toyota\n";
            cout << "Model: " << model << "\n";
            cout << "Nam san xuat: " << namSanXuat << "\n";
            cout << "Dong co: " << dongCo << "\n";
        }
};

class Honda : public Xe
{
    private:
        string mauSac;

    public:
        Honda(string m, int nam, string mau): Xe(m,nam), mauSac(mau){}

        void hienThiThongTin() override {
            cout << "Hang xe: Honda\n";
            cout << "Model: " << model << "\n";
            cout << "Nam san xuat: " << namSanXuat << "\n";
            cout << "Mau sac: " << mauSac << "\n";
        }
};

class Mazda : public Xe
{
    private:
        string loaiDanDong;

    public:
        Mazda(string m, int nam, string loaiDanDong): Xe(m,nam), loaiDanDong(loaiDanDong){}

        void hienThiThongTin() override {
            cout << "Hang xe: Mazda\n";
            cout << "Model: " << model << "\n";
            cout << "Nam san xuat: " << namSanXuat << "\n";
            cout << "Loai dan dong: " << loaiDanDong << "\n";
        }
};

int main(int argc, char const *argv[])
{
   
    Mazda cx3("CX-3", 2019, "Dan dong 4 banh"); // stack

    // Toyota toyota1("campry", 2020, "V6");   // 0x01
    
    Xe *ptr[] = {new Toyota("campry", 2020, "V6"),  // toyota("campry", 2020, "V6") // 0x01
                 new Honda("civic", 2019, "do"),
                 new Mazda("CX-5", 2021, "Dan dong 4 banh"),
                 new Toyota("corolla", 2018, "I4 1.8L"),
                 new Honda("accord", 2020, "den"),
                 &cx3};
   
    for (int i=0; i<6; i++)
    {
        ptr[i]->hienThiThongTin();
        cout << "--------------" << endl;
        delete ptr[i];
    }
    return 0;
}
```
Với ví dụ trên, có một Class trừu tượng là lớp Xe, ba lớp còn lại là ba lớp kế thừa lớp xe và các lớp này định nghĩa lại hàm thuần ảo ```hienThiThongTin()```

Tại mảng ```Xe *ptr[]```, đây là mảng các con trỏ nên không thể truyền vào một đối tượng trực tiếp như ```Toyota toyota1("campry", 2020, "V6")``` mà phải truyền vào một con trỏ, vì thế ta có cú pháp ```new Honda("civic", 2019, "do")```
### Đa kế thừa

Đa kế thừa (Multiple Inheritance) là một tính năng trong C++ cho phép một lớp có thể kế thừa từ hai hoặc nhiều lớp cha cùng một lúc. Điều này cho phép lớp con thừa hưởng các thuộc tính và phương thức từ nhiều lớp cha, giúp kết hợp chức năng của nhiều Class.

Cấu trúc:
```cpp
class Con : public Cha1, public Cha2, public Cha3 {
    // Nội dung của lớp con
};
```

```cpp
#include <iostream>

using namespace std;

class Sensor{
    public:
        void initialize(){
            cout << "Initializing sensor" << endl;
            // code khởi tạo cảm biến
        }

        int readData(){
            cout << "Reading sensor data" << endl;
            // code đọc dữ liệu cảm biến
            return 30;
        }
};

class Communication{
    public:
        void setupCommunication() {
            cout << "Setting up communication protocol" << endl;
            // code thiết lập giao thức truyền thông (SPI, I2C, UART,...)
        }

        void sendData(int data) {
            cout << "Sending data: " << data << endl;
            // code gửi dữ liệu qua các giao thức
        }
};

class Control : public Sensor, public Communication{
    public:
        Control(){
            setupCommunication();

            initialize();

            int data = readData();

            sendData(data);
        }
};

int main(int argc, char const *argv[])
{
    Control sensorControl;
    return 0;
}
```

Ví dụ trên ta có hai Class Sensor và Comunication chưa những phương thức khác nhau. Và Class Control kế thừa cả hai Class này nên có thể sử dụng trực tiếp 4 phương thức trong Constructor của nó.

Kết quả:
```
Setting up communication protocol
Initializing sensor
Reading sensor data
Sending data: 30
```

**Vấn đề Diamond**  
Khi nhiều lớp cha có các phương thức hoặc thuộc tính trùng tên, việc gọi chúng từ lớp con có thể gây ra sự nhầm lẫn.

Khi một lớp con kế thừa từ hai lớp cha, mà hai lớp cha này đều cùng kế thừa từ cùng một lớp khác. Tình huống này tạo ra cấu trúc hình thoi (diamond), do đó được gọi là vấn đề "Diamond".

Ví dụ
```cpp
#include <iostream>

using namespace std;

class A{
    public:
        A(){ cout << "Constructor A\n"; }

        void hienThiA(){ cout << "Day la lop A\n"; }
};

class B : public A{
    public:
        B(){ cout << "Constructor B\n"; }

        void hienThiB(){ cout << "Day la lop B\n"; }
};

class C : public A {
    public:
        C(){ cout << "Constructor C\n"; }

        void hienThiC(){ cout << "Day la lop C\n"; }
};

class D : public B, public C{
    public:
        D(){ cout << "Constructor D\n"; }

        void hienThiD(){ cout << "Day la lop D\n"; }
};

int main() {
    D d;

    // d.hienThiA(); // wrong

    // Gọi phương thức từ lớp A qua B và C
    d.B::hienThiA(); // Gọi hàm hienThiA từ lớp A thông qua B
    d.C::hienThiA(); // Gọi hàm hienThiA từ lớp A thông qua C

    // d.hienThiB();
    // d.hienThiC();
    // d.hienThiD();

    return 0;
}
```
Với ví dụ trên, ta có cấu trúc  
- Một lớp A là lớp cha của hai lớp B và C.
- Một lớp D kế thừa từ cả B và C.
- D có hai bản sao của A, gây ra sự mơ hồ khi truy cập thành viên của A.
Vì thế ghi ta lập trình
```
D d;
d.hienThiA(); // Lỗi
```
thì d không biết gọi hàm ```hienthiA()``` từ A qua B hay qua C.

Để khắc phục ta phải chỉ rõ phạm vi của hàm 
```
d.B::hienThiA(); // Gọi từ A thông qua B
d.C::hienThiA(); // Gọi từ A thông qua C
```
Kết quả:
```
Constructor A
Constructor B
Constructor A
Constructor C
Constructor D
Day la lop A 
Day la lop A 
Day la lop B
Day la lop C
Day la lop D
```
Ta thấy, khi khởi tạo một đối tượng lớp D, thì các ConStructor của A được thực thi hai lần, cho thấy Class D vẫn có hai bản sao của A, gây tốn bộ nhớ không cần thiết.

Để khắc phục vấn đề này, ta sẽ sử dụng giải pháp **Kế thừa ảo**

### Kế thừa ảo (Virtual Inheritance)

- Kế thừa ảo giúp tránh vấn đề diamond problem trong đa kế thừa.
- Chỉ có một bản sao duy nhất của lớp cơ sở chung được kế thừa.
- Kế thừa ảo giúp quản lý các lớp liên quan đến phần cứng và giao tiếp. Điều này giúp tránh trùng lặp tài nguyên và quản lý hiệu quả trong hệ thống nhúng.

Cú pháp
```cpp
class Cha {
    // Nội dung lớp cha
};

class Con : virtual public Cha {
    // Nội dung lớp con
};
```
Ví dụ:
```cpp
#include <iostream>
using namespace std;

class A {
public:
    A() { cout << "Constructor A\n"; }
    void hienThiA() { cout << "Day la lop A\n"; }
};

// Thêm virtual
class B : virtual public A {
public:
    B() { cout << "Constructor B\n"; }
    void hienThiB() { cout << "Day la lop B\n"; }
};

// Thêm virtual
class C : virtual public A {
public:
    C() { cout << "Constructor C\n"; }
    void hienThiC() { cout << "Day la lop C\n"; }
};

class D : public B, public C {
public:
    D() { cout << "Constructor D\n"; }
    void hienThiD() { cout << "Day la lop D\n"; }
};

int main() {
    D d;

    d.hienThiA(); // Không còn lỗi, chỉ có một bản sao của A
    d.hienThiB();
    d.hienThiC();
    d.hienThiD();

    return 0;
}
```
Ví dụ này có cấu trúc giống với ví dụ trên bị phát sinh về lỗi Diamond, nhưng đã được khắc phục thông qua kế thừa ảo. Lúc này, D chỉ có một bản sao duy nhất của Acủa  nên có thể gọi trục tiếp phương thức ```hienThiA()``` mà không phải thông qua B hoặc C. Đồng thời, Constructor của A cũng chỉ được gọi một lần.

Kết quả:
```
Constructor A
Constructor B
Constructor C
Constructor D
Day la lop A
Day la lop B
Day la lop C
Day la lop D
```


</details>


## Bài 16: Namespace
<details><summary>Xem</summary>  

Xét một tình huống, khi chúng ta có hai người cùng tên là Trung trong cùng lớp. Bất cứ khi nào cần phân biệt họ một cách rõ ràng, chúng ta sẽ phải sử dụng thông tin bổ sung cùng với tên của họ, ví dụ: vị trí họ sống hay tên cha mẹ của họ...

Tình huống tương tự xảy ra trong C++. Ví dụ: Code bạn đang viết có hàm tên là test() và có thư viện khác có sẵn mà cũng có hàm test(). Bây giờ, trình biên dịch không biết phiên bản nào của hàm mà bạn muốn sử dụng trong code của mình.

Để giải quyết vấn đề này, chúng ta sẽ sử dụng **Namespace**

Namespace không phải là định nghĩa một kiểu dữ liệu mới mà  là cách nhóm các đối tượng như biến, hàm, class,... vào một không gian tách biệt.

Namespace được sử dụng với mục đích là để tránh xung đột tên khi có các định danh giống nhau được khai báo trong các phần của chương trình hoặc các thư viện khác nhau.

Cú pháp:
```cpp
namespace name_Namespace {
    //Hàm, biến
}
```
Sử dụng:
```cpp
name_Namespace::nameFunction
name_Namespace::nameVariable
```


Ví dụ:

```cpp
#include <iostream>

using namespace std;

namespace A{
    char *name = (char*)"Van Tu";
    float point = 9.2;
    void display(){
        cout << "Name: " << name;
        cout << "  Point: " << point << endl;
    }
}

namespace B{
    char *name = (char*)"Thanh Tu";
    float point = 8.1;
    void display(){
        cout << "Name: " << name;
        cout << "  Point: " << point << endl;
    }
}

int main(int argc, char const *argv[])
{
    cout << "Name: " << A::name << endl;
    cout << "Name: " << B::name << endl;
    cout << endl;
    A::display();
    B::display();
    return 0;
}
```
Với ví dụ trên, ta có hai Namespace A và B cùng chứa hai biến giống nhau là ```name``` và ```point``` nhưng không gây xung đột vì các biến này đặt tại hai không gian khác nhau. 

Kết quả:
```
Name: Van Tu  
Name: Thanh Tu

Name: Van Tu  Point: 9.2
Name: Thanh Tu  Point: 8.1
```

### Từ khóa Using trong Namespace

Từ khóa using cho phép bạn sử dụng các phần tử trong namespace mà không cần phải sử dụng toán tử '::' mỗi khi truy cập.

Thay vì sử dụng
```std::cout << "Trung" << std::endl;``` ta có thể lượt bỏ đi ```std::``` thành cú pháp ```cout << "Trung" << endl;```



Ý nghĩa trong việc rút gọn cú pháp tránh lặp tên không gian và làm cho mã dễ đọc hơn

Nếu sử dụng Using cho nhiều Namespace, việc đó có thể gây ra lỗi tham chiếu không rõ ràng khi có hai phần tử trung lặp nhau ở hai không gian. Vì thế chỉ nên sử dụng với các Namespace mà phần tử của chúng là duy nhất.

Ví dụ
```cpp
#include <iostream>

using namespace std;

namespace A{
    char *name = (char*)"Trung 20";
}

namespace B{
    char *name = (char*)"Trung 21";
}

using namespace A;

// using namespace B; // error: tham chiếu không rõ ràng

int main(int argc, char const *argv[])
{
    cout << "Name: " << name << endl;
    cout << "Name: " << B::name << endl;
    return 0;
}
```

Kết quả:
```
Name: Trung 20
Name: Trung 21
``` 
Khi gọi biến name thì sẽ mặc định truy cập vào Namespace A vì có sử dụng từ khóa Using.



### Namespace lồng nhau

Namespace lồng nhau (nested namespace) là khi bạn khai báo một namespace bên trong một namespace khác. Điều này giúp tổ chức mã nguồn tốt hơn, đặc biệt trong các dự án lớn.

```cpp
#include <iostream>

using namespace std;

namespace A{
    char *name = (char*)"space A";

    namespace C{
        char *str = (char*)"space C";
    }
}

namespace B{
    char *name = (char*)"space B";
}

using namespace A::C;

int main(int argc, char const *argv[])
{
    cout << "Name: " << A::name << endl;
    cout << "Name: " << B::name << endl;
    cout << "Name: " << str << endl;
    
    return 0;
}

```
Ví dụ trên ta có Namespace C được lồng trong Namespace A.
Đồng thời nếu muốn sử dụng trực tiếp C thì ta phải sử dụng Using theo cú pháp ```using namespace A::C```

Mặc dù sử dụng trực tiếp C nằm trong A, nhưng ta không thể sử dụng các phần tử nằm ngoài C trong A trực tiếp.

### Namespace mở rộng

Namespace có thể được mở rộng bằng cách khai báo nhiều lần cùng một tên namespace trong các phần khác nhau của chương trình. Các khai báo này sẽ được ghép lại thành một namespace duy nhất.

Ví dụ:
```cpp
#include <iostream>

// Định nghĩa ban đầu của namespace MyNamespace
namespace MyNamespace {
    void sayHello() {
        std::cout << "Hello from MyNamespace!" << std::endl;
    }
}

// Mở rộng MyNamespace để thêm một hàm mới
namespace MyNamespace {
    void sayGoodbye() {
        std::cout << "Goodbye from MyNamespace!" << std::endl;
    }
}

int main() {
    MyNamespace::sayHello();   // Gọi hàm từ phần đầu tiên
    MyNamespace::sayGoodbye(); // Gọi hàm từ phần mở rộng
    return 0;
}
```

Kết quả:
```
Hello from MyNamespace!
Goodbye from MyNamespace!
```

### Namespace C++ tiêu chuẩn (std);

Một trong những namespace quan trọng và phổ biến nhất trong C++ là std. Tất cả các thành phần của thư viện chuẩn C++ (như cout, cin, vector, string) đều được định nghĩa bên trong namespace std.

### Cấp phát bộ nhớ động trong C++

```cpp
#include <iostream>
using namespace std;
int main() {
    // Cấp phát động một số nguyên
    int* ptr1 = new int;  
    int* ptr2 = new int(20);  
    
    
    cout << "Value 1: " << *ptr1 << endl;
    cout << "Value 2: " << *ptr2 << endl;

    *ptr1 = 42;  

    cout << "Value 1: " << *ptr1 << endl << endl;
    
    int num = 5;
    int* ptrArr = new int[num];

    for(int i = 0; i < num; i++){
        ptrArr[i] = i*2;
    }  

    for(int i = 0; i < num; i++){
        cout << "Arr[" << i << "]: " << ptrArr[i] << endl;
    }  


    // Giải phóng bộ nhớ
    delete ptr1, ptr2;  

    delete[] ptrArr;

    return 0;
}
```
Các vùng nhớ được khởi tạo sẽ nằm tại bộ nhớ heap

```cpp
#include <iostream>

class Student {
public:
    std::string name;

    // Constructor
    Student(std::string n) { 
        name = n; 
    }

    void display() { 
        std::cout << "Student Name: " << name << std::endl; 
    }
};

int main() {
    // Cấp phát động một đối tượng Student
    Student s1("Tu"); //Vùng nhớ được đặt tại bộ nhớ Stack
    
    Student* s2 = new Student("Hoai"); //Vùng nhớ được đặt tại bộ nhớ Heap


    // Gọi phương thức của đối tượng
    s1.display();
    s2->display();
    // Giải phóng bộ nhớ
    delete s2;

    return 0;
}
```


</details>


## Bài 17: Standard Template Library
<details><summary>Xem</summary>  

Standard Template Library ( STL) là một thư viện trong ngôn ngữ lập trình C++ cung cấp một tập hợp các template classes và functions để thực hiện nhiều loại cấu trúc dữ liệu và các thuật toán phổ biến. 

STL đã trở thành một phần quan trọng của ngôn ngữ C++ và làm cho việc lập trình trở nên mạnh mẽ, linh hoạt và hiệu quả.

Một số thành phần chính của STL:
- Container - Bộ chứa
- Iterator - Bộ lặp
- Algorithms - Thuật toán
- Functor - Hàm đối tượng (Function Objects)

### Container
Một container là một cấu trúc dữ liệu chứa nhiều phần tử theo một cách cụ thể. STL (Standard Template Library) cung cấp một số container tiêu biểu giúp lưu trữ và quản lý dữ liệu. Như Vector, List, Map, Array

#### Vector
Vector là một trong những container quan trọng nhất trong STL của C++. Nó cung cấp một mảng động với khả năng thay đổi kích thước một cách linh hoạt. Vì là mảng động nên được lưu vào bộ nhớ **Heap**
Một số đặc điểm chính của vector:
- vector là một mảng động, tức là có khả năng thay đổi kích thước một cách linh hoạt.
- Truy cập ngẫu nhiên: Việc truy cập các phần tử của vector có thể được thực hiện bằng cách sử dụng chỉ số.
- Hiệu suất chèn và xóa: Chèn và xóa phần tử ở cuối vector có hiệu suất tốt. Tuy nhiên, chèn và xóa ở vị trí bất kỳ có thể đòi hỏi di chuyển một số phần tử.

Một số method của vector:
- ```at()```: Truy cập vào phần tử của vector, đọc hoặc ghi.
- ```size()```: Trả về kích thước của vector.
- ```resize()```: Thay đổi kích thước của vector.
- ```begin()```: Địa chỉ của phần tử đầu tiên của vector.
- ```end()```: Địa chỉ của phần tử cuối cùng của vector.
- ```push_back()```: Thêm phần tử vào vị trí cuối của vector.
- ```pop_back()```: Xóa phần tử tại vị trí cuối của vector.
- ```insert()```: Thêm phần tử tại vị trí bất kỳ.
- ```erase()```: Xóa phần tử tại vị trí bất kỳ.

Cấu trúc để tạo một vector có kiểu dữ liệu số nguyên
```
vector <int> arr = {2,5,7,4,9};
```

Ví dụ
```cpp
#include <iostream>
#include <vector>

using namespace std;


void printVector(vector <int> arr){
    for (int i = 0; i < arr.size(); i++)
    {
        cout  << arr.at(i) << " ";
    }
    cout << endl;
    cout << "-----------" << endl;
}

void printVector1(vector <int> arr){
    vector<int>::iterator item;// Tạo một con trỏ quét qua từng địa chỉ của các phần tử trong vector
    
    for (item = arr.begin(); item != arr.end(); item++) //begin: địa chỉ tại phần tử bắt đầu; end: địa chỉ sau địa chỉ cuối cùng của vector
    {
        cout  << *item << " ";
    }
    cout << endl;
    cout << "-----------" << endl;
}

int main()
{
  
    vector <int> arr = {2,5,7,4,9};
    printVector(arr);

    arr.at(0) = 3;
    arr.pop_back();
    arr.resize(7);
    printVector1(arr);
    

    arr.push_back(10);
    printVector(arr);

    arr.insert(arr.begin() + 2, 20); // Thêm giá trị 20 vào vị trí arr[2] và dịch các phần tử phía sau
    printVector(arr);

    arr.erase(arr.end() - 1);
    printVector(arr);

    return 0;
}

```
Kết quả:
```
2 5 7 4 9 
-----------
3 5 7 4 0 0 0
-----------
3 5 7 4 0 0 0 10
-----------
3 5 20 7 4 0 0 0 10
-----------
3 5 20 7 4 0 0 0
-----------
```

- ```arr.at(0) = 3;```: Thay đổi giá trị tại phần tử 0 thành giá trị 3.
- ```arr.resize(7);```: Thay đổi kích thước của vector thành 7 và khởi tạo giá trị 0
-  ```arr.push_back(10);```: Thêm vào cuối vector giá trị 10.
- ```arr.pop_back();```: Xóa phần tử cuối.
- ``` arr.insert(arr.begin() + 2, 20);```: Thêm phần tử vào vị trí arr[2].
- ```arr.erase(arr.end()-1);```: Xóa phần tử cuối cùng.

**Truy cập vector bằng interator**
```
void printVector1(vector <int> arr){
    vector<int>::iterator item;// Tạo một con trỏ quét qua từng địa chỉ của các phần tử trong vector
    
    for (item = arr.begin(); item != arr.end(); item++) //begin: địa chỉ tại phần tử bắt đầu; end: địa chỉ sau phần tửcuối cùng của vector
    {
        cout << "Value: " << *item << endl;
    }
}
```
Giải thích
- Cấu trúc Class của ireteror:
    ```cpp
    template <typename T>
    class MyIterator : public std::iterator<std::input_iterator_tag, T> {
    private:
        T* ptr;

    public:
        // Constructor
        explicit MyIterator(T* p) : ptr(p) {}

        // Toán tử dereference (*)
        T& operator*() { return *ptr; }

        // Toán tử ++ (tiến tới phần tử kế tiếp)
        MyIterator& operator++() {
            ++ptr;
            return *this;
        }

        // Toán tử so sánh ==
        bool operator==(const MyIterator& other) const {
            return ptr == other.ptr;
        }

        // Toán tử so sánh !=
        bool operator!=(const MyIterator& other) const {
            return ptr != other.ptr;
        }
    };
    ```

    Class này sẽ định nghĩa lại hai toán tử * và ++
    - ```++```: Cộng con trỏ đến địa chỉ của phần tử tiếp theo.
    - ```*```: Con trỏ ptr là con trỏ Private, nên không thể giải tham chiếu trực tiếp. Vì thế phải định nghĩa lại toán tử này để giải tham chiếu gián tiếp giá trị tại địa chỉ mà con trỏ ptr đang trỏ vào.

    Interator là một Class nằm trong vector vì thế để truy cập phải thông qua cấu trúc:```vector<int>::iterator item;```.

    Vì thế khi ta tạo vòng lặp for để truy cập giá trị từng phần tử ```for (item = arr.begin(); item != arr.end(); item++)``` thì con trỏ sẽ duyệt qua địa chỉ từng phần tử.

    Và để đọc thì gọi toán tử ```*``` để giải tham chiếu tại địa chỉ mà con trỏ đang trỏ tới

#### List - Danh sách liên kết

List là một container trong STL của C++, triển khai dưới dạng danh sách liên kết hai chiều. Dưới đây là một số đặc điểm quan trọng của list:
- **Truy cập tuần tự**: Truy cập các phần tử của list chỉ có thể thực hiện tuần tự, không hỗ trợ truy cập ngẫu nhiên.
- Hiệu suất chèn và xóa: Chèn và xóa ở bất kỳ vị trí nào trong danh sách có hiệu suất tốt hơn so với vector. Điều này đặc biệt đúng khi thêm/xóa ở giữa danh sách.

**Không như vector, List có các phần tử nằm tại những vị trí ngẫu nhiên và được liên kết với nhau**


Một số method của list:
- ```push_front()```
- ```push_back()```
- ```pop_back()```
- ```pop_front()```
- ```insert()```
- ```erase()```
- ```size()```

Truy cập các phần tử của List
- Cách 1:
    ```cpp
    for(auto item : arr1){
        cout << item << " ";
    }
    ```
    Sử dụng vòng lặp for cải tiến để duyệt qua từng phần tử của list

- Cách hai:
    ```cpp
    list <int> :: iterator it;
    int i = 0;
    for (it = arr1.begin(); it != arr1.end(); it++)
    {   
        cout << *it << " ";
    }    
    ```
    Sử dụng iterator, khác với vector, list có các phần tử nằm tại vị trí ngẫu nhiên. Vì thế, thay vì cộng địa chỉ của it lên số lượng byte nhất định để đọc thì sẽ thay đổi địa chỉ của con trỏ ứng với phần tử tiếp theo để đọc.

Thêm vào phần tử tại vị trí ngẫu nhiên, vì List là các phần tử với địa chỉ ngẫu nhiên nên không thể sử dụng cách cộng dồn số byte địa chỉ từ vị trí node đầu được. Ta sẽ kết hợp với iterator
```cpp
void insertListItem(list <int> &lst ,int position, int value){
    list <int> :: iterator it;
    int i = 0;
    for (it = lst.begin(); it != lst.end(); it++)
    {
        if (i == position)
        {
            lst.insert(it,value);
            break;
        }
        i++;
    }
}

void eraseListItem(list <int> &lst ,int position){
    list <int> :: iterator it;
    int i = 0;
    for (it = lst.begin(); it != lst.end(); it++)
    {
        if (i == position)
        {
            lst.erase(it);
            break;
        }
        i++;
    }
}
```
Ta sẽ duyệt qua từng phần tử và đến vị trí phần tử muốn thêm vào sẽ sử dụng hàm ``` lst.insert(it,value);``` để thêm giá trị vào vị trí đó. Tương tự với hàm xóa

Ví dụ:
```cpp
#include <iostream>
#include <list>

using namespace std;

void printList(list <int> lst){
    list <int> :: iterator it;
    int i = 0;
    for (it = lst.begin(); it != lst.end(); it++)
    {   
        cout << *it << " ";
    }    
    cout << endl << "----------------" << endl;
}



void insertListItem(list <int> &lst ,int position, int value){
    list <int> :: iterator it;
    int i = 0;
    for (it = lst.begin(); it != lst.end(); it++)
    {
        if (i == position)
        {
            lst.insert(it,value);
            break;
        }
        i++;
    }
}

void eraseListItem(list <int> &lst ,int position){
    list <int> :: iterator it;
    int i = 0;
    for (it = lst.begin(); it != lst.end(); it++)
    {
        if (i == position)
        {
            lst.erase(it);
            break;
        }
        i++;
    }
}



int main()
{
  
    list <int> arr1;

    arr1.push_back(5);
    arr1.push_back(3);
    arr1.push_back(6);
    arr1.push_back(2);
    arr1.push_back(9);
    arr1.push_front(1);

    //in các phần tử, cách 1:
    for(auto item : arr1){
        cout << item << " ";
    }
    cout << endl << "----------------" << endl;


    //Cách 2:
    list <int> :: iterator it;
    int i = 0;
    for (it = arr1.begin(); it != arr1.end(); it++)
    {   
        cout << *it << " ";
    }    
    cout << endl << "----------------" << endl;


    arr1.pop_back();
    printList(arr1);

    arr1.pop_front();
    printList(arr1);


    insertListItem(arr1, 2, 15);
    printList(arr1);


    eraseListItem(arr1, 3);
    printList(arr1);

    return 0;
}
```
Kết quả:
```
1 5 3 6 2 9     
----------------
1 5 3 6 2 9     
----------------
1 5 3 6 2       
----------------
5 3 6 2
----------------
5 3 15 6 2      
----------------
5 3 15 2        
----------------
```
Với chương trình trên, ta khởi tạo List và thêm vào cuối danh sách các giá trị 5 3 6 2 9 và thêm vào đầu danh sách giá trị 1.

Sau đó xóa giá trị cuối và giá trị đầu. Thêm giá trị vào vị trí 2 và xóa giá trị ở vị trí 3.


**Lưu ý**  
Sử dụng vector khi:
- Cần truy cập ngẫu nhiên đến các phần tử.
- Thực hiện nhiều thao tác chèn/xóa ở cuối danh sách.
- Dung lượng có thể biết trước hoặc thay đổi ít.

Sử dụng list khi:
- Thực hiện nhiều thao tác chèn/xóa ở bất kỳ vị trí nào trong danh sách.
- Cần thực hiện nhiều thao tác chèn/xóa mà không làm ảnh hưởng đến các iterators hiện có.
- Dung lượng không quan trọng hoặc thay đổi thường xuyên.
Tùy thuộc vào yêu cầu cụ thể của vấn đề, bạn có thể chọn sử dụng std::vector hoặc std::list.

#### Map
Map là một container trong STL của C++, cung cấp một cấu trúc dữ liệu ánh xạ **key-value**

Map lưu trữ các phần tử dưới dạng cặp key-value, trong đó mỗi key phải là duy nhất trong map.

Ta có thể thêm phần tử mới vào map bằng cách sử dụng operator [] hoặc hàm insert(). Để xóa phần tử, bạn có thể sử dụng hàm erase().
Ta có thể sử dụng iterator để duyệt qua các phần tử của map

Khác với vector và list chỉ có một kiểu dữ liệu. Map có hai kiểu liệu cần truyền vào
```std::map<KeyType, ValueType> myMap;```

**Tính chất**
- Cơ chế này hoạt động giống như **JSON nhưng key** của map **có thể thuộc bất kỳ kiểu dữ liệu nào** trong khi key của Json mặc định là String. 

- **Không quan tâm thứ tự khai báo, map sẽ tự sắp xếp thứ tự tăng dần của key.**

- Value có thể giống nhau nhưng key phải khác nhau. Nếu có **hai key trùng lặp**, trình biên dịch sẽ **lấy value được khai báo sau cùng**

Ví dụ:
```cpp
#include <map>
#include <iostream>
#include <string>

using namespace std;

struct Animal{
    string EnglishName;
    int soChan;
    string thucAn;
};

int main() {
    map<int, string> myMap;// Khai báo đối tượng map với key kiểu int và value kiểu string
    // Thêm phần tử vào map
    myMap[5] = "Five";// Thêm một cặp key-value: 5:"Five"
    myMap[3] = "Three";// Thêm một cặp key-value: 3:"Three"
    myMap[1] = "One";// Thêm một cặp key-value: 1:"One"
    myMap[2] = "Two";// Thêm một cặp key-value: 2:"Two"
    
    myMap.insert({4, "Four"}); // Thêm 1 cặp key-value: 4:"Four"
    myMap.erase(2); //Xóa key 2. Chỉ cần truyền key cần xóa, sẽ tự động xóa value ứng với key đó.

    map<string, Animal> myMap1 = 
    {
        {
            "Chó", {
                "Dog",
                4,
                "Ăn tạp"
            }
        },
        {
            "Gà", {
                "Chicken",
                2,
                "Ăn tạp"
            }
        },
        {
            "Sư tử", {
                "Lion",
                4,
                "Ăn thịt"
            }
        }
    };

    //Đọc dữ liệu cách 1
    for (auto var : myMap)
    {
        cout << "Key: " << var.first << " , " << "Value: " << var.second << endl; //first ứng với key, second là value ứng với key
    }
    cout << endl;
    
    //Cách 2
    map<string,Animal> ::iterator it;
    for (it = myMap1.begin(); it != myMap1.end(); ++it)
    {
        cout << "Key: " << (*it).first << " , " << "Value: " << "English:" << (*it).second.EnglishName << " - Số chân: " << (*it).second.soChan << " - Thức ăn: " << (*it).second.thucAn <<  endl;
    }
    
    return 0;
}

```
Kết quả:
```
Key: 1 , Value: One  
Key: 3 , Value: Three
Key: 4 , Value: Four
Key: 5 , Value: Five

Key: Chó , Value: English: Dog - Số chân: 4 - Thức ăn: Ăn tạp
Key: Gà , Value: English: Chicken - Số chân: 2 - Thức ăn: Ăn tạp
Key: Sư tử , Value: English: Lion - Số chân: 4 - Thức ăn: Ăn thịt
```
### Algorithms - Thuật toán

Thư viện STL (Standard Template Library) cung cấp một số thuật toán tiêu biểu thông qua algorithm. Các thuật toán này hoạt động trên các phạm vi hoặc các loại dữ liệu khác nhau, giúp thực hiện các nhiệm vụ như sắp xếp, tìm kiếm, chuyển đổi dữ liệu, và nhiều thao tác khác. 

Ví dụ:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{

    vector <int> arr = {3,5,7,4,1};

    for (auto const var : arr)
    {
        cout << "Vector: " << var << endl;
    }

    int numFind = 7;
    auto index = find(arr.begin(),arr.end(), numFind);
    if (index != arr.end())
    {
        cout << "Đã tìm thấy "<< numFind <<" tại vị trí " << (index - arr.begin()) << endl;
    }
    else
    {
        cout << "Không tìm thấy " << numFind << endl;
    }



    sort(arr.begin(), arr.end());
    
    cout << "Sắp xếp vector tăng dần: " << endl;

    for (auto const var : arr)
    {
        cout << "Vector: " << var << endl;
    }

    sort(arr.begin(), arr.end(), greater<>());
    
    cout << "Sắp xếp vector giảm dần: " << endl;

    for (auto const var : arr)
    {
        cout << "Vector: " << var << endl;
    }
    return 0;
}
```
Kết quả:
```
Vector: 3
Vector: 5
Vector: 7
Vector: 4
Vector: 1
Đã tìm thấy 7 tại vị trí 2
Sắp xếp vector tăng dần:
Vector: 1
Vector: 3
Vector: 4
Vector: 5
Vector: 7
Sắp xếp vector giảm dần:
Vector: 7
Vector: 5
Vector: 4
Vector: 3
Vector: 1
```
### Iterator
Iterator cung cấp một cách chung để duyệt qua các phần tử của một container mà không cần biết chi tiết về cách container được triển khai.  
Iterator là một đối tượng cho phép truy cập tuần tự qua các phần tử của một container.  
Nó giống như con trỏ, cho phép di chuyển qua các phần tử trong container.



</details>



## Bài 18: Template
<details><summary>Xem</summary>  

Template là một tính năng  cho phép lập trình viên viết mã tổng quát (generic code) mà có thể làm việc với nhiều kiểu dữ liệu khác nhau mà không cần viết lại nhiều lần. Nó giúp tăng tính tái sử dụng và linh hoạt của chương trình.

### Function Template
Trong C++, Function Templates giúp viết các function chung có thể được sử dụng cho nhiều kiểu dữ liệu khác nhau mà không cần phải triển khai nhiều phiên bản của cùng một function.

Ví dụ
```cpp
#include <iostream>
using namespace std;

// Khai báo một function template
template <typename T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    cout << findMax(10, 20) << endl;       // Dữ liệu kiểu int
    cout << findMax(3.5, 2.8) << endl;     // Dữ liệu kiểu double
    cout << findMax('A', 'Z') << endl;     // Dữ liệu kiểu char
    return 0;
}
```

```template <typename T>```: Khai báo một template với kiểu dữ liệu tổng quát T.  
```T findMax(T a, T b)```: Hàm có thể hoạt động với bất kỳ kiểu dữ liệu nào (int, double, char,...).  
Khi gọi hàm ```findMax(10, 20)```, trình biên dịch tự động suy luận kiểu T là int.  
Tương tự, ```findMax(3.5, 2.8)``` suy luận T là double.

Kết quả:
```
20
3.5
Z
```

### Class Template

Class templates trong C++ là một khái niệm tương tự như function templates, nhưng được áp dụng cho class thay vì function. Class templates cho phép bạn viết một lớp chung mà có thể được sử dụng với nhiều kiểu dữ liệu khác nhau.

Ví dụ:
```cpp
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class MyContainer {
private:
    T element;

public:
    MyContainer(T val) : element(val) {}

    T getValue() const {
        return element;
    }
};

int main()
{

    MyContainer<int> intContainer(42);
    MyContainer<double> doubleContainer(3.14);
    MyContainer<string> stringContainer("Trung");

    int intValue = intContainer.getValue();
    double doubleValue = doubleContainer.getValue();
    string stringValue = stringContainer.getValue();

    cout << "int value: " << intValue << endl;
    cout << "double value: " << doubleValue << endl;
    cout << "string value: " << stringValue << endl;

    return 0;
}
```
Ví dụ trên sẽ tạo một Class sử dụng cho nhiều kiểu dữ liệu, có một Constructor để khởi tạo giá trị của ```element``` và một getter.

Chúng ta sẽ kiểm tra kết quả với ba đối tượng thuộc ba kiểu dữ liệu khác nhau là int, double và string.

Kết quả:
```
int value: 42
double value: 3.14
string value: Trung
```

## Các kỹ thuật template nâng cao trong C++
### Non-Type Template Parameters (Tham số không phải kiểu dữ liệu)
Ngoài typename T, template còn có thể nhận các tham số là giá trị hằng số.

Ví dụ:
```cpp
#include <iostream>
using namespace std;

template <typename T, int N>
class Array {
private:
    T arr[N];
public:
    void set(int index, T value) {
        if (index >= 0 && index < N) {
            arr[index] = value;
        }
    }
    T get(int index) {
        return arr[index];
    }
    int size() {
        return N;
    }

    void print(){
        for (int i = 0; i < N; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Array<int, 5> arrInt;
    arrInt.set(0, 10);
    arrInt.set(1, 6);
    arrInt.set(2, 3);
    cout << "Kích thước mảng: " << arrInt.size() << endl;
    arrInt.print();

    Array<string, 3> arrString;
    arrString.set(1, "Tu");
    arrString.set(0, "Toan");
    arrString.set(2, "Hung");

    cout << "Kích thước mảng: " << arrString.size() << endl;
    arrString.print();

    return 0;

}
```

```template <typename T, int N>```: N là tham số không phải kiểu, xác định kích thước mảng.  
```Array<int, 5> arr;```: tạo một mảng có 5 phần tử kiểu int.

Kết quả:
```
Kích thước mảng: 5
10 6 3 32765 -272859112
Kích thước mảng: 3
Toan Tu Hung
```
### Template Metaprogramming (TMP)

Template Metaprogramming (TMP) là một kỹ thuật lập trình trong C++ giúp thực hiện các tính toán ngay tại thời điểm biên dịch (compile-time) thay vì chạy tại thời điểm thực thi (runtime). 

**Ứng dụng trong tính toán giai thừa tại thời điểm biên dịch**

```cpp
#include <iostream>
using namespace std;

// Template đệ quy để tính giai thừa tại compile-time
template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

// Trường hợp cơ sở: Factorial<0> = 1
template <>
struct Factorial<0> {
    static const int value = 1;
};

int main() {
    cout << "5! = " << Factorial<5>::value << endl; 
    cout << "7! = " << Factorial<7>::value << endl; 
    return 0;
}
```

Trong khi biên dịch, chương trình sẽ tính toán giai thừa ```Factorial<5>::value```. Và lúc run-time chỉ cần in ra giá trị.
```cpp
template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};
```
Tạo một Struct chứa giá trị của giai thừa trong biến Static Value, Struct có thể đọc mà không cần phải tạo đối tượng và biến này không thể thay đổi trong lúc chạy.

```
template <>
struct Factorial<0> {
    static const int value = 1;
};
```
Gán biến Value của ```Factorial<0> = 1```

Kết quả:
```
5! = 120
7! = 5040
```

### Expression Templates
Dùng để tối ưu hiệu suất của các biểu thức số học bằng cách tránh tạo ra các đối tượng trung gian không cần thiết.


### Variadic Templates
Tạo một hàm có thể chấp nhận số lượng tham số đầu vào không xác định.

```cpp
#include <iostream>

using namespace std;

void println()
{
    cout << endl;
}

template<typename T, typename... Rest>
void println(T first, Rest... rest) {
    cout << first << endl;
    println(rest...);
}


template <typename... Args>
void print(Args... args) {
 (cout << ... << args) << '\n';
}

int main() {
 print(1, 2, 3, "hello", 4.5, "Trung", 55);
 cout << "-------------------- \n" ;
 println(1, 2, 3, "hello", 4.5, "Trung", 55);
 return 0;
}

```

Giải thích:
```cpp
void println()
{
    cout << endl;
}

template<typename T, typename... Rest>
void println(T first, Rest... rest) {
    cout << first << endl;
    println(rest...);
}
```
- Hàm ```println()``` là hàm cơ sở, nếu hàm println được gọi khi không có tham số thì sẽ chạy hàm này.
- ```T first``` là tham số đầu tiên của hàm ```println```, các tham số còn lại được chứa trong ```rest```. Hàm này sẽ in lần lượt các giá trị tham số và xuống dòng.

```cpp
template <typename... Args>
void print(Args... args) {
 (cout << ... << args) << '\n';
}
```
- ```Args``` sẽ chứa tất cả các tham số truyền vào và in ra lần lượt không xuống dòng.

Kết quả:
```
123hello4.5Trung55
--------------------
1
2
3
hello
4.5
Trung
55
```


</details>


## Bài 19: Smart Pointer - Lambda
<details><summary>Xem</summary>  

### Lambda

Các hàm được tạo sẽ có một vùng nhớ riêng và sẽ giữ lại trong suốt quá trình thực thi. Nhưng với các hàm chỉ hoạt động một lần duy nhất thì việc này làm tiêu tốn bộ nhớ. Vì thể ta sẽ có cú pháp khai báo riêng cho chúng.

Lambda trong C++ là một cách để định nghĩa hàm vô danh (không cần khai báo tên hàm) ngay trong mã nguồn, thường dùng khi bạn chỉ cần hàm để sử dụng một lần hoặc trong một ngữ cảnh cụ thể mà không cần phải định nghĩa hàm ngoài.

Tính chất:
- Là hàm không có tên.
- Định nghĩa trực tiếp trong một hàm khác
- Cú pháp:  

```cpp
[capture] (parameter_list) -> return_type 
{ 
    //function_body 
}
```
Hoặc 
```
```cpp
[capture] (parameter_list)
{ 
    //function_body 
}
```
  
Không cần khai báo kiểu trả về, tự động suy diễn  
Trong đó  
- ```parameter_list```: Là các tham số truyền vào
- ```return_type```: là kiểu trả về (int, void, class,...).
- ```capture```: cho biết cách sử dụng các biến xung quang lambda
    - ```[<name_variable>]```: chỉ định cụ thể biến sẽ sử dụng, **read-only**, kể cả toàn cục của hàm chứa Lambda.

    - ```[=]```: cho phép sử dụng tất cả các biến xung quanh, **read-only**

    - ```[&<name_variable>]```: truyền tham chiếu của biến cụ thể, có thể đọc/ghi

    - ```[&]```: truyền tham chiếu của tất cả biến xung quanh

    - Phối hợp cả hai kiểu.


Ví dụ
```cpp
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int x = 1; // 0x01
    int y = 2; // 0x05
    int z = 3; // 0xf4

    int a = 9;
    int b = 2;

    // Không sử dụng biến
    auto sum = [](int a, int b)
    {
        return a + b;
    };
    cout << "Tổng 2 số: " << sum(a, b) << endl;

    // Sử dụng hai biến x,y READ-ONLY
    auto sub = [x, y](int a, int b)
    {
        return (a + b) - (x + y);
    };
    cout << "Hiệu a+b - (x+y): " << sub(a, b) << endl;

    // Sử dụng tất cả các biến READ-ONLY
    auto sumAll = [=](int a, int b)
    {
        return a + b + x + y + z;
    };
    cout << "Tổng tất cả: " << sum(a, b) << endl;

    // Sử dụng biến y và z, READ-WRITE
    auto sumChange = [&y, &z](int a, int b)
    {
        y = 15; // read - write
        z = 9;  // read - write
        return a + b + y + z;
    };
    cout << "Tổng sau khi thay đổi a+b+y+z: " << sumChange(a, b) << endl;

    // Tham chiếu được tất cả các biến xung quanh
    auto sumAll1 = [&](int a, int b)
    {
        x = 5;  // read - write
        y = 10; // read - write
        z = 1;  // read - write
        return a + b + x + y + z;
    };
    cout << "Tổng tất cả: " << sumAll1(a, b) << endl;

    // Kết hợp.
    auto sumCombine = [x, &y, &z](int a, int b)
    {
        // x = 5;   // read - write
        y = 10; // read - write
        z = 1;  // read - write
        return a + b + x + y + z;
    };
    cout << "Tổng kết hợp: " << sumCombine(1, 2) << endl;

    // Lambda không có tham sôs

    auto display = []()
    {
        cout << "Hello, world\n";
    };

    display();

    // Sử dụng trực tiếp lambda
    //Có tham số
    cout << [](int a, int b)
    {
        return a + b;
    }(2, 3)
         << endl;
    // Không tham số
    []()
    {
        cout << "Hello, world\n";
    }();

    return 0;
}
```
Kết quả:
```
Tổng 2 số: 11
Hiệu a+b - (x+y): 8
Tổng tất cả: 11
Tổng tất cả: 27
Tổng kết hợp: 19
Hello, world
5
Hello, world
```

Ví dụ 2: 
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> vec = {2,15,4,6,5,3,8,1,9};

    // sort(vec.begin(), vec.end(), greater<int>());

    cout << "Vector ban đầu: ";

    for (auto item : vec)
    {
        cout << item << " ";
    }
    cout << endl;

    // sắp xếp tăng dần
    sort(vec.begin(), vec.end(), [](int i, int j) -> bool
    {
        return i < j;
    });

    cout << "Vector sau khi sắp xếp: ";

    for (auto item : vec)
    {
        cout << item << " ";
    }
    cout << endl;

    cout << "Vector sau khi sắp xếp: ";

    // sắp xếp giảm dần
    sort(vec.begin(), vec.end(), [](int i, int j) -> bool
    {
        return i > j;
    });

    for (auto item : vec)
    {
        cout << item << " ";
    }
    cout << endl;


    int count_even = 0;
    int count_odd  = 0;

    vector<int> evens, odds;


    //vec.begin() và vec.end() xác định phạm vi của vector vec.
    //count_if sẽ duyệt từng phần tử trong phạm vi này, truyền từng phần tử đó vào lambda [&](int x).
    //x trong lambda là một tham số của hàm pred, được truyền vào từ count_if.
    
    count_if(vec.begin(), vec.end(), [&](int x)
    {
        if (x % 2 == 0)
        {
            count_even++;
            evens.push_back(x);
        } else {
            count_odd++;
            odds.push_back(x);
        }

        return false;
    });


    std::cout << "Số lượng số chẵn: " << count_even << endl;

    for (auto i : evens)
    {
        cout << i << " ";
    }

    cout << endl;

    cout << "Số lượng số lẻ: " << count_odd << endl;

    for (auto i : odds)
    {
        cout << i << " ";
    }

    return 0;
}

```
Ví dụ trên sẽ ứng dụng trục tiếp Lambda vào việc sắp xếp thứ tự của một vector  
```cpp
sort(vec.begin(), vec.end(), [](int i, int j) -> bool
    {
        return i < j;
    });
```

Hàm này có ba tham số truyền vào ```sort(first, last, compare);```
- First, last là con trỏ hoặc iterator trỏ đến phần tử đầu hoặc cuối trong phạm vi cần sắp xếp.
- compare: Hàm so sánh, ```true``` không hoán đối vị trí, ```false``` hoán đổi vị trí. 
- Hàm Lambda trả về true nếu i nhỏ hơn j, tức là giữ thứ tự hiện tại của i và j. Nếu i > j, sort sẽ hoán đổi vị trí của chúng.

Tương tự với hàm sắp xếp giảm dần.


Hàm tính số chẵn lẻ:
```cpp
count_if(vec.begin(), vec.end(), [&](int x)
    {
        if (x % 2 == 0)
        {
            count_even++;
            evens.push_back(x);
        } else {
            count_odd++;
            odds.push_back(x);
        }

        return false;
    });
```
- vec.begin() và vec.end() xác định phạm vi của vector vec.
- count_if sẽ duyệt từng phần tử trong phạm vi này, truyền từng phần tử đó vào lambda [&](int x).
- x trong lambda là một tham số của hàm pred, được truyền vào từ count_if.
- Nếu x chia hết cho hai thì là số chẵn.

Kết quả:
```
Vector ban đầu: 2 15 4 6 5 3 8 1 9 
Vector sau khi sắp xếp: 1 2 3 4 5 6 8 9 15
Vector sau khi sắp xếp: 15 9 8 6 5 4 3 2 1
Số lượng số chẵn: 4
8 6 4 2
Số lượng số lẻ: 5
15 9 5 3 1
```

### Smart-Pointer

Trong C++, smart pointers là một cơ chế quản lý bộ nhớ tự động giúp giảm thiểu rủi ro của lỗi liên quan đến quản lý bộ nhớ và giúp người lập trình tránh được việc quên giải phóng bộ nhớ đã được cấp phát.

Smart-Pointer là một **Class** chứa một con trỏ và nhiều cơ chế để quản lý

#### Unique Pointer
- unique_ptr là một loại smart pointer trong C++, giúp quản lý bộ nhớ động và tự động giải phóng bộ nhớ khi không còn cần thiết. 
- Đặc điểm chính của unique_ptr là khi một vùng nhớ được cấp phát thì chỉ có duy nhất một unique_ptr để quản lý, sở hữu vùng nhớ này, có thế lạ một đối tượng hoặc mảng và khi một unique_ptr bị hủy, bộ nhớ của đối tượng sẽ được tự động giải phóng.
- Nếu một con trỏ muốn truy cập vùng nhớ đã được quản lý bởi một con trỏ khác. Thì còn trỏ đang quản lý vùng nhớ đó phải được gán giá trị Null.

- **Unique chỉ ngăn các đối tượng unique pointer khác trỏ tới chứ không thể ngăn các con trỏ thông thường.**
```cpp
private:
        T *ptr; /**< Con trỏ thô đến đối tượng được quản lý. */
        

    public:
        /**
         * @brief   Constructor khởi tạo con trỏ UniquePointer.
         * @param   p   Con trỏ thô đến đối tượng. Giá trị mặc định là nullptr.
         */
        UniquePointer(T *p = nullptr) : ptr(p){}


        /**
         * @brief   Destructor giải phóng vùng nhớ của đối tượng được quản lý nếu không null.
         */
        ~UniquePointer()
        {
            if (ptr) delete ptr;
        }
```
- Khi một Unique Pointer được khởi tạo, sẽ gán đối tượng cho nó hoặc gán mặc định giá trị NULL bằng Constructor
- Và khi thu hồi sẽ thu hồi đối tượng được trỏ tới trước sau đó thu hồi con trỏ
```cpp
/**
         * @brief   Copy Constructor - Xóa bỏ khả năng sao chép đối tượng UniquePointer.
         */
        UniquePointer(const UniquePointer &other) = delete;


        /**
         * @brief   Copy Assignment Operator - Xóa bỏ khả năng gán bằng copy đối tượng UniquePointer.
         * @return  Trả về tham chiếu đến đối tượng UniquePointer hiện tại.
         */
        UniquePointer& operator = (const UniquePointer &other) = delete;
```
- Khi một con trỏ uptr2 được khởi tạo để copy uptr1 ```UniquePointer<int> uptr2(uptr1);``` thì Constructor của uptr2 sẽ thực thi để sao chép giá trị của uptr1 việc này vi phạm quy định chỉ duy nhất một con trỏ quản lý vùng nhớ. Vì thế sẽ bị lỗi được gọi là **Copy constructor**.

- Tương tự với phép gán hai con trỏ
    ```
    UniquePointer<int> uptr2;
        uptr2 = uptr1;
    ```
    Toán tử ```=``` sẽ được định nghĩa lại trong Class Unique Pointer để gán giá trị của hai con trỏ này. Nhưng việc này lại tiếp tục vi phạm quy định trên nhưng tại phép gán. Vì thế được gọi là **Copy Assignment Operator**


```cpp
/**
         * @brief   Toán tử dereference để truy cập đối tượng được quản lý.
         * @return  Tham chiếu đến đối tượng được quản lý.
         */
        T& operator * () const
        {
            return *ptr;
        }


        /**
         * @brief   Toán tử để truy cập các thành phần của đối tượng.
         * @return  Con trỏ đến đối tượng được quản lý.
         */
        T* operator -> () const
        {
            return ptr;
        }
```
Định nghĩa lại các toán tử ```*``` để giải tham chiếu giá trị mà con trỏ thô ptr đang trỏ tới và toán tử ```->``` để trỏ đến địa chỉ của ptr, trỏ đến các đối tượng có trong Class hoặc Struct được trỏ tới.

Sử dụng
```cpp
class Test 
{
    public:
        int value;

        Test(int val = 10) : value(val){}

        void setValue(int newValue)
        {
            value = newValue;
        }

        int getValue() const
        {
            return value;
        }

        void display() const 
        {
            cout << "Test value: " << getValue() << endl;
        }
};

int main(){
    UniquePointer<int> uptr1 = new int(10);
    cout << "new value of int: " << *uptr1 << endl;
    
    UniquePointer<Test> uptr = new Test(10);
    uptr->display();
    uptr->setValue(50);
    uptr->display();

    (*uptr).setValue(100);
    (*uptr).display();


}
```

Các Method có trong Class Unique Pointer
```cpp
T* get() const
        {
            return ptr;
        }

        
        /**
         * @brief   Chuyển quyền sở hữu đối tượng cho con trỏ thô bên ngoài.
         * @return  Con trỏ thô đến đối tượng trước khi release.
         */
        T* release()
        {
            T* temp = ptr;  // lưu lại địa chỉ của đối tượng đang quản lý
            ptr = nullptr;  // đặt con trỏ thô ptr thành con trỏ null
            return temp;    // trả về địa chỉ của đối tượng
        }

        
        /**
         * @brief   Giải phóng đối tượng hiện tại và quản lý đối tượng mới.
         * @param   p   Con trỏ thô đến đối tượng mới. Mặc định là nullptr.
         */
        void reset(T *newPtr = nullptr)
        {
            if (this->ptr) delete ptr;

            ptr = newPtr;
        }
```
- Hàm get() trả về con trỏ thô, tức là địa chỉ của đối tượng được trỏ đến
- Hàm release() để chuyển quyền sở hữu cho một con trỏ khác bằng cách đặt con trỏ hiện tại thành NULL và trả về địa chỉ vùng nhớ để gán vào con trỏ khác.
- Hàm reset() giải phóng đối tượng hiện tại khi không co tham số truyền vào hoặc quản lý đối tượng mới.
```cpp
        /**
         * @brief   Move constructor chuyển nhượng quyền sở hữu con trỏ.
         * @param   other   Đối tượng 'UniquePointer' cần chuyển nhượng quyền sở hữu.
         */
        UniquePointer(UniquePointer &&other) : ptr(other.ptr)
        {
            other.ptr = nullptr;
        }


        /**
         * @brief   move assignment operator - Toán tử gán chuyển nhượng quyền sở hữu.
         * @param   other   Đối tượng 'UniquePointer' cần chuyển nhượng quyền sở hữu.
         */
        UniquePointer& operator = (UniquePointer &&other)
        {
            if (this != &other)
            {
                // giải phóng đối tượng hiện tại
                if (this->ptr) delete ptr;

                // chuyển quyền sở hữu
                this->ptr = other.ptr;
                other.ptr = nullptr;
            }

            return *this;
        }
```

Có hai cách chuyển quyền sỡ hữu con trỏ đến một đối tượng khác: Move Constructor và Move Assignment operator. Cả hai đều chuyển con trỏ tới một đối tượng được quản lý bởi con trỏ khác sau đó xóa con trỏ đó. Nhưng khác nhau về cách thực thi giữa Constructor và phép gán.

Kiểm tra:
```
/* sử dụng move semantic để chuyển quyền sở hữu */
UniquePointer<int> uptr2(move(uptr1));

/* sử dụng move assignment operator để chuyển quyền sở hữu */
UniquePointer<int> uptr3;
uptr3 = move(uptr2);
```

#### Shared Pointed
shared_ptr là một Smart pointer khác trong C++ và cũng giúp quản lý bộ nhớ động. Điểm đặc biệt của shared_ptr là nó sử dụng một bộ đếm tham chiếu để theo dõi số lượng shared_ptr đang tham chiếu đến một đối tượng, và chỉ giải phóng bộ nhớ khi không còn shared_ptr nào tham chiếu đến nó. Tức là nó cho phép một vùng nhớ được sở hữu bởi nhiều con trỏ khác nhau.

Khác với Unique Pointer, Share Pointer có thêm một thuộc tính khác là bộ đếm tham chiếu
```cpp
T *ptr;              /**< Con trỏ thô đến đối tượng được quản lý. */
size_t *ref_count;   /**< Bộ đếm tham chiếu. */
```
Bộ đếm này là một con trỏ vì nếu sử dụng biến thường thì mỗi khi khởi tạo một đối tượng sẽ cấp một vùng nhớ để lưu ```ref_count``` gây tiêu hao bộ nhớ và đếm không chính xác. Vì thế sử dụng con trỏ để chỉ trỏ đến một vùng nhớ duy nhất và cộng dồn giá trị này với mỗi đối tượng được khởi tạo.

**Constructor:**
```cpp
/**
* @brief Constructor khởi tạo SharedPointer.
* @param p Con trỏ thô đến đối tượng. Giá trị mặc định là nullptr.
*/
SharedPointer(T *p = nullptr) : ptr(p), ref_count(p ? new size_t(1) : nullptr){}
```
- Giá trị mặc định của ```p``` là ```nullptr```, tức là nếu không truyền tham số, SharedPointer sẽ không trỏ đến đối tượng nào.
- Nếu ```p``` khác ```nullptr```, cấp phát một ```size_t``` có giá trị 1 để đếm số tham chiếu.
- Nếu ```p``` là ```nullptr```, con trỏ ```ref_count``` cũng là ```nullptr```.

**Destructor:**

```cpp
void release_in()
{
    if (ref_count && --(*ref_count) == 0)
    {
        delete ptr;
        delete ref_count;
    }
}
~SharedPointer()
{
    release_in();
}
```
- Nếu ```ref_count = 0 hoặc 1``` thì khi giải phóng thì sẽ giải phóng vùng nhớ được trỏ đến và giải phóng vùng nhớ chứa ```ref_count```

**Copy Constructor:**
```cpp
/**
* @brief Copy constructor tăng bộ đếm tham chiếu.
* @param other Đối tượng SharedPointer cần sao chép.
*/
SharedPointer(const SharedPointer &other) : ptr(other.ptr), ref_count(other.ref_count)
{
    if (ref_count) (*ref_count)++;
}
```
Khi khởi tạo con trỏ mới bằng cách Copy con trỏ đã có để quản lý chung vùng nhớ, Với Unique Pointer thì sẽ xóa con trỏ hiện tại để con trỏ mới được quản lý. Nhưng với Shared Pointer, sẽ gán con trỏ mới bằng với giá trị con trỏ hiện có và chỉ định chung vùng nhớ của biến ```ref_count``` và cộng biến này lên 1.

**Toán tử gán**
```cpp
/**
* @brief  Giải phóng tài nguyên và trả về con trỏ thô hiện tại.
* @return Con trỏ thô đến đối tượng được quản lý trước khi giải phóng.
*/
T* release()
{
    T *temp = ptr;
    ptr = nullptr;
    if (ref_count && --(*ref_count) == 0)
    {
        delete ref_count;
        ref_count = nullptr;
    }
    return temp;
}

/**
* @brief  Toán tử gán bằng copy.
* @param  other Đối tượng SharedPointer cần sao chép.
* @return Tham chiếu đến đối tượng SharedPointer hiện tại.
*/
SharedPointer& operator = (const SharedPointer &other)
{
    if (this != &other)
    {
        release();
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ref_count) (*ref_count)++;
    }
    return *this;
}
```

- Kiểm tra hai con trỏ có khác nhau hay không để thực hiện phép gán
- Gọi hàm ```release()``` để giảm số lượng bộ đếm tham chiếu của vùng nhớ đang trỏ vào để đổi con trỏ sang vùng nhớ khác, nếu ```ref_count``` vùng nhớ hiện có không còn con trỏ nào quản lý thì giải phóng.
- Sau đó gán con trỏ hiện tại với con trỏ mới và tăng ```ref_count``` lên 1.

Test:
```cpp
// Khởi tạo Shared Pointer 1
    SharedPointer<int> sp1 = new int(100);
    cout << "sp1 value: " << *sp1 << ", count: " << sp1.use_count() << endl;


    // Khởi tạo Shared Pointer 2 (copy constructor)
    SharedPointer<int> sp2(sp1);
    cout << "sp2 value: " << *(sp2.get()) << ", count: " << sp2.use_count() << endl;


    // Khởi tạo Shared Pointer 3 (copy assignment operator)
    SharedPointer<int> sp3, sp4;
    sp4 = sp1;
    sp3 = sp1;
    cout << "sp3 value: " << *sp3 << ", count: " << sp3.use_count() << endl;

    
    // Khởi tạo Shared Pointer 4 trong Lambda sau khi thoát khỏi hàm sẽ bị thu hồi
    {
        SharedPointer<int> sp4 = sp2;
        cout << "sp4 value: " << *sp2 << ", count: " << sp1.use_count() << endl;
    }

    // Đếm số lượng shared pointer
    cout << "count: " << sp2.use_count() << endl;


    // Shared Pointer 1 & 2 không còn quản lý đối tượng
    sp1.reset();
    sp2.reset();


    // chuyển quyền sở hữu đối tượng cho con trỏ thô mới
    int *rawPtr = sp3.release();
    cout << "raw pointer: " << *rawPtr << endl;
    cout << "count Raw Pointer: " << sp3.use_count() << endl;
    
    cout << "count: " << sp1.use_count() << endl;
```

Kết quả:
```
sp1 value: 100, count: 1
sp3 value: 100, count: 4
sp4 value: 100, count: 5
count: 4
raw pointer: 100
count Raw Pointer: 1
count: 0
```

#### Weak Pointer

weak_ptr là một cơ chế giữ tham chiếu yếu (weak reference) đến một **đối tượng được quản lý bởi shared_ptr**. Nó cung cấp một cách an toàn để theo dõi một đối tượng mà **không tăng bộ đếm tham chiếu của shared_ptr**. weak_ptr không trực tiếp truy cập đến đối tượng (object) mà nó theo dõi. 

weak_ptr có một phương thức là lock(), mà trả về một shared_ptr. Nếu shared_ptr mà weak_ptr theo dõi vẫn tồn tại, lock() sẽ trả về một shared_ptr hợp lệ có thể sử dụng để truy cập đối tượng. Ngược lại, nếu shared_ptr đã bị giải phóng, lock() sẽ trả về một shared_ptr rỗng.

**Constructor:**
```cpp
/**
* @brief Constructor khởi tạo WeakPointer từ SharedPointer.
* @param shared Đối tượng SharedPointer.
*/
WeakPointer(const SharedPointer<T> &shared) : ptr(shared.get()), ref_count(nullptr)
{
    ref_count = shared.use_count() ? new size_t(shared.use_count()) : nullptr;
}
```
- Khởi tạo đối tượng mới từ Shared Pointer nhưng sẽ tạo một đối tượng mới ở vùng nhớ khác để chứa ```ref_count``` bằng 0 nếu shared pointer không quản lý đối tượng nào hoặc bằng ```ref_count``` của shared pointer nếu nó lớn hơn 0.

**Method expired**
```cpp
/**
* @brief  Kiểm tra xem WeakPointer có còn quản lý đối tượng không.
* @return true nếu đối tượng không tồn tại, false ngược lại.
*/
bool expired() const
{
    return !ref_count || *ref_count == 0;
}
```
Trả về true khi ```ref_count``` bằng 0 hoặc NULL. tức Weakpointer không còn quản lý đổi tượng nào.


**Method Lock**
```cpp
/**
* @brief  Chuyển WeakPointer thành SharedPointer nếu đối tượng còn tồn tại.
* @return SharedPointer đến đối tượng hoặc SharedPointer trống nếu đối tượng không còn tồn tại.
*/
SharedPointer<T> lock() const
{
    return expired() ? SharedPointer<T>(nullptr) : SharedPointer<T>(ptr);
}
```
Ép kiểu đối tượng hiện tại từ Weak Pointer thành Shared Pointed để có thể đọc giá trị.


Tất cả các Class trên được tích hợp trong thư viện **<memory>**

#### Một số phương thức mới:
- ```make_unique``` Tạo một đối tượng mới được quản lý bởi một Unique_Pointer
Ví dụ:
```cpp
unique_ptr<SpeedSensor> uptr = make_unique<SpeedSensor>(10);
unique_ptr<SpeedSensor> uptr1(new SpeedSensor(10));
```
Cả hai dòng lệnh trên có chung ý nghĩa


- Tương tự ta sẽ có ```make_shared```  
Ví dụ:
```
shared_ptr<int> sptr1 = make_shared<int>(20);
```
- Hoán đổi hai đối tượng
```cpp
shared_ptr<int> a = make_shared<int>(40);   // 0xa1
shared_ptr<int> b = make_shared<int>(50);   // 0xb3
a.swap(b);
```

Bây giờ ```b``` sẽ quản lý ```40``` và ```a``` sẽ quản lý ```50```

- ```a = move(b);```: Chuyển đối tượng được ```b``` quản lý sang ```a``` và ```b``` không còn quản lý đối tượng nào.

</details>
