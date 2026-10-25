// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B090C-0x800B0A08 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns -mps-float
#include "types.h"

typedef struct {
    char pad0x00[0x08];
    __ps_t p08;
    __ps_t p10;
    char pad0x18[0x14];
    s32 state;
    char pad0x30[0x04];
    f32 f34;
    char pad0x38[0x08];
    f32 min0, min1, min2;
    char pad0x4C[0x04];
    f32 max0, max1, max2;
} BoundsObj;

typedef struct {
    __ps_t p0;
    __ps_t p8;
} Point;

typedef struct {
    f32 hi;
    f32 lo;
} PairF;

typedef struct {
    PairF lo;
    PairF hi;
    PairF res;
} PSOut;

extern __ps_t lbl_80298778;

s32 fn_800B090C(BoundsObj *arg0, Point *arg1) {
    PSOut out;
    __ps_t q;
    __ps_t d;
    __ps_t z;
    __ps_t w;
    __ps_t q2;
    __ps_t n;
    __ps_t acc;
    __ps_t r;
    register s32 state __asm__("r11");
    register s32 var_r0 __asm__("r0");
    register f32 t __asm__("fr0");
    f32 val;
    f32 x0, x1, x2;

    state = arg0->state;
    q = arg0->p10;
    d = arg1->p8;
    z = lbl_80298778;
    w = arg1->p0;
    var_r0 = 0;

    d = __builtin_ps_sub(d, q);
    *(volatile __ps_t *)&out.hi = d;

    d = __builtin_ps_mul(d, d);
    q2 = arg0->p08;
    d = __builtin_ps_merge00(d, z);
    n = __builtin_ps_sub(w, q2);
    *(volatile __ps_t *)&out.lo = n;
    acc = __builtin_ps_madd(n, n, d);
    r = __builtin_ps_sum0(acc, acc, acc);
    *(volatile __ps_t *)&out.res = r;
    t = out.res.hi;
    __asm__("" : "+f"(t));
    val = t;

    if (state != 0) {
        if (state == 2) {
            var_r0 = (val <= arg0->f34);
        }
    } else {
        var_r0 = 0;
        if (!(((PairF *)&arg1->p0)->hi >= arg0->min0)) goto done;
        if (!(((PairF *)&arg1->p0)->lo >= arg0->min1)) goto done;
        if (!(((PairF *)&arg1->p8)->hi >= arg0->min2)) goto done;
        if (!(((PairF *)&arg1->p0)->hi <= arg0->max0)) goto done;
        if (!(((PairF *)&arg1->p0)->lo <= arg0->max1)) goto done;
        if (!(((PairF *)&arg1->p8)->hi <= arg0->max2)) goto done;
        var_r0 = 1;
    }
done:
    return var_r0;
}
