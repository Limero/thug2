// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80273268-0x80273384 (284B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
// Identity: scalbnf/ldexpf (fdlibm family) — scales f32 x by 2^n.
// Suggested rename: scalbnf (or ldexpf)
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_803CA950; /* two25  = 33554432.0f */
extern f32 lbl_803CA954; /* tiny   ~ 1e-30f      */
extern f32 lbl_803CA958; /* huge   ~ 1e+30f      */
extern f32 lbl_803CA95C; /* twom25 = 2**-25      */

f32 fn_80273384(f32 a, f32 b); /* copysignf */

f32 fn_80273268(f32 x, s32 n) {
    register f32 vf2 __asm__("fr2");
    f32 sp8;
    register f32 tf __asm__("fr0");
    register f32 tf2 __asm__("fr1");
    register u32 var_r11 __asm__("r11");
    u32 tr;
    u32 nb;
    s32 k;

    vf2 = x;
    __asm__("fmr %0,%1" : "=f"(tf) : "f"(vf2));
    sp8 = tf;
    tr = *(u32 *) &sp8;
    __asm__("mr %0,%1" : "=r"(var_r11) : "r"(tr));
    k = (var_r11 >> 23) & 0xff;
    if (k == 0) {
        if ((var_r11 & QB_UNKNOWN_0x7FFFFFFF) == 0) {
            return x;
        }
        vf2 = vf2 * lbl_803CA950;
        __asm__("fmr %0,%1" : "=f"(tf) : "f"(vf2));
        sp8 = tf;
        tr = *(u32 *) &sp8;
        __asm__("mr %0,%1" : "=r"(var_r11) : "r"(tr));
        k = (var_r11 >> 23) & 0xff;
        {
            s32 t;
            __asm__ volatile("lis %0,-1\n\taddi %1,%1,-25\n\tori %0,%0,0x3cb0"
                             : "=&r"(t), "+r"(k));
            __asm__ volatile("");
            if (n < t) {
                tf2 = lbl_803CA954;
                goto block_14;
            }
        }
    }
    if (k == 0xff) {
        return vf2 + vf2;
    }
    k = k + n;
    if (k > 0xfe) {
        return fn_80273384(lbl_803CA958, vf2) * lbl_803CA958;
    }
    if (k > 0) {
        __asm__ volatile("slwi %0,%0,0x17" : "+r"(k));
        __asm__ volatile("rlwinm %0,%1,0,9,0" : "=&r"(nb) : "r"(var_r11));
        *(u32 *) &sp8 = nb | k;
        vf2 = *(f32 *) &sp8;
        __asm__("" : "+f"(vf2));
        return vf2;
    }
    if (k <= -25) {
        if (n > 50000) {
            return fn_80273384(lbl_803CA958, vf2) * lbl_803CA958;
        }
        return fn_80273384(lbl_803CA954, vf2) * lbl_803CA954;
    }
    k = k + 25;
    __asm__ volatile("rlwinm %0,%1,0,9,0" : "=&r"(nb) : "r"(var_r11));
    __asm__ volatile("slwi %0,%0,0x17" : "+r"(k));
    *(u32 *) &sp8 = nb | k;
    vf2 = *(f32 *) &sp8;
    __asm__ volatile("");
    tf2 = lbl_803CA95C;
block_14:
    return vf2 * tf2;
}
