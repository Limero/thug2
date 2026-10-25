// WIP DRAFT (non-matching) — hand rebuild from the original function.
// family=hand range=0x800058CC-0x80005A18 size=332B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT THIS IS: basis-vector construction. `out` is a 4-float vector supplied
// by the caller, `in` is the axis to reject. Each step is paired-single:
//
//   len = rsqrt(out.x^2 + out.y^2 + out.z^2)     (rsqrte then res, scalar
//                                                  extracted through the stack)
//   fn_80005854(out, in)                        (Gram-Schmidt: remove `in`)
//   if (out.len2 == 0.0f)                        (degenerate: `out` was
//       out.xyz = (-in.z, in.x, -in.y)            parallel to `in`)
//   if (out.len2 > 0.0f) {
//       r = rsqrt(out.len2)
//       out.xy *= r
//       out.zw *= (r, 1.0f)                      (pair built on the stack:
//                                                 half pair store, half float
//                                                 store, then pair reload)
//   }
//   out.zw *= len                                (restore the pre-projection
//   out.w   = 0.0f                                length; the pair is read
//   out.xy *= len                                 back from a single float
//   return out;                                   slot, so lane 1 is dead)
//
// Constants (verified in the DOL .rodata2): lbl_8028FCC8 starts with the
// {0.0f, 0.0f} pair used as the ps_merge00 argument, lbl_8028FCF4 = 0.0f,
// lbl_8028FCF8 = 1.0f.
//
// The dot product is the usual three-pair PS form (ps_mul on the high pair,
// ps_merge00 against the zero pair, ps_madd of the low pair, ps_sum0), written
// out three times because the original recomputes it in each block rather than
// caching it. The stack round trips are deliberate: the length scalar is read
// out of the PS result through a memory slot, and the (r, 1.0f) operand is
// assembled by a pair store followed by one scalar store into its upper lane.
//
// Open questions for the next measurement: FPR colouring of the three PS
// scratch chains and the pair-copy (ps_mr) the original emits before each reuse
// of the length value; those are register-allocation choices, so they may need
// declaration-order or non-escaping-slot changes rather than new statements.
#include "types.h"
#include "structs.h"

extern __ps_t lbl_8028FCC8;
extern f32 lbl_8028FCF4;
extern f32 lbl_8028FCF8;

typedef union {
    struct {
        __ps_t p0;
        __ps_t p1;
    } ps;
    f32 f[4];
} Vec4;

void fn_80005854(Vec4 *dst, Vec4 *src);

Vec4 *fn_800058CC(Vec4 *out, Vec4 *in) {
    __ps_t p0;
    __ps_t p1;
    __ps_t t;
    __ps_t r;
    SN_PS_type d;
    volatile f32 keep;
    f32 len;
    f32 n2;

    p1 = out->ps.p1;
    t = __builtin_ps_mul(p1, p1);
    p0 = out->ps.p0;
    t = __builtin_ps_merge00(t, lbl_8028FCC8);
    t = __builtin_ps_madd(p0, p0, t);
    t = __builtin_ps_sum0(t, t, t);
    t = __builtin_ps_rsqrte(t);
    t = __builtin_ps_res(t);
    d.ps = t;
    len = d.flt.hi;

    fn_80005854(out, in);

    p1 = out->ps.p1;
    t = __builtin_ps_mul(p1, p1);
    p0 = out->ps.p0;
    t = __builtin_ps_merge00(t, lbl_8028FCC8);
    t = __builtin_ps_madd(p0, p0, t);
    t = __builtin_ps_sum0(t, t, t);
    t = __builtin_ps_rsqrte(t);
    t = __builtin_ps_res(t);
    d.ps = t;
    n2 = d.flt.hi;

    if (n2 == lbl_8028FCF4) {
        out->f[0] = -in->f[2];
        out->f[1] = in->f[0];
        out->f[2] = -in->f[1];
    }

    p1 = out->ps.p1;
    p0 = out->ps.p0;
    t = __builtin_ps_mul(p1, p1);
    t = __builtin_ps_merge00(t, lbl_8028FCC8);
    t = __builtin_ps_madd(p0, p0, t);
    t = __builtin_ps_sum0(t, t, t);
    d.ps = t;

    if (d.flt.hi > lbl_8028FCF4) {
        volatile SN_PS_type k;

        r = __builtin_ps_rsqrte(d.ps);
        out->ps.p0 = __builtin_ps_muls0(p0, r);
        k.ps = r;
        k.flt.lo = lbl_8028FCF8;
        out->ps.p1 = __builtin_ps_mul(p1, k.ps);
    }

    keep = len;
    p1 = out->ps.p1;
    p0 = out->ps.p0;
    t = *(volatile __ps_t *)&keep;
    out->ps.p1 = __builtin_ps_muls0(p1, t);
    out->f[3] = lbl_8028FCF4;
    out->ps.p0 = __builtin_ps_muls0(p0, t);
    return out;
}
