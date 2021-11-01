/* trying to send/rec */
#include "rpi.h"
// #include "ir-tsop322.h"

enum { ir_eps = 200 };
// we should never get this.
enum { NOISE = 0 } ;

struct readings { unsigned usec, v; };

const char *key_to_str(unsigned x) {
    output("convert an input value to a string\n");
    switch(x) {
        case 501364706:
            return "->O";
        case 401094626:
            return "O->";
        case 367671266:
            return "x";
        case 467941346:
            return "UP";
        case 434517986:
            return "DOWN";
    }
    return "N/A";
}

// adapt your read_while_equal: return 0 if timeout passed, otherwise
// the number of microseconds + 1 (to prevent 0).
static int read_while_eq(int pin, int v, unsigned timeout) {
    unsigned startTime = timer_get_usec();
    while(1) {
        if (gpio_read(pin) != v) {  // Expected value found
            return (timer_get_usec() - startTime + 1);
        }
        if (timer_get_usec() - startTime >= timeout) {  // Timeout
            return 0;
        }
    }
}

// integer absolute value.
static int abs(int x) {
    return x < 0 ? -x : x; 
}

// return 1 if <t_expect> is within eps of <t_actual>
static int within(unsigned t_expect, unsigned t_actual, unsigned eps) {
    return abs(t_expect - t_actual) < eps;
}

// return 0 if e is within eps of lb, 1 if its within eps of ub
static int pick(struct readings *e, unsigned lb, unsigned ub) {
    if (e->usec >= lb - ir_eps && e->usec <= lb + ir_eps) {
        return 0;
    }
    if (e->usec >= ub - ir_eps && e->usec <= ub + ir_eps) {
        return 1;
    }
    panic("invalid time: <%d> expected %d or %d\n", e->usec, lb, ub);
}

// return 1 if is a skip: skip = delay of 550-/+eps
static int is_skip(struct readings *e) {
    if (within(e->usec, 550, ir_eps))
        return 1;
    return 0;
}

// header is a delay of 9000 and then a delay of 4500
int is_header(struct readings *r, unsigned n) {
    if(n < 2)
        return 0;

    if (within(9000, r[0].usec, ir_eps) && within(4500, r[1].usec, ir_eps)) {
        return 1;
    }

    return 0;
}

// convert <r> into an integer by or'ing in 0 or 1 depending on the time.
// assert that they are seperated by skips!
unsigned convert(struct readings *r, unsigned n) {
    if(!is_header(r,n))
        return NOISE;
    assert(n > 4);
    assert(is_skip(&r[2]));

    int i = 3;
    unsigned val = 0;


    for (; i < n; i++) {
        if (i % 2 == 0) {
            assert(is_skip(&r[i]));
        }
        else {
            if (pick(&r[i], 600, 1600))
                val |= 1 << i/2;
        }
    }

    return val;
}

static void print_readings(struct readings *r, int n) {
    assert(n);
    printk("-------------------------------------------------------\n");
    for(int i = 0; i < n; i++) {
        if(i) {
            assert(!is_header(r+i,n-i));
    }
        printk("\t%d: %d = %d usec\n", i, r[i].v, r[i].usec);
    }
    printk("readings=%d\n", n);
    if(!is_header(r,n))
        printk("NOISE\n");
    else
        printk("convert=%x\n", convert(r,n));
}

// read in values until we get a timeout, return the number of readings.  
static int get_readings(int in, struct readings *r, unsigned N) {
    unsigned timeout = 15000;
    unsigned startTime = timer_get_usec();
    unsigned readingsCounter = 0;
    int n,expect;
    for(n=expect=0; n<N; n++) {
        // is the input pin high or low?
        r[n].v = expect;
        r[n].usec = read_while_eq(in, expect, timeout);
        if (r[n].usec == 0)
            return readingsCounter;
        readingsCounter++;
        expect = 1 - expect;
    }
    return readingsCounter;
    panic("too many readings\n");
}

// initialize the pin.
int tsop_init(int input) {
    gpio_set_input(input);
    gpio_set_pullup(input);
    return 1;
}

void notmain(void) {
    int in = 21;
    tsop_init(in);
    output("about to start reading\n");

    while(1) {
        // wait until signal: or should we timeout?
        while(gpio_read(in))
            ;
#       define N 256
        static struct readings r[N];
        int n = get_readings(in, r, N);
        print_readings(r,n);  // TODO REMOVE

        output("done getting readings\n");
    
        unsigned x = convert(r,n);
        output("converted to %x\n", x);
        const char *key = key_to_str(x);
        if(key)
            printk("%s\n", key);
        else
            // failed: dump out the data so we can figure out what happened.
            print_readings(r,n);
    }
	printk("stopping ir send/rec!\n");
    clean_reboot();
}
