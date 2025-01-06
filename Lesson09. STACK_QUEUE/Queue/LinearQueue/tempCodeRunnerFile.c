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