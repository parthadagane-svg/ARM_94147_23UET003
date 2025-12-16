#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint8_t value = 5;          

    uint8_t leftShifted  = value << 2;  
    uint8_t rightShifted = value >> 1;  

    printf("Original value: %u\n", value);
    printf("After left shift by 2: %u\n", leftShifted);
    printf("After right shift by 1: %u\n", rightShifted);

    return 0;
}
