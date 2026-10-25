// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026AECC-0x8026AFB8 (236B). Byte-identical.
#include "types.h"
typedef unsigned int size_t;

void* memmove(void* dst_void, const void* src_void, size_t n)
{
    char* dst = dst_void;
    const char* src = src_void;
    unsigned long* aligned_dst;
    const unsigned long* aligned_src;
    size_t n2 = n;

    if (src < dst && dst < src + n2)
    {
        src += n2;
        dst += n2;
        while (n2--)
            *--dst = *--src;
    }
    else
    {
        if (n > 15 && ((((unsigned long)src) | ((unsigned long)dst)) & 3) == 0)
        {
            aligned_dst = (unsigned long*)dst;
            aligned_src = (const unsigned long*)src;

            do {
                *aligned_dst = *aligned_src;
                n2 -= 16;
                *++aligned_dst = *++aligned_src;
                *++aligned_dst = *++aligned_src;
                *++aligned_dst = *++aligned_src;
                aligned_dst++;
                aligned_src++;
            } while (n2 > 15);

            while (n2 > 3)
            {
                *aligned_dst++ = *aligned_src++;
                n2 -= 4;
            }

            dst = (char*)aligned_dst;
            src = (const char*)aligned_src;
        }

        while (n2--)
            *dst++ = *src++;
    }

    return dst_void;
}
