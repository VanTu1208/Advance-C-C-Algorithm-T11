#include <stdio.h>
#include <stdint.h>

typedef struct{
    uint8_t  mem1;
    uint32_t mem3;
    uint16_t mem2;
    
} Container;


typedef struct{
    uint8_t arr1[12];
    uint32_t arr2[4]; 
    uint16_t arr3[3]; 
    uint64_t arr4[1];

} ContainerArr;

int main(int argc, char const *argv[])
{
    printf("Size of Container: %d\n",sizeof(Container));

    printf("Size of ContainerArr: %d\n",sizeof(ContainerArr));
    return 0;
}

