#include <stdio.h>

int main()
{
    int pin = 21;
    unsigned value = 0b00101101001;
    unsigned first_bit_location = pin % 10 * 3; // where do we start writing?
    unsigned bitmask = 0b111 << first_bit_location;

    unsigned masked_value = ~( ~value | bitmask );
    printf("%u", masked_value);
}
