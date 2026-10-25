// strlen — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
//
// Original SN Systems ProDG newlib source (crashwoc decomp, runtime/libc).
// Compiles byte-exact against the THUG2 DOL (0x8026B338, 0x6C) with the
// game's ngccc (ProDG 3.9.3). The 0x01010101/0x80808080 bit-trick word
// scan via an unsigned long* pins the andc/and. register allocation.
#include "types.h"

typedef unsigned int size_t;

#define DETECTNULL(X) (((X) - 0x01010101) & ~(X) & 0x80808080)

size_t strlen(const char *str) {
    const char *start = str;
    unsigned long *aligned_addr;

    if (((unsigned long)str & 3) == 0) {
        aligned_addr = (unsigned long *)str;
        if (!DETECTNULL(*aligned_addr)) {
            do {
                aligned_addr++;
            } while (!DETECTNULL(*aligned_addr));
        }
        str = (const char *)aligned_addr;
    }

    while (*str) {
        str++;
    }

    return str - start;
}
