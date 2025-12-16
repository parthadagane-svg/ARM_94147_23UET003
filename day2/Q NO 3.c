#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint16_t reg = 0xABCD;
    uint8_t lower_4_bits = reg & 0x000F;
    
    uint8_t upper_4_lower_byte = (reg & 0x00F0) >> 4;

    printf("Register value            : 0x%04X\n", reg);
    printf("Lower 4 bits               : 0x%X\n", lower_4_bits);
    printf("Upper 4 bits of lower byte : 0x%X\n", upper_4_lower_byte);

    return 0;
}
