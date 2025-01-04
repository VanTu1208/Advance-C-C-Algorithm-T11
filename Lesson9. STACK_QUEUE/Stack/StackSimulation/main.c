#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct {
    int* items; //mảng lưu giá trị các phần tử
    int size; // số lượng phần tử tối đa của stack
    int top; // chỉ số lấy giá trị ở đỉnh Stack
} Stack;

void initialize( Stack *stack, int size) { // Hàm khởi tạo 1 Stack, truyền vào tham số là con trỏ để trỏ đến địa chỉ của stack (cấu hình trực tiếp)
    stack->items = (int*) calloc(size,sizeof(int)); //Tạo mảng động lưu trữ giá trị của Stack, khởi tạo giá trị 0 cho các phần tử
    stack->size = size;
    stack->top = -1; // Khởi tạo giá trị chỉ số cho Stack (khi rỗng)
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


