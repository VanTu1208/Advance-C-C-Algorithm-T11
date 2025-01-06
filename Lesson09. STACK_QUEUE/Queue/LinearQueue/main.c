#include <stdio.h>
#include <stdlib.h>


typedef struct Queue {
    int* items;
    int size;
    int front;
    int rear;
} Queue;

void initialize(Queue *queue, int size) 
{
    queue->items = (int*) calloc(size,sizeof(int));
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
}

int is_empty(Queue queue) {
    return (queue.front == -1 || queue.rear == -1);
}

int is_full(Queue queue) {
    return queue.rear == queue.size - 1;
}

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


