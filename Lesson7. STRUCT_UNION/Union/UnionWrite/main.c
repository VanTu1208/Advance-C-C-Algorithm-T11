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
                    //val1 =   00000000 00000000 00000000 01010101
                    //val3 =   00000000 00000000 10010101 01010101

    printf("Dia chi bien 1: %p        Gia tri bien 1: %d\n",&group1.val1 ,group1.val1);
    printf("Dia chi bien 2: %p        Gia tri bien 2: %d\n",&group1.val2 ,group1.val2);
    printf("Dia chi bien 3: %p        Gia tri bien 3: %d\n",&group1.val3 ,group1.val3);
    return 0;
}

