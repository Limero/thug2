// FIXED 2026-10-10 (was a compile FAIL, now scores): the local SN_PS_type
// typedef conflicted with the header's; replaced with #include
// "dolphin/SN_PS.h" (same {hi,lo} layout, the promoted-PS-file pattern).
// PARKED 2026-10-10: DIFF 0.8% (got 484B vs want 388B). Got spills FPRs
// (lfd f31) — too many live doubles / wrong scratch-frame model. Needs a
// frame-layout rebuild, not expression tweaks.
// WIP DRAFT (non-matching) — paired-single scalar-float reconstruction
// (replaces the m2c stub 2026-10-06).
// family=m2c range=0x801F7FEC-0x801F8170 size=388B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
//
// Rebuild of the two-segment "did the heading turn too sharply" test.
// Every `psq_l/psq_st ...,W0,I0` in the WANT is the ngccc -mps-float form of
// a plain f32 load/store (W0 = one element), and every opcode-4 word is the
// standard scalar->PS lowering of ordinary float math, so the source is
// ordinary f32 C, not paired-single math. The want runs a squaring of the
// distance pair in f0 (word 0x10000032), a pair-move within f0 (word
// 0x10006C20, whose selector is C=2), a move of f0 to f13 (word 0x11A00090),
// an accumulation into f0 from f12 and f0 (word 0x100C033A), a horizontal
// lane sum into f0 (word 0x10000014), a multiply of f11 by f12 into f13
// (word 0x11AB0332), a scaling by lane 0 into f0 (word 0x100C0358), a
// normalization of f0 into f13 (word 0x11A00034), and a subtraction of
// arg0.x from arg1.x into f13 (word 0x11AD6028).
#include "types.h"
#include "structs.h"
#include "qb_constants.h"

#include "dolphin/SN_PS.h"
/* (local SN_PS_type redundancy removed 2026-10-10: the header's union has the
   same {hi, lo} layout and is what the promoted PS files use; the local
   typedef conflicted and failed compilation.) */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

extern f32 lbl_802AE430;
extern f32 lbl_802AE4E8;
extern f32 lbl_802AE4EC;
extern f32 lbl_802AE4F0;

f32 cosf(f32);
f32 fn_8012570C(u32 param, s32 arg1);

s32 fn_801F7FEC(Vec3 *arg0, Vec3 *arg1, Vec3 *arg2) {
    struct {
        SN_PS_type p0;  /* ground delta  arg1 - arg0 (x)  -> psq_st @0x08 */
        SN_PS_type p1;  /* ground delta  arg1 - arg0 (z)  -> psq_st @0x10 */
        SN_PS_type q0;  /* ground delta  arg2 - arg1 (x)  -> psq_st @0x18 */
        SN_PS_type q1;  /* ground delta  arg2 - arg1 (z)  -> psq_st @0x20 */
        SN_PS_type dot; /* magnitude / cosine accumulator -> psq_st @0x38 */
    } fr;
    SN_PS_type a;
    SN_PS_type b;
    SN_PS_type k;
    SN_PS_type scale;
    __ps_t t;
    f32 len;
    f32 lim;
    f32 angle;
    s32 ok;

    lim = lbl_802AE4E8;

    /* ---- ground segment arg0 -> arg1, thresholded normalize ---- */
    a.flt.hi = arg1->x;
    b.flt.hi = arg0->x;
    fr.p0.ps = __builtin_ps_sub(a.ps, b.ps);
    a.flt.hi = arg1->z;
    b.flt.hi = arg0->z;
    fr.p1.ps = __builtin_ps_sub(a.ps, b.ps);
    fr.p0.flt.lo = lbl_802AE4E8;

    t = __builtin_ps_mul(fr.p1.ps, fr.p1.ps);
    k.flt.hi = lbl_802AE430;
    t = __builtin_ps_merge00(t, k.ps);
    fr.dot.ps = __builtin_ps_madd(fr.p0.ps, fr.p0.ps, t);
    fr.dot.ps = __builtin_ps_sum0(fr.dot.ps, fr.dot.ps, fr.dot.ps);
    len = fr.dot.flt.hi;
    if (len > lim) {
        scale.ps = __builtin_ps_rsqrte(fr.dot.ps);
        fr.p0.ps = __builtin_ps_muls0(fr.p0.ps, scale.ps);
        scale.flt.lo = lbl_802AE4EC;
        fr.p1.ps = __builtin_ps_mul(fr.p1.ps, scale.ps);
    }

    /* ---- ground segment arg1 -> arg2, thresholded normalize ---- */
    a.flt.hi = arg2->x;
    b.flt.hi = arg1->x;
    fr.q0.ps = __builtin_ps_sub(a.ps, b.ps);
    a.flt.hi = arg2->z;
    b.flt.hi = arg1->z;
    fr.q1.ps = __builtin_ps_sub(a.ps, b.ps);
    fr.q0.flt.lo = lbl_802AE4E8;

    t = __builtin_ps_mul(fr.q1.ps, fr.q1.ps);
    k.flt.hi = lbl_802AE430;
    t = __builtin_ps_merge00(t, k.ps);
    fr.dot.ps = __builtin_ps_madd(fr.q0.ps, fr.q0.ps, t);
    fr.dot.ps = __builtin_ps_sum0(fr.dot.ps, fr.dot.ps, fr.dot.ps);
    len = fr.dot.flt.hi;
    if (len > lim) {
        scale.ps = __builtin_ps_rsqrte(fr.dot.ps);
        fr.q0.ps = __builtin_ps_muls0(fr.q0.ps, scale.ps);
        scale.flt.lo = lbl_802AE4EC;
        fr.q1.ps = __builtin_ps_mul(fr.q1.ps, scale.ps);
    }

    /* ---- cosine between the two normalized ground headings ---- */
    t = __builtin_ps_mul(fr.p1.ps, fr.q1.ps);
    k.flt.hi = lbl_802AE430;
    t = __builtin_ps_merge00(t, k.ps);
    fr.dot.ps = __builtin_ps_madd(fr.p0.ps, fr.q0.ps, t);
    fr.dot.ps = __builtin_ps_sum0(fr.dot.ps, fr.dot.ps, fr.dot.ps);
    angle = fr.dot.flt.hi; /* kept in f31 across the two calls */

    ok = 0;
    if (!(angle < cosf(fn_8012570C(QB_RAIL_CORNER_LEAVE_ANGLE, 0) * lbl_802AE4F0))) {
        ok = 1;
    }
    return ok;
}

