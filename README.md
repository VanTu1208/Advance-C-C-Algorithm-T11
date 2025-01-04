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
Stack (ngăn xếp) là một cấu trúc dữ liệu tuân theo nguyên tắc "Last In, First Out" (LIFO), nghĩa là phần tử cuối cùng được thêm vào stack sẽ là phần tử đầu tiên được lấy ra.

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






















