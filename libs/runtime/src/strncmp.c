// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026B3A4-0x8026B484 (224B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
typedef unsigned int size_t;

#define UNALIGNED(X, Y) \
    ((((long)(X)) & (sizeof(long) - 1)) | (((long)(Y)) & (sizeof(long) - 1)))
#define DETECTNULL(X) (((X) - QB_SWAR_ONES) & ~(X) & QB_UNKNOWN_0x80808080)

int strncmp(const char* s1, const char* s2, size_t n)
{
    unsigned long* a1;
    unsigned long* a2;
    int t;

    if (n == 0)
        return 0;

    if (!UNALIGNED(s1, s2))
    {
        a1 = (unsigned long*)s1;
        a2 = (unsigned long*)s2;
        while (n >= sizeof(unsigned long) && *a1 == *a2)
        {
            n -= sizeof(unsigned long);
            if (n == 0 || DETECTNULL(*a1))
                return 0;
            a1++;
            a2++;
        }
        s1 = (char*)a1;
        s2 = (char*)a2;
    }

    while (1)
    {
        t = n--;
        if (t == 0)
            break;
        if (*(const unsigned char*)s1 != *(const unsigned char*)s2)
            break;
        if (n == 0 || *s1 == '\0')
            return 0;
        s1++;
        s2++;
    }

    return (*(const unsigned char*)s1 - *(const unsigned char*)s2);
}
