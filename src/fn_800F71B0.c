// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F71B0-0x800F7280 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8029C0B4[];
extern f32 lbl_8029C0B8;

bool fn_800F71B0(f32 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7) {
    f32 t0;
    f32 t2;
    f32 zero1;
    f32 num12;
    f32 num13;
    f32 num11;
    f32 zero2;
    register f32 abs12 __asm__("fr13");
    f32 eps;
    register s32 eps_addr __asm__("r9");
    char *out;

    t0 = farg7 * farg2;
    __asm__ volatile("" : "+f"(t0));
    zero1 = lbl_8029C0B8;
    farg5 = farg1 - farg5;
    __asm__ volatile("" : "+f"(farg5));
    farg3 = -farg3;
    __asm__ volatile("" : "+f"(farg3));
    __asm__ volatile("mr %0,%1" : "=r"(out) : "r"(arg0));
    t2 = farg5 * farg2;
    __asm__ volatile("" : "+f"(t2));
    farg4 = farg0 - farg4;
    __asm__ volatile("" : "+f"(farg4));
    num12 = (farg6 * farg3) + t0;
    __asm__ volatile("" : "+f"(num12));
    farg7 = -farg7;
    __asm__ volatile("" : "+f"(farg7));
    farg5 = farg5 * farg6;
    __asm__ volatile("" : "+f"(farg5));
    num13 = (farg4 * farg3) + t2;
    __asm__ volatile("" : "+f"(num13));
    num11 = (farg4 * farg7) + farg5;
    __asm__ volatile("" : "+f"(num11));

    if (num12 > zero1) {
        if (num11 < zero1) {
            return false;
        }
        if (num11 > num12) {
            __asm__ __volatile__("");
            return false;
        }
        goto block_6;
    }
    if (num11 > zero1) {
        return false;
    }
    if (num11 < num12) {
        return false;
    }
block_6:
    zero2 = lbl_8029C0B8;
    if (num12 > zero2) {
        if (num13 < zero2) {
            return false;
        }
        if (num13 > num12) {
            __asm__ __volatile__("");
            return false;
        }
        goto block_12;
    }
    if (num13 > zero2) {
        return false;
    }
    if (num13 < num12) {
        return false;
    }
block_12:
    __asm__ volatile("lis %0,%1@ha" : "=r"(eps_addr) : "s"(lbl_8029C0B4));
    __asm__ volatile("fabs %0,%1" : "=f"(abs12) : "f"(num12));
    __asm__ volatile("lfs %0,%1@l(%2)" : "=f"(eps) : "s"(lbl_8029C0B4), "r"(eps_addr));
    if (abs12 < eps) {
        *(f32 *)out = lbl_8029C0B8;
        return true;
    }
    *(f32 *)out = num11 / num12;
    return true;
}
