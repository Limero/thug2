// floor — SN ProDG newlib fdlibm (byte-exact, ngccc -O2 -G0).
//
// Identified: fdlibm/newlib floor() — IEEE-754 floor via hi/lo bit twiddling
// with 1e300 (lbl_802B21E0) as the "huge" threshold and 0.0 (lbl_802B21E8)
// compare operand.
// NOTE: the game carries a second floor copy in its own math lib
// (src/fn_80270290.c, .sdata constants); this one is newlib's (rodata2).
// range 0x8026E5DC-0x8026E750 (372B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern const f64 lbl_802B21E0;
extern const f64 lbl_802B21E8;
f64 floor(f64 x) {
    union {
        f64 d;
        struct { s32 hi, lo; } w;
    } u;
    register s32 i0 __asm__("r10");
    register s32 i1 __asm__("r6");
    register s32 je __asm__("r5");
    u32 i, j;

    register s32 hi __asm__("r9");
    register s32 lo __asm__("r10");
    u.d = x;
    __asm__ volatile("lwz %0, 8(%%r1)" : "=r"(hi));
    __asm__ volatile("lwz %0, 0xc(%%r1)" : "=r"(lo));
    i1 = lo;
    i0 = hi;
    je = ((i0 >> 20) & 0x7ff) - 0x3ff;
    if (je < 20) {
        if (je < 0) {
            if (x + lbl_802B21E0 > lbl_802B21E8) {
                if (i0 >= 0) {
                    i1 = 0;
                    i0 = 0;
                } else {
                    if (((i0 & QB_UNKNOWN_0x7FFFFFFF) | i1) != 0) {
                        i0 = -QB_UNKNOWN_0x40100000;
                        i1 = 0;
                    }
                }
            }
        } else {
            i = QB_UNKNOWN_0x000FFFFF >> je;
            if (((i0 & i) | i1) == 0) {
                return x;
            }
            if (x + lbl_802B21E0 > lbl_802B21E8) {
                if (i0 < 0) {
                    i0 += QB_UNKNOWN_0x00100000 >> je;
                }
                i0 &= ~i;
                i1 = 0;
            }
        }
    } else if (je > 51) {
        if (je == 0x400) {
            return x + x;
        }
        return x;
    } else {
        i = 0xffffffffu >> (je - 20);
        if ((i1 & i) == 0) {
            return x;
        }
        if (x + lbl_802B21E0 > lbl_802B21E8) {
            if (i0 < 0) {
                if (je == 20) {
                    i0 += 1;
                } else {
                    { register s32 sh __asm__("r9") = 52 - je; j = i1 + (1 << sh); }
                    if (j < (u32)i1) {
                        i0 += 1;
                    }
                    i1 = j;
                }
            }
            i1 &= ~i;
        }
    }
    u.w.hi = i0;
    u.w.lo = i1;
    return u.d;
}
