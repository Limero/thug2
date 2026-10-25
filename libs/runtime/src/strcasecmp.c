// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026B04C-0x8026B0E0 (148B). Byte-identical.
#include "types.h"
extern unsigned char _ctype_[];

int strcasecmp(const char* s1_in, const char* s2_in)
{
    register const char* s1 __asm__("r3") = s1_in;
    register const char* s2 __asm__("r4") = s2_in;
    int c1;
    int c2;
    int rc1;

    for (;;)
    {
        if (*s1 == '\0')
            break;

        c1 = *s1;
        if ((_ctype_ + 1)[c1] & 1)
            c1 += 0x20;

        c2 = *s2;
        if ((_ctype_ + 1)[c2] & 1)
            c2 += 0x20;

        if (c1 != c2)
            break;

        s1++;
        s2++;
    }

    rc1 = (unsigned char)*s1;
    if ((_ctype_ + 1)[rc1] & 1)
        rc1 += 0x20;

    c2 = (unsigned char)*s2;
    if ((_ctype_ + 1)[c2] & 1)
        c2 += 0x20;

    return rc1 - c2;
}
