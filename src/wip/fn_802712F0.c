// scalbn (fdlibm): y * 2**n via exponent manipulation. sdata consts:
// family=hand range=0x802712F0-0x80271444 size=340B
// two54=lbl_803CA750, tiny=lbl_803CA758, huge=lbl_803CA760, twom54=lbl_803CA768.
// Region recipe (cf. promoted sibs fn_8027124C/1444/1538/1A34): plain extern
// f64 refs, -msdata=eabi -G8, signed union words, tail-shared y*const returns.
// PARKED: 6-word residual (sda_verify LINK-SIM: want=got except below).
// Clean rewrite (no asm/pins except r11, sdata externs, -G8, lo-first copies
// per doc-44 floor lever) matches everything except two scheduling artifacts
// that also survived the prior asm-barrier draft, so they are structural:
//  (a) subnormal threshold: want `lis r0,-1` BEFORE `addi r11,r11,-0x36`
//      (materializes -50000 split around k-=54); clean emission puts the
//      lis after the addi. Needs the compare constant live before the
//      subtract with scheduling off - no clean source shape found.
//  (b) normal-path storeback: want compute-first (`slwi;rlwinm;lwz;lwz`)
//      but clean emission loads-first (`lwz;lwz;slwi;rlwinm`); the FINAL path
//      with identical source shape matches loads-first, so this is
//      combiner/reload context sensitivity (trailing `return y` vs
//      `return y*twom54`), not source order. Inline-form probe only swapped
//      rlwinm/slwi, did not move the loads.
// NEXT IDEAS: per-path scheduling is impossible per-object, so try making the
// normal path's trailing RTL resemble the final path (e.g. return via a temp
// consumed like the fmul), or find the original's word-read construct (the
// extra high-word lwz both shapes emit suggests a union struct copy idiom).
// FLAG: -msdata=eabi -G8 -fno-schedule-insns -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
extern f64 lbl_803CA750; /* two54 */
extern f64 lbl_803CA758; /* tiny */
extern f64 lbl_803CA760; /* huge */
extern f64 lbl_803CA768; /* twom54 */

extern f64 fn_80272044(f64 arg0, f64 arg1);

f64 fn_802712F0(f64 farg0, s32 n) {
    union { f64 d; s32 w[2]; } u;
    register s32 k __asm__("r11");
    s32 hx;
    s32 lx;
    s32 ku;
    s32 su;
    f64 y;
    f64 cv2;
    f64 tv;
    y = farg0;
    u.d = y;
    lx = u.w[1];
    hx = u.w[0];
    k = (hx >> 0x14) & 0x7ff;
    if (k == 0) {
        if ((lx | (hx & QB_UNKNOWN_0x7FFFFFFF)) == 0) {
            return y;
        }
        y *= lbl_803CA750;
        u.d = y;
        hx = u.w[0];
        k = ((hx >> 0x14) & 0x7ff) - 0x36;
        if (n < -50000) {
            return y * lbl_803CA758;
        }
    }
    if (k == 0x7ff) {
        return y + y;
    }
    k += n;
    if (k > 0x7fe) {
        goto overflow;
    }
    if (k > 0) {
        u.d = y;
        ku = k << 0x14;
        su = hx & 0x800FFFFF;
        u.w[0] = su | ku;
        u.w[1] = u.w[1];
        y = u.d;
        return y;
    }
    if (k <= -0x36) {
        if (n > 50000) {
overflow:
            cv2 = fn_80272044(lbl_803CA760, y);
            return cv2 * lbl_803CA760;
        } else {
            tv = fn_80272044(lbl_803CA758, y);
            return tv * lbl_803CA758;
        }
    }
    k += 0x36;
    u.d = y;
    ku = k << 0x14;
    su = hx & 0x800FFFFF;
    u.w[0] = su | ku;
    u.w[1] = u.w[1];
    y = u.d;
    return y * lbl_803CA768;
}
