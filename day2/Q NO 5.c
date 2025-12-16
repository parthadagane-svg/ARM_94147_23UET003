#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint8_t reg = 0xAA;   
    uint8_t field;

    printf("Initial register: 0x%02X\n", reg);

    
    field = (reg >> 2) & 0x07;   
    printf("Bits 2 to 4 (read): 0b%03b (%u)\n", field, field);

    
    reg &= ~(0x07 << 2);         
    reg |=  (0x03 << 2);         

    printf("Modified register: 0x%02X\n", reg);

    return 0;
}
