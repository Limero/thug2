// memcpy — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
//
// Original SN Systems ProDG newlib source (crashwoc decomp, runtime/libc).
// Compiles byte-exact against the THUG2 DOL (0x8026AE28, 0xA4) with the
// game's ngccc (ProDG 3.9.3). The *++dl/*++sl pre-increment idiom produces
// the stwu stores of the unrolled 16-byte loop.
#include "types.h"

typedef unsigned int size_t;

void* memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d;
    const unsigned char* s;
    unsigned long* dl;
    unsigned long* sl;

    d = (unsigned char*)dest;
    s = (const unsigned char*)src;

    if (n > 15 && (((unsigned long)s | (unsigned long)d) & 3) == 0) {
        dl = (unsigned long*)d;
        sl = (unsigned long*)s;

        while (n > 15) {
            *dl = *sl;
            n -= 16;
            *++dl = *++sl;
            *++dl = *++sl;
            *++dl = *++sl;
            dl++;
            sl++;
        }

        while (n > 3) {
            *dl++ = *sl++;
            n -= 4;
        }

        d = (unsigned char*)dl;
        s = (const unsigned char*)sl;
    }

    while (n-- != 0) {
        *d++ = *s++;
    }

    return dest;
}
