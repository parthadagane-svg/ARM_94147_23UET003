#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint8_t reg = 0x2A; // 0010 1010

    // Set bit 4
    reg |= (1 << 4);
    printf("After setting bit 4:  0x%02X  (00111010)\n", reg);

    // Clear bit 1
    reg &= ~(1 << 1);
    printf("After clearing bit 1: 0x%02X  (00111000)\n", reg);

    // Toggle bit 5
    reg ^= (1 << 5);
    printf("After toggling bit 5: 0x%02X  (00011000)\n", reg);

    return 0;
}
