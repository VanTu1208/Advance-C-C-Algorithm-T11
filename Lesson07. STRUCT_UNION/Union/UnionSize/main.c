#include <stdio.h>
#include <stdint.h>

typedef union {
    uint8_t arr1[5];
    uint32_t arr2[4]; 
    uint16_t arr3[10]; 
} Container;

int main(int argc, char const *argv[])
{
    printf("Size of Container: %d\n",sizeof(Container));

    //printf("Size of ContainerArr: %d\n",sizeof(ContainerArr));
    return 0;
}

