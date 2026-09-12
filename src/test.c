#include <stdio.h>

int main() {
    // 1. Receive the number as a decimal
    // Example: 11189196 (which is 0xAABBCC in hex)
    unsigned int decimalNum = 11189196;

    // 2. Extract three 8-bit parts from the 24-bit total field
    unsigned char part1 = (decimalNum >> 16) & 0xFF; // Leftmost 8 bits
    unsigned char part2 = (decimalNum >> 8) & 0xFF;  // Middle 8 bits
    unsigned char part3 = (decimalNum) & 0xFF;       // Rightmost 8 bits

    // 3. Print the results converted directly to octal
    printf("Input Decimal: %u\n\n", decimalNum);
    
    // We use %o to print each 8-bit part as base-8 (octal)
    printf("Part 1 (Octal): %o\n", part1);
    printf("Part 2 (Octal): %o\n", part2);
    printf("Part 3 (Octal): %o\n", part3);

    return 0;
}
