// WIP DRAFT (non-matching) — hand-rebuilt 2026-09-27 from the retail disasm
// (previous body was the inert m2c stub: 8 `0;` holes, no PS math, 1/8 the size).
// family=m2c range=0x800B0A08-0x800B0B68 size=352B
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-03 (a23): DIFF 36.4% masked (32/88 words), SIZE 352B == retail
// 352B EXACTLY, and the 51-word PS block is now ALIGNED 1:1 WITH RETAIL (same
// 16 A-form words in the same order at the same offsets; before this round the
// body was 1 word short and the block drifted).
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800B0A08
//
// *** THE FIX THAT MATTERED (was a SEMANTICS bug, not CSE) ***
// Retail does `addi r10,r30,8` and then loads `8(r10)` twice.  r10 = arg1+8,
// so `8(r10)` = arg1+0x10 — a SECOND __ps_t field, NOT arg1+8 again.  The
// previous round concluded "ngccc CSEs the four identical v08 loads"; that was
// wrong, they were never identical.  Retail's real operand map (see below):
//     d1 = arg2[1] - arg1->v10          (v10 = the __ps_t at +0x10)
//     d0 = arg2[0] - arg1->v08          (v08 = the __ps_t at +0x08)
//     out[0] = v08 + d0*sc ; out[1] = v10 + d1*sc
// i.e. axis 0 uses the +0x08 pair and axis 1 uses the +0x10 pair.  Adding
// `__ps_t v10;` to the Obj typedef and using it for axis 1 took 29.5 -> 36.4
// and made the .text size exact.  Struct offsets after this: v08@0x08,
// v10@0x10, unk2C@0x2C, unk30@0x30, unk38@0x38, pair@0x40 (unchanged, the two
// 16-byte fields fit in the old pad10[0x1C]).
//
// *** PS WORD DECODE (measured, not guessed — reuse this) ***
// ngccc A-form: XO@bits1-5, operand@bits6-10, operand@bits11-15,
// operand(A)@bits16-20, operand(D)@bits21-25, form=4@bits26-30, Rc@bit0.
// Derivation: compile `register __ps_t A __asm__("fr3")` locals + one
// __builtin each and read the fields (script in <scratch>).
//   sub=20 add=21 muls0=12 muls1=13 mul=25 madd=29 madds0=14 msub=28
//   sum0=10 sum1=11 merge00=16 rsqrte=26, and bits1-5==8 = the X-form
//   lane-move family (ps_mr-class) whose "D" is also at bits21-25.
//   3-operand ops (madd/sum0/madds0/msub) put A@16-20, B@6-10, C@11-15,
//   D@21-25.  GCC COMMUTES mul/madd freely, so never read source operand order
//   off the encoding.  merge00-11 carry a mode EXTENSION (16..19) in bits6-10,
//   not a register.  psq_l/psq_st use a SPLIT D field — do not hand-decode.
// Retail colouring: d1->f9, d1*d1->f0, d0->f12, sq->f0, sum->f0, scalar->f13,
// rsqrte->f0, d0*sc->f13, d1*sc->f11, out0->f12, out1->f0.
// Got colouring:   d1->f10, sq->f0, d0->f13, scalar->f12, d0*sc->f13,
// d1*sc->f0, out1->f13.
//
// PRECISE RESIDUAL (56 words, four classes):
//  (a) ONE structural word: retail keeps `addi r10,r30,8` (base &v08) and
//      reaches v10 as `8(r10)`; ngccc folds the address to `0x10(r30)` on both
//      v10 sites.  Tried: named `__ps_t *pv10 = &arg1->v10` used at both
//      sites (current body) — still folded.  NOT a CSE problem any more, just
//      address-materialisation choice.
//  (b) retail uses r11 for `&ob.a` (`addi r11,r1,8` hoisted between
//      `cmpwi r0,2` and `bne`); got now hoists it too but picks r10, because
//      (a) frees r10.  The two are coupled — fixing (a) may fix (b).
//  (c) `fcmpu cr0,f13,f10` vs `fcmpu cr0,f12,f11`: pure FPR colouring of the
//      `.flt.hi` lane-extraction result.
//  (d) retail emits one EXTRA X-form word (0x10006090, XO=8, D@f0) that splats
//      `unk30` into BOTH lanes before the two muls0's; the draft's
//      `sc.flt.hi = unk30` yields `muls0(.., f12)` directly.  Only lane 0 is
//      ever consumed (muls0), so it is value-neutral; a full-pair splat
//      (`sc.flt.lo = sc.flt.hi = unk30`, or PS_BUILD) would likely ADD a word
//      and break the now-exact 352B size.  Not measured.
// Most promising next idea: register pins for the two surviving colour
// classes — `d1` to fr9 (retail's d1 register) and the `.flt.hi` scalar to
// fr13 — since the OP SEQUENCE is now already correct, so colouring is the
// only thing left.  One pin (`v1` -> fr12, for the short-circuit copy's phi)
// is already load-bearing in the body; adding a second is unmeasured.
//
// RULED OUT (do not redo):
//  * "the four v08 loads are CSE'd by ngccc" — false, they are +0x08/+0x10.
//  * flag ladders (-fno-schedule-insns{,2}, -fno-sched-spec, -fno-sched-
//    interblock, -fno-gcse, -fno-strength-reduce, -fno-rerun-cse-after-loop):
//    byte-for-byte no-ops or regressions (measured 2026-09-27).
//  * `volatile double _dummy` frame padding: frame is already 0x58 == retail.
//  * if/else-if or switch instead of goto-form dispatch: costs ~8 points
//    (case-0 arm gets inlined).
//  * ps_sel ICEs cc1 (optabs.c:4116); ps_div/ps_res/ps_mr-via-builtin ICE too
//    under ngccc 3.9.3 -O2 -mps-float — the lane move must come from a
//    `.flt.hi` union read, which is what the body already does.
//  * llvm-objdump/capstone MNEMONICS for opcode-4 words are VMX garbage
//    (vmsumshm/vsel/vmhaddshs); decode the raw word instead (doc-06 M5.0t).

