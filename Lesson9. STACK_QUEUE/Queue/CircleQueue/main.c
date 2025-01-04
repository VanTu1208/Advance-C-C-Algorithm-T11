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


