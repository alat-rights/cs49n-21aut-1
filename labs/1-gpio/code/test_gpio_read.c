#include <stdio.h>

int main() {

    unsigned v = 0;
    unsigned bits = 0b00100100110;
    unsigned bitmask = 0b1 << 4;
    v = ((bits & bitmask) > 0b0);
    printf("%u", v);
    return v;
}
