// family=m2c range=0x8011F590-0x8011FB48 size=1464B
// PARKED 2026-10-03 (b02): DIFF 2.2% (baseline FAIL - did not compile).
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8011F590
// GOT 1340B vs WANT 1464B (8/366 masked words).  The pct is positional noise:
// the body is instruction-for-instruction correct from 0x2c onward, but the
// want's prologue is 7 words (mine is 11) and the want carries a 25-word
// paired-single NORMALISE block that scalar C cannot emit, so everything after
// 0xb4 is shifted and scores ~0.
// FIXED (the FAIL): ngccc rejected m2c's bare `sqrtf()' / `sinf(x)'-as-statement
//   / `asinf(0, x)'.  Body is now a full hand-decode with declared f32
//   prototypes for asinf/sinf/sqrtf/fabsf (implicit decls would promote the
//   float args to double and call a non-existent `fabs'), u16 arg0 fields
//   (sth/lhz, not stw/lwz), s32 arg2 (the want does `srwi r28,0x10', so the
//   high half is a real u32 shift, not a u16 param), the block_56 label INSIDE
//   the else arm (so the main path branches over the 0x12 store exactly as the
//   want's `b 0x8011fafc' does), and all four overlapping range arms decoded
//   from their cror polarity:
//     arm0 (sp8[0])  ang >= D708 || ang <= D70C,  t = ang+D710 (-D714)
//     arm1 (sp8[1])  ang <= D71C && ang <= D710,   ang + D70C
//     arm2 (sp8[2])  ang <= D70C && ang <= D708,   ang - D70C
//     arm3 (sp8[3])  ang >= D710 || ang <= D71C,  t = ang+D708 (-D714)
//   each ending in sqrtf(sinf((t/D718)*D700)).  The `.rodata2' constants are
//   lbl_8029D6F4..lbl_8029D730 (base 0x802A0000 in the want) and the flag is
//   lbl_80302CFC (base 0x80300000), NOT the lbl_80302CFC m2c used for .data.
// REMAINING DIFF, in order of cost:
//   1. 0x644-0x6A4, 25 words: psq_l/ps_mul/ps_merge00/ps_madd/ps_sum0/
//      ps_rsqrte/ps_res normalise.  ngccc emits NONE of these from scalar C
//      (verified: `1.0f/sqrtf(a*a+b*b)' -> bl sqrtf + fdivs, with or without
//      -mps-float), so the original source used the SN_PS.h intrinsics
//      (ps_mul/ps_merge00/ps_madd/ps_sum0/ps_rsqrte/ps_res - the chain is
//      emittable, see recipes SS6397/L16772).  Reproducing it needs
//      `sn_ps' locals, which REQUIRES -mps-float for the whole object, which
//      re-frames every scalar call site in the function (q1 probe: the
//      sinf/sqrtf stfs/bl/stfs survives, but the FPR save offsets shift).
//      Recipes SS6397/290 call this the known normalise-family wall.
//   2. Prologue: want saves exactly f28-f31 (ang, farg2, 0.0f, inv-len);
//      this body saves f26-f31 because `lensq' (live across bl sqrtf) and `t'
//      (spilled to a callee-saved colour) also survive a call.  Getting to 4
//      saves needs the want's store-then-reload idiom for lensq, which is only
//      available once (1) lands.
//   3. Frame: want 0xa0 with locals 0x8..0x68 (sp8[4]@8, sp18[4]@0x18,
//      vec4@0x28, inv-len@0x38, PS pair@0x40/0x44, int<->double scratch@0x68);
//      got 0x70.  A `volatile double _dummy' (the harness's own +8 probe) makes
//      it WORSE (2.2% -> 1.9%), so the gap is real locals, not the frame quirk.
// RULED OUT:
//   * -mps-float / sn_ps intrinsics for the normalise block: the intrinsic
//     chain IS emittable, but the -mps-float object-wide frame shift breaks
//     every scalar call site, and `SN_PS_type.flt' (not sn_ps) is needed to
//     reach the low lane - too big a rewrite to validate in budget.
//   * implicit-declaration math calls: they compile but promote f32 args to
//     double, which is why declaring the four prototypes is mandatory, not
//     cosmetic.
//   * u16 arg2 (m2c's type): folds away the `srwi r28,0x10' the want has.
//   * the `d7d1' (0 <= x <= 0x20) tail: the want uses four separate `bgt'
//     with a shared target, i.e. `a<=L && b<=L && c<=L && d<=L', which this
//     body already spells that way.
// MOST PROMISING NEXT IDEA: rebuild the whole body around a `sn_ps' pair for
//   the 0x28/0x30 group so the normalise block emits natively, then chase the
//   FPR count down to 4 (that alone fixes the prologue AND every stack offset).
//
#include "types.h"
#include "structs.h"
extern char lbl_8029D6F4[];
extern f32 lbl_8029D6F8;
extern f32 lbl_8029D6FC;
extern f32 lbl_8029D700;
extern f32 lbl_8029D704;
extern f32 lbl_8029D708;
extern f32 lbl_8029D70C;
extern f32 lbl_8029D710;
extern f32 lbl_8029D714;
extern f32 lbl_8029D718;
extern f32 lbl_8029D71C;
extern f32 lbl_8029D720;
extern f32 lbl_8029D724;
extern f32 lbl_8029D730;
extern s32 lbl_80302CFC;
extern f32 fabsf(f32);
extern f32 asinf(f32);
extern f32 sinf(f32);
extern f32 sqrtf(f32);

