// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80270CA4-0x80270D9C (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

union U70CA4 { f32 f; s32 i; };

// sqrtf @ 0x80270CA4
f32 sqrtf(f32 farg0) {
    union U70CA4 sp8;
    f32 res;
    s32 i;
    s32 m;
    s32 k;
    s32 j;
    s32 b;
    register s32 a __asm__("r10");
    s32 c;
    s32 t1;
    s32 cst;
    s32 t2;
    s32 t3;

    sp8.f = farg0;
    i = sp8.i;
    m = i;
    __asm__("" : "+r"(m));
    __asm__ volatile("rlwinm %0,%1,0,1,8" : "=r"(t1) : "r"(m));
    __asm__ volatile("lis %0,0x7f80" : "=r"(cst));
    if (t1 == cst) {
        return farg0 * farg0 + farg0;
    }
    if (m <= 0) {
        if ((m & 0x7FFFFFFF) == 0) {
            return farg0;
        }
        if (m < 0) {
            res = farg0 - farg0;
            return res / res;
        }
    }
    k = i >> 0x17;
    if (k == 0) {
        c = 0;
        if (!(m & 0x00800000)) {
            do {
                m <<= 1;
                c += 1;
            } while (!(m & 0x00800000));
        }
        k = 1 - c;
    }
    t2 = m & 0x7FFFFF;
    k -= 0x7F;
    m = t2 | 0x800000;
    if (k & 1) {
        m += m;
    }
    k >>= 1;
    m += m;
    j = 0;
    b = 0;
    a = 0x01000000;
    do {
        t3 = j + a;
        if (t3 <= m) {
            j = t3 + a;
            b += a;
            m -= t3;
        }
        m += m;
        a = a / 2U;
    } while (a != 0);
    if (m != 0) {
        b += b & 1;
    }
    m = b >> 1;
    k <<= 0x17;
    m += 0x3F000000;
    t3 = m + k;
    __asm__("" : "+r"(t3));
    sp8.i = t3;
    res = sp8.f;
    return res;
}
