// strcat — SN ProDG newlib runtime (byte-exact, ngccc -O2 -G0).
//
// Original SN Systems ProDG newlib source (crashwoc decomp, runtime/libc).
// Compiles byte-exact against the THUG2 DOL (0x8026B0E0, 0x90) with the
// game's ngccc (ProDG 3.9.3). DETECTNULL scan for the end of s1, then a
// call to strcpy (wired at 0x8026B2B4).
#include "types.h"

typedef unsigned int size_t;

char *strcpy(char *dst0, const char *src0);

#define ALIGNED(X) (((long)(X) & (sizeof(long) - 1)) == 0)
#define DETECTNULL(X) (((X) - 0x01010101) & ~(X) & 0x80808080)

char* strcat(char* s1, const char* s2)
{
    char* s = s1;

    /* Skip over the data in s1 as quickly as possible. */
    if (ALIGNED(s1)) {
        unsigned long* aligned_s1 = (unsigned long*)s1;
        while (!DETECTNULL(*aligned_s1))
            aligned_s1++;
        s1 = (char*)aligned_s1;
    }

    while (*s1)
        s1++;

    strcpy(s1, s2);
    return s;
}