#include "types.h"
#include "dolphin/SN_PS.h"

/* retail object: 0x08 __ps_t v08, 0x2C s32 unk2C, 0x30 f32 unk30,
 * 0x38 ptr, 0x40 P4 (4 x __ps_t = 32B) -- same layout as src/fn_800B08A4.c */
typedef struct P4 { __ps_t a; __ps_t b; __ps_t c; __ps_t d; } P4;
typedef struct Obj {
    char pad00[8];
    __ps_t v08;
    __ps_t v10;
    char pad18[0x14];
    s32 unk2C;
    f32 unk30;
    char pad34[4];
    void *unk38;
    char pad3C[4];
    P4 pair;
} Obj;
/* volatile on both halves: fn_80007A4C writes 16B through this pointer and
 * retail's dead-slot stores only survive for memory-resident MODE_PS. */
typedef struct Out { volatile __ps_t a; volatile __ps_t b; } Out;

extern __ps_t lbl_80298778;   /* .rodata2 0x80298778 = {0.0f, 0.0f} zero pair */
extern f32 lbl_802987B4;      /* .rodata2 0x802987B4 = 0.0f   (eps compare)  */
extern f32 lbl_802987B8;      /* .rodata2 0x802987B8 = 1.0f   (inv.lo)       */

s32 fn_800B090C(Obj *, void *);
void fn_80007A4C(void *, void *, void *);

s32 fn_800B0A08(void *arg0, Obj *arg1, __ps_t *arg2) {
    Out ob;
    volatile __ps_t t18;
    volatile __ps_t t20;
    volatile __ps_t u3;
    volatile __ps_t u4;
    SN_PS_type inv;
    SN_PS_type sc;
    register __ps_t v1 __asm__("fr12");
    __ps_t *op;

    if (fn_800B090C(arg1, arg2) != 0) {
        ((__ps_t *)arg0)[0] = arg2[0];
        v1 = arg2[1];
    } else {
        /* goto-form so the case-0 arm lands out of line with a `beq`,
         * matching retail's block order and branch polarity. */
        if (arg1->unk2C == 0) {
            goto c0;
        }
        op = &ob.a;
        if (arg1->unk2C != 2) {
            goto j;
        }
        {
            __ps_t d1;
            __ps_t d0;
            __ps_t sq;
            __ps_t *pv10 = &arg1->v10;
            SN_PS_type len2;

            /* d1 = src[1] - mover.v10, d0 = src[0] - mover.v08  (TWO fields!) */
            t20 = d1 = __builtin_ps_sub(arg2[1], pv10[0]);
            t18 = d0 = __builtin_ps_sub(arg2[0], arg1->v08);
            /* len2 = |d0|^2 + |d1|^2 (3 components; merge00 drops one) */
            sq = __builtin_ps_mul(d1, d1);
            sq = __builtin_ps_merge00(sq, lbl_80298778);
            len2.ps = __builtin_ps_madd(d0, d0, sq);
            len2.ps = __builtin_ps_sum0(len2.ps, len2.ps, len2.ps);
            if (len2.flt.hi > lbl_802987B4) {
                inv.ps = __builtin_ps_rsqrte(len2.ps);
                t18 = __builtin_ps_muls0(d0, inv.ps);
                inv.flt.lo = lbl_802987B8;   /* {inv, 1.0f} */
                t20 = __builtin_ps_mul(d1, inv.ps);
            }
            /* out[0] = v08 + d0 * sc,  out[1] = v10 + d1 * sc */
            sc.flt.hi = arg1->unk30;
            t18 = __builtin_ps_muls0(t18, sc.ps);
            t20 = __builtin_ps_muls0(t20, sc.ps);
            op[0] = u3 = __builtin_ps_add(arg1->v08, t18);
            u4 = __builtin_ps_add(pv10[0], t20);
            op[1] = u4;
        }
        goto j;
    c0:
        fn_80007A4C(&arg1->pair, arg2, &ob);
    j: ;
        ((__ps_t *)arg0)[0] = ob.a;
        v1 = ob.b;
    }
    ((__ps_t *)arg0)[1] = v1;
    return (s32)arg0;
}
