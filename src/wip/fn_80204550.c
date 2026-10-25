// WIP DRAFT (non-matching) - hand rebuild from the original unit disassembly.
// family=m2c range=0x80204550-0x80204628 size=216B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// STRUCTURE: fills one 2x2 rotation basis (two 8-byte float pairs) into `out`.
//   ang = (f32)(f64)arg2 * lbl_802AEF78      (0.8975979 = 2*pi/7)
//   c = cosf(ang), s = sinf(ang)
//   m = { 1.0f, 0.0f, 1.0f, 1.0f }          (address-taken, so memory resident)
//   out[0] = c * m[0] - s
//   out[1] = 0.0f
//   out[2] = s * m[0] + c * m[2]
//   out[3] = 1.0f
// The two output pairs are written with 8-byte paired-single copies, which is
// why the draft is compiled with -mps-float: the original writes each pair
// from its stack slot with one psq_l/psq_st pair (scalar fmuls/fmsubs/fmadds
// for the arithmetic).
//
// The int->float conversion goes through the game's signed int->double
// expansion (xoris sign flip + 2^52+2^31 bias then frsp), which is what
// `(f32)(f64)arg2` produces for an s32 argument; arg1 is unused by the body.
//
// The four matrix values stay in memory (`volatile` array) because the
// original reloads m[0] for both expressions and m[2] for the second one
// instead of folding the constants into the arithmetic.
#include "types.h"

extern const f32 lbl_802AEF78;
extern const f32 lbl_802AEF7C;
extern const f32 lbl_802AEF80;

f32 cosf(f32);
f32 sinf(f32);

s32 fn_80204550(s32 out, s32 arg1, s32 arg2) {
    volatile f32 m[4];
    f32 o[4];
    f32 ang;
    f32 c;
    f32 s;

    ang = (f32)(f64)arg2 * lbl_802AEF78;
    c = cosf(ang);
    s = sinf(ang);
    m[0] = lbl_802AEF7C;
    m[2] = lbl_802AEF7C;
    m[1] = lbl_802AEF80;
    m[3] = lbl_802AEF7C;
    o[1] = lbl_802AEF80;
    o[0] = c * m[0] - s;
    *(__ps_t *)out = *(__ps_t *)&o[0];
    o[3] = lbl_802AEF7C;
    o[2] = s * m[0] + c * m[2];
    *(__ps_t *)(out + 8) = *(__ps_t *)&o[2];
    return out;
}
