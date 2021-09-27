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
    // what is the address of fsel0?
    unsigned addr = GPIO_BASE + pin / 10; // Calculate address based on pin
    unsigned first_bit_location = ( pin % 10 ) * 3; // Where do we start writing?
    unsigned bits_to_write = 0b001 >> first_bit_location; // looks like 000[...]001
    unsigned bitmask = 0xFF & ~(0b111 >> first_bit_location); // 32 1s with three 0s where we want them

    PUT32(addr, bits_to_write & bitmask);
}

// set GPIO <pin> on.
void gpio_set_on(unsigned pin) {
    // implement this
    // use <gpio_set0>
}

// set GPIO <pin> off
void gpio_set_off(unsigned pin) {
    // implement this
    // use <gpio_clr0>
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
    // implement.
}

// return the value of <pin>
int gpio_read(unsigned pin) {
    unsigned v = 0;

    // implement.
    return v;
}
