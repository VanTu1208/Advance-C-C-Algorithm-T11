#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

void swap(int *a, int *b)
{

    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void generateRandom(int *arr, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100; 
    }
}

int main()
{
    int n, x, i;
    printf("Nhap so phan tu cua mang: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    
    generateRandom(arr, n);

    printArray(arr, n);

    bubbleSort(arr, n);

    printArray(arr, n);

    printf("Nhap gia tri can tim: ");
    scanf("%d", &x);

    int result = binarySearch(arr, 0, n - 1, x);

    if (result == -1)
        printf("Khong tim thay gia tri!");
    else
        printf("Gia tri %d nam tai Arr[%d]", x, result);
    
    free(arr);
    return 0;
}