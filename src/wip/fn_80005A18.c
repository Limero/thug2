// WIP DRAFT — hand re-match (PS normalize-and-scale leaf)
// family=hand range=0x80005A18-0x80005A90 size=120B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// IDENT (2026-09-06): PS scale-by-inverse-magnitude (suggested rename:
// PS_ScaleVecByInvLen): mag = 1/sqrt(d1*d1 + d0*d0) of the pairs at
// arg0+8/+0 (merge00 with lbl_8029FCC8), then v = arg1 pairs scaled by mag
// (ps_muls0) and stored into arg0+0/+8.
// PARKED 2026-09-06 (spill structure byte-exact, residual = reg-pin): want copies
// arg0 into r11 at entry (`mr r11,r3`) and addresses ALL dest pairs through
// r11; ngccc keeps r3 directly (no promoted source produces this prologue —
// scanned all of src/*.c). Documented GPR-coloring wall, doc 06 M5.0o/M5.0r.
// Volatile sp16/sp8 + three-stage pun chain (dot.flt.hi -> x -> (__ps_t*)&x)
// reproduces want's frame 0x28, stfs->psq_l->ps_mr mag idiom and dead spills.
// FLAG: -mps-float -Os
#include "types.h"
extern __ps_t lbl_8029FCC8;
void fn_80005A18(s32 arg0, void *arg1) {
    volatile __ps_t sp8;
    volatile __ps_t sp16;
    SN_PS_type dot;
    __ps_t d0;
    __ps_t d1;
    __ps_t v0;
    __ps_t v1;
    __ps_t m;
    __ps_t v0s;
    __ps_t v1s;
    f32 sp20;
    volatile f32 x;
    d1 = *(__ps_t *)((char *)arg0 + 8);
    d0 = *(__ps_t *)arg0;
    v1 = ((__ps_t *)arg1)[1];
    v0 = ((__ps_t *)arg1)[0];
    dot.ps = __builtin_ps_madd(d0, d0,
        __builtin_ps_merge00(__builtin_ps_mul(d1, d1), lbl_8029FCC8));
    dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
    dot.ps = __builtin_ps_rsqrte(dot.ps);
    dot.ps = __builtin_ps_res(dot.ps);
    x = dot.flt.hi;
    sp20 = x;
    m = *(__ps_t *)&sp20;
    v1s = __builtin_ps_muls0(v1, m);
    v0s = __builtin_ps_muls0(v0, m);
    sp16 = v1s;
    *(__ps_t *)arg0 = v0s;
    *(__ps_t *)((char *)arg0 + 8) = *(volatile __ps_t *)&sp16;
    sp8 = v0s;
}
