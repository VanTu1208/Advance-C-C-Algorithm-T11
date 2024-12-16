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