// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80005A90-0x80005B00 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float -mcpu=603
#include "types.h"
#include "dolphin/SN_PS.h"
#include "structs.h"

typedef union {
    __ps_t p[2];
    f32 f[4];
} Vec4;

typedef union {
    __ps_t p;
    f32 s;
} PScalar;

extern __ps_t lbl_8028FCC8;

void fn_80005A90(Vec4 *arg0, Vec4 *arg1) {
    register Vec4 *dst __asm__("r11");
    volatile __ps_t o[2];
    SN_PS_type dot;
    PScalar sc;
    __ps_t shi, dhi, dlo, slo, t, lo;
    f32 s;

    dst = arg0;
    shi = arg1->p[1];
    dhi = dst->p[1];
    dlo = dst->p[0];
    t = __builtin_ps_mul(dhi, shi);
    t = __builtin_ps_merge00(t, lbl_8028FCC8);
    slo = arg1->p[0];
    t = __builtin_ps_madd(dlo, slo, t);
    dot.ps = __builtin_ps_sum0(t, t, t);
    s = dot.flt.hi;
    sc.s = s;
    o[1] = __builtin_ps_muls0(shi, sc.p);
    lo = __builtin_ps_muls0(slo, sc.p);
    dst->p[0] = lo;
    dst->p[1] = o[1];
    o[0] = lo;
}