void fn_8011F590(Unk_7C948358 *arg0, Unk_31DE137E *arg1, s32 arg2, s32 arg3,
                 f32 farg0, f32 farg1, f32 farg2) {
    f32 sp8[4];
    s32 sp18[4];
    f32 zero;
    f32 sp2C;
    f32 sp28;
    f32 sp30;
    f32 sp34;
    f32 sp38;
    f32 lensq;
    f32 ang;
    f32 t;
    s32 r9v;
    s32 r0v;
    s32 i;

    zero = *(f32 *)&lbl_8029D6F4;
    sp8[3] = zero;
    sp8[2] = zero;
    sp8[1] = zero;
    sp8[0] = zero;

    if (lbl_80302CFC != 0) {
        if ((farg0 == zero) && (farg1 == zero)) {
            r9v = 0;
            *(u16 *)((char *)arg0 + 0x16) = 0;
            *(u16 *)((char *)arg0 + 0xC) = 3;
            goto block_56;
        }
        sp2C = fabsf(farg1);
        sp28 = fabsf(farg0);
        sp34 = zero;
        sp30 = zero;
        lensq = sp28 * sp28 + sp2C * sp2C;
        sp38 = 1.0f / sqrtf(lensq);
        if (lensq > zero) {
            sp28 = sp28 * sp38;
            sp2C = lensq * sp38;
        }
        t = sp2C;
        if (sp2C > lbl_8029D6F8) {
            t = lbl_8029D6F8;
        }
        if (t < zero) {
            t = zero;
        }
        ang = 2.0f * asinf(t) - lbl_8029D6FC;
        if (farg0 < zero) {
            ang = lbl_8029D700 - ang;
        }
        ang = ang * lbl_8029D704;

        if ((ang >= lbl_8029D708) || (ang <= lbl_8029D70C)) {
            t = ang + lbl_8029D710;
            if (t <= lbl_8029D714) {
                t = t - lbl_8029D714;
            }
            sp8[0] = sqrtf(sinf((t / lbl_8029D718) * lbl_8029D700));
        }
        if ((ang <= lbl_8029D71C) && (ang <= lbl_8029D710)) {
            sp8[1] = sqrtf(sinf(((ang + lbl_8029D70C) / lbl_8029D718) * lbl_8029D700));
        }
        if ((ang <= lbl_8029D70C) && (ang <= lbl_8029D708)) {
            sp8[2] = sqrtf(sinf(((ang - lbl_8029D70C) / lbl_8029D718) * lbl_8029D700));
        }
        if ((ang >= lbl_8029D710) || (ang <= lbl_8029D71C)) {
            t = ang + lbl_8029D708;
            if (t <= lbl_8029D714) {
                t = t - lbl_8029D714;
            }
            sp8[3] = sqrtf(sinf((t / lbl_8029D718) * lbl_8029D700));
        }
        i = 0;
        do {
            sp8[i] = sp8[i] * sp38;
            if (sp8[i] > lbl_8029D720) {
                sp8[i] = lbl_8029D720;
            }
            i++;
        } while (i != 4);
        i = 0;
        do {
            sp18[i] = (s32)(farg2 * (f32)((s32)(sp8[i] * lbl_8029D724 / lbl_8029D720))
                            * lbl_8029D730);
            i++;
        } while (i != 4);
        if ((sp18[0] <= 0x20) && (sp18[1] <= 0x20) &&
            (sp18[2] <= 0x20) && (sp18[3] <= 0x20)) {
            r9v = 0;
            *(u16 *)((char *)arg0 + 0x16) = 0;
            *(u16 *)((char *)arg0 + 0xC) = 3;
            goto block_56;
        }
        *(u16 *)((char *)arg0 + 0xC) = 0x4000;
        if (sp18[0] > 0) {
            *(u16 *)((char *)arg0 + 0xC) = 0x4001;
            *(u16 *)((char *)arg0 + 0x12) = *(u16 *)&sp18[0];
        }
        if (sp18[1] > 0) {
            *(u16 *)((char *)arg0 + 0x16) = *(u16 *)&sp18[1];
            *(u16 *)((char *)arg0 + 0xC) = (u16)(*(u16 *)((char *)arg0 + 0xC) | 2);
        }
        if (sp18[2] > 0) {
            *(u16 *)((char *)arg0 + 0x22) = *(u16 *)&sp18[2];
            *(u16 *)((char *)arg0 + 0xC) = (u16)(*(u16 *)((char *)arg0 + 0xC) | 0x200);
        }
        if (sp18[3] > 0) {
            *(u16 *)((char *)arg0 + 0x26) = *(u16 *)&sp18[3];
            *(u16 *)((char *)arg0 + 0xC) = (u16)(*(u16 *)((char *)arg0 + 0xC) | 0x400);
        }
    } else {
        r0v = (s32)(farg2 * farg0 * lbl_8029D730 * lbl_8029D724 * lbl_8029D730);
        r9v = (s32)(farg2 * farg1 * lbl_8029D730 * lbl_8029D724 * lbl_8029D730);
        if (r0v > 0x7FFF) {
            r0v = 0x7FFF;
        } else if (r0v < 0) {
            r0v = 0;
        }
        if (r9v > 0x7FFF) {
            r9v = 0x7FFF;
        } else if (r9v < 0) {
            r9v = 0;
        }
        r9v = (r0v + r9v) / 2;
        *(u16 *)((char *)arg0 + 0xC) = 3;
        *(u16 *)((char *)arg0 + 0x16) = (u16)r9v;
block_56:
        *(u16 *)((char *)arg0 + 0x12) = (u16)r9v;
    }
    arg1->unk0x1C |= 0x12;
    if (arg3 != 0) {
        *(u16 *)((char *)arg0 + 0xA8) = arg2;
        *(u16 *)((char *)arg0 + 0xA6) = (u16)(arg2 >> 0x10);
        arg1->unk0x1C |= 0x80000;
    }
}