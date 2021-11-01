/*
 * Implement the following routines to set GPIO pins to input or output,
 * and to read (input) and write (output) them.
 *
 * DO NOT USE loads and stores directly: only use GET32 and PUT32
 * to read and write memory.  Use the minimal number of such calls.
 *
 * See rpi.h in this directory for the definitions.
 */
#include "rpi.h"

// see broadcomm document for magic addresses.
#define GPIO_BASE 0x20200000

// do not read or write these directly --- only use put32 and get32
// (defined in start.S)
static volatile unsigned *gpio_fsel0 = (void*)(GPIO_BASE + 0x00);
static volatile unsigned *gpio_set0  = (void*)(GPIO_BASE + 0x1C);
static volatile unsigned *gpio_clr0  = (void*)(GPIO_BASE + 0x28);


//
// Part 1 implement gpio_set_on, gpio_set_off, gpio_set_output
//

// set <pin> to be an output pin.
//
// note: fsel0, fsel1, fsel2 are contiguous in memory, so you
// can (and should) use array calculations!
void gpio_set_output(unsigned pin) {  // pin is GPIO # on Rpi
    if (pin >= 32)
        return;

    // what is the address of fsel0?
    volatile unsigned *addr = gpio_fsel0 + pin / 10; // Contiguous 32-bit regions
    unsigned value = get32(addr); // Get 32 bits from the address

    unsigned first_bit_location = pin % 10 * 3; // Where do we start writing?
    unsigned bitmask = 0b111 << first_bit_location;

    unsigned masked_value = ~( ~value | bitmask );
    unsigned bits_to_write = 0b001 << first_bit_location; // looks like [001]000... Pg. 92: 001 = output

    put32(addr, bits_to_write | masked_value);
}

// set GPIO <pin> on.
void gpio_set_on(unsigned pin) {
    // use <gpio_set0>
    volatile unsigned *addr = gpio_set0;
    if (pin >= 32)
        return;
    put32(addr, 1 << pin);
}

// set GPIO <pin> off
void gpio_set_off(unsigned pin) {
    // use <gpio_clr0>
    volatile unsigned *addr = gpio_clr0;
    if (pin >= 32)
        return;
    put32(addr, 1 << pin);
}

// set <pin> to <v> (v \in {0,1})
void gpio_write(unsigned pin, unsigned v) {
    if (v)
        gpio_set_on(pin);
    else
        gpio_set_off(pin);
}

//
// Part 2: implement gpio_set_input and gpio_read
//

// set <pin> to input.
void gpio_set_input(unsigned pin) {
    if (pin >= 32)
        return;
    volatile unsigned *addr = gpio_fsel0 + pin / 10;
    unsigned value = get32(addr); // get 32 bits from the address

    unsigned first_bit_location = pin % 10 * 3; // where do we start writing?
    unsigned bitmask = 0b111 << first_bit_location;

    unsigned masked_value = ~( ~value | bitmask );

    put32(addr, masked_value);
}

// return the value of <pin>
int gpio_read(unsigned pin) {
    if (pin >= 32)
        return -1;
    unsigned v = 0;
    volatile unsigned *addr = (void *)(GPIO_BASE + 0x34);
    unsigned bits = get32(addr);
    unsigned bitmask = 0b1 << pin;
    v = ((bits & bitmask) > 0b0);
    return v;
}

void gpio_set_function(unsigned pin, gpio_func_t function) {
    if (pin >= 32 || !(0 <= function && function <= 7))
        return;
    volatile unsigned *addr = gpio_fsel0 + pin / 10;
    unsigned value = get32(addr); // get 32 bits from the address

    unsigned first_bit_location = pin % 10 * 3; // where do we start writing?
    unsigned bitmask = 0b111 << first_bit_location;

    unsigned masked_value = ~( ~value | bitmask );

    put32(addr, function << first_bit_location | masked_value);

}