// PARKED 2026-10-06: PS/-mps-float function, structure recovered
// but not byte-exact.  Body above is a faithful skeleton (two ground-plane
// segment deltas, thresholded normalize via ps_rsqrte/ps_muls0, final cosine
// against cosf(ScriptValue(Rail_Corner_Leave_Angle) * DEG2RAD)); the m2c body
// it replaces was literal `0;` junk that could not express this control flow.
//
// What is PROVEN from the WANT (all 97 words decoded with tools/ps_diff.py's
// field map, a->frA / b->frC / c->frB for ps_madd/ps_sum0/muls0/merge00):
//   - every opcode-4 word is the ordinary scalar-float lowering under
//     -mps-float (psq_l/psq_st ...,W0,I0 = 4-byte f32 access; ps_mul/ps_madd/
//     ps_sum0 = the canonical dot-product chain documented in
//     docs/parkings/06-paired-single-ops.md M5.0j);
//   - two identical normalize blocks (arg1-arg0 then arg2-arg1) reusing the
//     x/z components of a 12-byte vector only (the +4 y lane is never read);
//   - frame 0x50, stfd f31 @0x48 (the +8 FPR pad8 class, handled by
//     test_wip_drafts.py's dual dummy test), lr @0x54, pair slots @0x08/0x10/
//     0x18/0x20/0x28/0x38, scalar const fills @0x0c/0x1c/0x2c/0x34;
//   - 0x76C1DA15 == QB_RAIL_CORNER_LEAVE_ANGLE (include/qb_constants.h).
//
// Blockers, in the order they bite:
//   1. dead psq_st spills after every ps_sub need the M5.0j-2r "addressable
//      intermediate" shape (intermediates homed in a struct member, results
//      read back through it).  Written that way here, but the exact member
//      set/order that reproduces slots 0x08..0x38 is unverified.
//   2. the lane-1 const fills (stfs @0x0c/0x1c from lbl_802AE4E8, @0x2c/0x34
//      from lbl_802AE4EC) are the scalar->pair broadcast plumbing of
//      -mps-float; without compiling I cannot tell whether they come from the
//      `flt.lo =` union writes above or from a second use of each constant.
//   3. ps_sum0/ps_merge00/ps_rsqrte/ps_muls0 + FPR31 coloring is the known
//      M5.0o/M5.0r regalloc+scheduler coin-flip class: doc 06's M5.0j sweep
//      found this whole subtraction/normalize cluster trailing on tie-breaks
//      even with a correct skeleton (fn_8005A114 ~33%, fn_8020D530 needs the
//      SNAPS rewrite).  Re-measure with
//      `tools/venv/bin/python tools/test_wip_drafts.py --addr 0x801F7FEC`
//      (the tool auto-applies -mps-float for `__ps_t` bodies) and refine the
//      skeleton with tools/ps_diff.py before touching flags.
