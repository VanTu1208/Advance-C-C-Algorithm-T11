#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;          // Dữ liệu của nút
    struct Node *next; // Con trỏ đến nút tiếp theo trong danh sách, node đó cũng chứa dữ liệu và địa chỉ của con trỏ kết tiếp
} Node;

Node *createNode(int value) // Trả về địa chỉ node cấp phát từ hàm malloc (các địa chỉ được khởi tạo khác nhau)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node; // trả về địa chỉ
}

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

// Thêm Node vào cuối List
void push_back(Node **head, int value) // Con trỏ cấp 2 cho phép thay đổi địa chỉ trỏ tới của Node, thay đổi địa chỉ của Node
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

void push_front(Node **head, int value) // Con trỏ cấp 2 cho phép thay đổi địa chỉ trỏ tới của Node, thay đổi địa chỉ của Node
{
    printf("Push front node, Data: %d\n",value);
    Node *newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
}

// Thêm Node vào vị trí bất kỳ
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

void front(Node *head)
{
    if (head == NULL)
        printf("Node is not available\n");
    else
    {
        printf("Front Node: Data = %d, Addr = %p_______nextAddr = %p\n", head->data, head, head->next);
    }
}

// Thêm Node vào vị trí bất kỳ
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

int isEmpty(Node *head)
{
    if (head == NULL){
        printf("Node is not available\n");
        return 1;
    }
    return 0;
    
}


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
