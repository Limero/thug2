// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A08C0-0x800A0A28 (360B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"

s32 GetFloat(s32 arg0, s32 arg1, f32 *arg2, s32 arg3);
extern f32 lbl_80297B80;

typedef struct {
    char _00[0x58];
    __ps_t acc0; /* +0x58: xy accumulator, += muls0(inXa, sc) */
    __ps_t acc1; /* +0x60: zw accumulator, += muls0(inXb, sc) */
    char _68[0x10];
    __ps_t in0a; /* +0x78 / +0x88 / +0x98: per-round scale input, lo lanes */
    __ps_t in0b; /* +0x80 / +0x90 / +0xA0: per-round scale input, hi lanes */
    __ps_t in1a;
    __ps_t in1b;
    __ps_t in2a;
    __ps_t in2b;
} A08C0Obj;

bool fn_800A08C0(A08C0Obj *arg0, s32 arg1) {
    __ps_t v[2];
    __ps_t *p = v;
    union { f32 f; __ps_t p; } s0;
    union { f32 f; __ps_t p; } s1;
    union { f32 f; __ps_t p; } s2;
    f32 f;
    f32 d = lbl_80297B80;

    f = d;
    GetFloat(arg1, QB_X, &f, 0);
    s0.f = f;
    v[0] = __builtin_ps_muls0(arg0->in0a, s0.p);
    v[1] = __builtin_ps_muls0(arg0->in0b, s0.p);
    arg0->acc0 = __builtin_ps_add(arg0->acc0, v[0]);
    arg0->acc1 = __builtin_ps_add(arg0->acc1, p[1]);

    f = d;
    GetFloat(arg1, QB_Y, &f, 0);
    s1.f = f;
    v[0] = __builtin_ps_muls0(arg0->in1a, s1.p);
    v[1] = __builtin_ps_muls0(arg0->in1b, s1.p);
    arg0->acc0 = __builtin_ps_add(arg0->acc0, v[0]);
    arg0->acc1 = __builtin_ps_add(arg0->acc1, p[1]);

    f = d;
    GetFloat(arg1, QB_Z, &f, 0);
    s2.f = f;
    v[0] = __builtin_ps_muls0(arg0->in2a, s2.p);
    v[1] = __builtin_ps_muls0(arg0->in2b, s2.p);
    arg0->acc0 = __builtin_ps_add(arg0->acc0, v[0]);
    arg0->acc1 = __builtin_ps_add(arg0->acc1, p[1]);

    return true;
}
