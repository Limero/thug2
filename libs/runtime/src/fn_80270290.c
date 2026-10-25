// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80270290-0x802703EC (348B). Byte-identical.
// extra_cflags: -msdata=eabi, -G8
// FLAG: -msdata=eabi -G8
// floor() (fdlibm): constants lbl_803CA648 (1e300) / lbl_803CA650 (0.0) are
// r13-relative .sdata doubles (R_PPC_EMB_SDA21, resolved at link vs
// _SDA_BASE_). Promoted via the sda_verify route (AGENTS.md 5q).
#include "types.h"
#include "qb_constants.h"

extern f64 lbl_803CA648; /* 1e300 */
extern f64 lbl_803CA650; /* 0.0   */

f64 fn_80270290(f64 x) {
    register f64 tf __asm__("fr0");
    union {
        f64 d;
        u32 w[2];
    } uu;
    register u32 var_r11 __asm__("r11");
    register u32 var_r6 __asm__("r6");
    u32 t9;
    u32 mask;
    s32 k;

    __asm__("fmr %0,%1" : "=f"(tf) : "f"(x));
    uu.d = tf;
    {
        register u32 tw0 __asm__("r9");
        register u32 tw1 __asm__("r10");
        __asm__ volatile("lwz %0,8(1)\n\tlwz %1,12(1)\n\tmr %2,%1\n\tmr %3,%0"
                         : "=r"(tw0), "=r"(tw1), "=r"(var_r6), "=r"(var_r11));
        __asm__ volatile("" : : "r"(tw0), "r"(tw1));
    }
    k = (s32) ((var_r11 >> 20) & 0x7FF) - 0x3FF;
    if (k <= 0x13) {
        if (k < 0) {
            if (! (x + lbl_803CA648 > lbl_803CA650)) {
                goto rebuild;
            }
            if ((s32) var_r11 >= 0) {
                var_r6 = 0;
                var_r11 = 0;
                goto rebuild;
            }
            if (((var_r11 & QB_UNKNOWN_0x7FFFFFFF) | var_r6) != 0) {
                var_r11 = QB_UNKNOWN_0xBFF00000;
                var_r6 = 0;
            }
            goto rebuild;
        } else {
            mask = 0xFFFFF >> k;
            if (((var_r11 & mask) | var_r6) == 0) {
                return x;
            }
            if (! (x + lbl_803CA648 > lbl_803CA650)) {
                goto rebuild;
            }
            if ((s32) var_r11 < 0) {
                var_r11 += 0x100000 >> k;
            }
            var_r11 &= ~mask;
            var_r6 = 0;
            goto rebuild;
        }
    } else {
        if (k > 0x33) {
            if (k == 0x400) {
                return x + x;
            }
            return x;
        }
        mask = QB_UINT32_MAX >> ((k + 0x3FF) - 0x413);
        if ((var_r6 & mask) == 0) {
            return x;
        }
        if (! (x + lbl_803CA648 > lbl_803CA650)) {
            goto rebuild;
        }
        if ((s32) var_r11 < 0) {
            if (k == 0x14) {
                var_r11 += 1;
            } else {
                t9 = var_r6 + (1 << (0x34 - k));
                if (t9 < var_r6) {
                    var_r11 += 1;
                }
                var_r6 = t9;
            }
        }
        var_r6 &= ~mask;
        goto rebuild;
    }
rebuild:
    __asm__("mr %0,%1" : "=r"(uu.w[0]) : "r"(var_r11));
    __asm__("mr %0,%1" : "=r"(uu.w[1]) : "r"(var_r6));
    x = uu.d;
    return x;
}
