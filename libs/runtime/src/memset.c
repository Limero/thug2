// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026AFB8-0x8026B04C (148B). Byte-identical.
#include "types.h"
typedef unsigned int size_t;

void* memset(void* dest, int c, size_t count)
{
    register unsigned long fill __asm__("r0");
    unsigned char* p;
    unsigned long* aligned_p;

    p = (unsigned char*)dest;

    if (count > 3 && (((unsigned long)dest & 3) == 0)) {
        c &= 0xFF;
        aligned_p = (unsigned long*)dest;
        fill = (c << 8) | c;
        fill |= fill << 16;
        __asm__ volatile("" ::: "memory");

        if (count > 15) {
            do {
                *aligned_p = fill;
                count -= 16;
                *++aligned_p = fill;
                *++aligned_p = fill;
                *++aligned_p = fill;
                aligned_p++;
            } while (count > 15);
        }

        while (count > 3) {
            *aligned_p++ = fill;
            count -= 4;
        }

        p = (unsigned char*)aligned_p;
    }

    while (count-- != 0) {
        *p++ = c;
    }

    return dest;
}
