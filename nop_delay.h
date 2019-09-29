#ifndef NOP_DELAY_H
#define NOP_DELAY_H

/* we're bit-banging the LED commands, and it's easiest (though
 * not nice) to just use a variable number of no-op instructions
 * to achieve the delay... this header provides some easy-access
 * and variable length delays */

#define NOP5()   { asm("nop;nop;nop;nop;nop"); }
#define NOP10()  { NOP5();  NOP5();  }
#define NOP20()  { NOP10(); NOP10(); }
#define NOP40()  { NOP20(); NOP20(); }
#define NOP80()  { NOP40(); NOP40(); }
#define NOP160() { NOP80(); NOP80(); }
#define NOP320() { NOP160(); NOP160(); }

#endif /* NOP_DELAY_H */
