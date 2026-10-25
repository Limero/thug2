// strcpy — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
//
// Original SN Systems ProDG newlib source (crashwoc decomp, runtime/libc).
// Compiles byte-exact against the THUG2 DOL (0x8026B2B4, 0x84) with the
// game's ngccc (ProDG 3.9.3). DETECTNULL word copy + byte copy tail.
#include "types.h"

typedef unsigned int size_t;

#define DETECTNULL(X) (((X) - 0x01010101) & ~(X) & 0x80808080)

char *strcpy(char *dst0, const char *src0) {
    char *dst = dst0;
    const char *src = src0;
    unsigned long *aligned_dst;
    const unsigned long *aligned_src;

    if (!(((unsigned long)src | (unsigned long)dst) & 3)) {
        aligned_dst = (unsigned long *)dst;
        aligned_src = (const unsigned long *)src;

        while (!DETECTNULL(*aligned_src)) {
            *aligned_dst++ = *aligned_src++;
        }

        dst = (char *)aligned_dst;
        src = (const char *)aligned_src;
    }

    while ((*dst++ = *src++) != '\0')
        ;

    return dst0;
}
