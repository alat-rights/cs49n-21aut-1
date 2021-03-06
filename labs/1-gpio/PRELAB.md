### Always obey the first rule of PI-CLUB

  - ***IF YOUR PI GETS HOT TO THE TOUCH: UNPLUG IT***  
  - ***IF YOUR PI GETS HOT TO THE TOUCH: UNPLUG IT***  
  - ***IF YOUR PI GETS HOT TO THE TOUCH: UNPLUG IT***  
  - ***IF YOUR PI GETS HOT TO THE TOUCH: UNPLUG IT***  
  - ***IF YOUR PI GETS HOT TO THE TOUCH: UNPLUG IT***  

You likely have a short somewhere and in the worst-case can fry your laptop.

---------------------------------------------------------------------
### Reading before lab:

  1. Read throuh `Part 0` of the lab (in the [README.md](README.md))
     to get a big-picture background of how the r/pi (and many computer
     systems) control devices.


  2. After doing so, read through pages 4--7 and 91---96 of the broadcom
     document (`../../docs/BCM2835-ARM-Peripherals.annot.pdf`) to see what
     memory addresses to read and write to get the GPIO pins to do stuff.

     Note 1: this is a low-level hardware document.  You will almost
     certainly be missing key bits of context and so it will seem
     confusing.  This is normal!  Just skim what you don't understand
     and try to pull out what you can.  We will cover the necessary
     pieces in class.

     As discussed in `Part 0` of the lab, your specific goal is to figure
     out how to configure GPIO pin 20 (the second from the bottom right
     pin sticking up from the r/pi when orientated with pins on the right)
     to be either an output pin (e.g., that can blink an led) or an
     input pin (that detects when it is receiving a voltage `>= 3.3v`).
     In the former case you want to figure out how to turn the pin off
     and on.  In the latter you want to read it if it is off or on.

     The general game here (and with most hardware) is that each pin has
     a set of associated memory addresses (confusingly called `registers`
     in the Broadcom document) that you have to write magic values to
     to configure, and then read/write magic values to do input and
     output on.  Your fetchquest is to chase down what addresses these
     are for GPIO pin 20, and what values you need.

  3. Most hardware descriptions have errors and the broadcom chip is no
     exception.  One nice thing about it is that people have gone through
     it relatively carefully, and written up the errors 
     ([errata](https://elinux.org/BCM2835_datasheet_errata).  You should
     read through this to get a feel for the mistakes often made, especially
     for any pages we read now or later.


  4. Look through the `code` directory.  You'll be implementing the
     routines in `gpio.c` which is used by three simple programs: `1-blink.c`
     `2-blink.c` and `3-input.c`.  You only modify `gpio.c`.  We provide
     prototypes (in `rpi.h`) and some trivial assembly routines in
     `start.S`.

  5. Note: where the broadcom document uses addresses `0x7420xxxx`, you'll use
     `0x2020xxxx`.

Questions you should be able to answer:

  0. Where are `put32` and `get32` defined?
  1. Write out the call to `put32` that will set GPIO pin 20 to be an
     output pin (i.e., give the address and expression used as arguments).
  2. Write out the call to `put32` that will set GPIO pin 20 to be an
     input pin (i.e., give the address and expression used as arguments).
  3. Write out the call to `get32` to determine what value is held in
     GPIO pin 21.
