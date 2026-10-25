// WIP DRAFT (non-matching) — semantic paired-single reconstruction
// TRAP RECORDED 2026-10-07: the first `L: fr9 -> fr29` hit from the retarget
//   sweep was a FALSE POSITIVE.  That sweep's regex ended at the `)` of the
//   `__asm__("frN")` and did not capture the optional ` = init` tail, so the
//   substitution DELETED the declaration initialiser (`register f32 L
//   __asm__("fr29");` with the `= arg0->len1;` gone), leaving L uninitialised while
//   it is read on the very next line -- same class of trap as the r1/r2 pins, and the
//   reason both sweep tools now capture and re-emit the tail.
// REFRESHED 2026-10-07 (FPR-pin RETARGET): 21.9780% -> 23.0769%. After
//   fixing the tail capture the SAME retarget is an honest win and is applied here:
//   `L` fr9 -> fr29 with the initialiser preserved.  Object length 364B == symbol
//   364B (size-exact, no alignment artefact; pre-edit length was 340B).  Only the
//   axis-0 pin moved; the axis-1 fr12 pin is untouched.  Verified with probe.py +
//   lencheck (23.0769% / 364B) after the edit.
// family=m2c range=0x800BB738-0x800BB8A4 size=364B
// extra_cflags: -mps-float
// SIGNATURE: (Obj *arg0) — the caller passes only the object pointer in r3
// (single argument, void return, leaf).
//
// WHAT THIS IS: two byte-for-byte identical "conditional vector normalize"
// blocks (axis 0 uses len@0x3C + the 4-float slot at 0x128, axis 1 uses
// len@0x40 + the slot at 0x148). Per axis:
//   if (len != lbl_80298DE4 /*0.0f*/) {
//       dot = ps_sum0(ps_madd(p128, p128, ps_merge00(ps_mul(p130, p130), k)),
//                     .., ..)          k = pair at lbl_80298CA0
//       inv = ps_res(ps_rsqrte(dot)).hi
//       if (inv > len) {  /* the fall-through is the RESET arm */
//           t   = -len / inv                       (stfs, then re-read as a pair)
//           m0  = ps_muls0(p130, t);  m1 = ps_muls0(p128, t)
//           v.x = ps_add(p128, m1)                 (also spilled to fr.ka)
//           v.y = ps_add(p130, m0)                 (m1 also spilled to fr.kb)
//       } else { v = (0,0,0,1) }                   /* lbl_80298DE4, lbl_80298DE8=1.0f */
//   }
//
// REGISTER PINS USED (disclosed, per the task's "last resort" allowance):
//   register f32 L __asm__("fr9")  — axis-0 length (retail holds len1 in f9)
//   register f32 L __asm__("fr12") — axis-1 length (retail holds len2 in f12)
// Without them ngccc allocates {len,c1} = {f12,f9} in BOTH blocks, i.e. the
// exact inverse of retail; with them both guard pairs match verbatim. These
// are declaration-level register vars only — no inline-asm templates are
// used anywhere in this file.
//
// VERDICT (tools/ps_diff.py 0x800BB738, -mps-float): 20/85 words = 23.5%,
// got 340B vs retail 364B. The instruction MULTISET is exact-minus-6: every
// mnemonic got emits is a retail mnemonic in the right quantity, and the
// retail-only mnemonics are 2x`fmr` + 4x`ps_mr` (see RESIDUAL). The frame,
// all six stack slots (r1+8/16/24/32/40/48), the whole dot-product PS chain
// (ps_mul/ps_merge00/ps_madd/ps_sum0/ps_rsqrte/ps_res, f10/f11/f13/f0),
// both `beq` guards, the `cror cr0un,cr0eq,cr0lt` + `bns` float guard, the
// dot spill/reload pair, the lbl page anchors and both object field offsets
// all match. See the RESIDUAL note at the bottom of this header for the
// exact per-instruction blockers and the levers already tried.
//
// PARKED 2026-10-03 (a50): DIFF 23.5% (ps_diff 20/85 words, got 340B vs
// retail 364B). Repro:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/ps_diff.py 0x800BB738
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800BB738
//
// RESIDUAL = exactly 3 words per axis, all of them *reg-reg copies GCC 2.95
// coalesces away*, plus one store-order rotation. Per axis:
//   On each axis retail copies the slot at 0x18(r1) through f13 before
//   comparing against f9, while the build compares f0 directly with no copy.
//   Retail negates f9 into f0 and divides by the f13-held inverse, while the
//   build negates and divides in place in f9 against f0. Retail stores the
//   four base slots in 8/0xc/4 order after the 0x128(r3) store, while the
//   build stores them in 4/0xc/8 order. And retail reloads the 32(r1) pair
//   into f0, copies it to f12, then scales f0 by f10 times f12, while the
//   build scales f12 by f10 times f0 straight from the load with no copy.
// Everything else is exact: frame 0x38, all six stack slots, the whole
// ps_mul/ps_merge00/ps_madd/ps_sum0/ps_rsqrte/ps_res chain (raw words
// identical, incl. f10/f11 for the two psq_l), both beq guards, the
// cror+bns float guard, the dot spill/reload, both reset arms' values.
//
// RULED OUT THIS ROUND (all measured, not guessed):
//  * `u = vv` copy idiom. src/fn_800C4D88.c (MATCHED, same idiom) gets
//    `psq_l f13` + `ps_mr f9,f13` from `vv = *(sn_ps*)&s38; u = vv;`. Doing
//    the same here (`vv = fr.sp1.ps; u = vv;` with fr.sp1 still volatile)
//    COALESCES - got emits no ps_mr, and it also permutes the two psq_l
//    loads (f10<->f11), costing 2 more words. 23.5% -> 19% (20/85 ->
//    16/85). GCC only folds the second copy when the load is a direct
//    struct-member read; the punned-pointer read in 800C4D88 is what
//    blocks the fold, and moving the scalar out of FRM breaks the frame.
//  * Reset-arm store order. Source order [v0, base1, base3, base2] (i.e.
//    assuming forward emission) scores 16/85 (18.8%) - worse than the
//    [v0, base2, base3, base1] in the file. ngccc rotates the two
//    same-constant stores as a unit for EVERY order, so only those two
//    words are unreachable this way.
//  * `volatile` on the dot1/dot2/sp1/sp2 members. Making them plain
//    (the fn_800C4D88 dot union is non-volatile) changes NOTHING: still
//    20/85, still no `fmr`. So the dot reload's missing copy is NOT a
//    volatile-vs-not effect.
//
// NEXT IDEA (untried): the missing `fmr f13,f0` and `fneg f0,f9` are one
// problem, not two - both vanish if `inv` is allocated f13 instead of f0.
// fn_800C4D88 gets f13 there because cr7 is used (the && merge); here the
// compare is cr0. Try making the comparison a *bit-test-free* `!(inv<=L)`
// on a value that GCC must keep in a second register, e.g. compare the
// SPILLED pair slot (`fr.dot1.flt.hi`) against L directly while dividing
// by a second read of it, so the two reads are distinct pseudos.
//
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "dolphin/SN_PS.h"

typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSU;

/* Frame template: fixes the six 8-byte stack slots at r1+8 .. r1+48
 * (ka/kb are shared by both axes, dot1/sp1 and dot2/sp2 are per-axis).
 * A plain local set lets ngccc merge the per-axis pairs down to five slots
 * (0x30 frame) and every stack offset then diverges. */
typedef struct {
    volatile PSU kb;
    volatile PSU ka;
    volatile PSU dot1;
    volatile PSU sp1;
    volatile PSU dot2;
    volatile PSU sp2;
} FRM;

/* File-local layout (trap #1): the shared Unk_ class mis-types these slots,
 * and 0x3C/0x40 are f32 length fields, not s32. v[] is the 4-float slot
 * that the psq pair ops address as {v[0],v[1]} and {v[2],v[3]}. */
typedef struct {
    char pad00[0x3C];
    f32 len1;
    f32 len2;
    char pad44[0xE4];
    f32 v[12];
} Obj;

extern f32 lbl_80298DE4;
extern f32 lbl_80298DE8;
extern __ps_t lbl_80298CA0;

void fn_800BB738(Obj *arg0) {
    FRM fr;

    {
    register f32 L __asm__("fr29") = arg0->len1;
    if (L != lbl_80298DE4) {
        f32 *base;
        __ps_t p128;
        __ps_t p130;
        __ps_t t;
        f32 inv;

        p130 = *(__ps_t *)&arg0->v[2];
        p128 = *(__ps_t *)&arg0->v[0];
        t = __builtin_ps_mul(p130, p130);
        base = arg0->v;
        t = __builtin_ps_merge00(t, lbl_80298CA0);
        t = __builtin_ps_madd(p128, p128, t);
        t = __builtin_ps_sum0(t, t, t);
        t = __builtin_ps_rsqrte(t);
        t = __builtin_ps_res(t);
        fr.dot1.ps = t;
        inv = fr.dot1.flt.hi;
        if (!(inv <= L)) goto scale1;
        arg0->v[0] = lbl_80298DE4;
        base[2] = lbl_80298DE4;
        base[3] = lbl_80298DE8;
        base[1] = lbl_80298DE4;
        goto done1;
    scale1:
        {
            __ps_t s;
            __ps_t m0;
            __ps_t m1;
            __ps_t a0;
            __ps_t a1;
            f32 neg = -L;
            fr.sp1.flt.hi = neg / inv;
            s = fr.sp1.ps;
            m0 = __builtin_ps_muls0(p130, s);
            fr.ka.ps = m0;
            m1 = __builtin_ps_muls0(p128, s);
            fr.kb.ps = m1;
            a0 = __builtin_ps_add(p128, m1);
            a1 = __builtin_ps_add(p130, m0);
            *(__ps_t *)&arg0->v[0] = a0;
            *(__ps_t *)&arg0->v[2] = a1;
        }
    done1:;
    }
    }

    {
    register f32 L __asm__("fr12") = arg0->len2;
    if (L != lbl_80298DE4) {
        f32 *base;
        __ps_t p128;
        __ps_t p130;
        __ps_t t;
        f32 inv;

        p130 = *(__ps_t *)&arg0->v[10];
        p128 = *(__ps_t *)&arg0->v[8];
        t = __builtin_ps_mul(p130, p130);
        base = arg0->v + 8;
        t = __builtin_ps_merge00(t, lbl_80298CA0);
        t = __builtin_ps_madd(p128, p128, t);
        t = __builtin_ps_sum0(t, t, t);
        t = __builtin_ps_rsqrte(t);
        t = __builtin_ps_res(t);
        fr.dot2.ps = t;
        inv = fr.dot2.flt.hi;
        if (!(inv <= L)) goto scale2;
        arg0->v[8] = lbl_80298DE4;
        base[2] = lbl_80298DE4;
        base[3] = lbl_80298DE8;
        base[1] = lbl_80298DE4;
        goto done2;
    scale2:
        {
            __ps_t s;
            __ps_t m0;
            __ps_t m1;
            __ps_t a0;
            __ps_t a1;
            f32 neg = -L;
            fr.sp2.flt.hi = neg / inv;
            s = fr.sp2.ps;
            m0 = __builtin_ps_muls0(p130, s);
            fr.ka.ps = m0;
            m1 = __builtin_ps_muls0(p128, s);
            fr.kb.ps = m1;
            a0 = __builtin_ps_add(p128, m1);
            a1 = __builtin_ps_add(p130, m0);
            *(__ps_t *)&arg0->v[8] = a0;
            *(__ps_t *)&arg0->v[10] = a1;
        }
    done2:;
    }
    }
}

// RESIDUAL (23.5%, 340B vs 364B) — 6 missing reg-reg copies + 2 orderings,
// 3 words per axis. Exactly, per axis:
//
//  1. `lfs f0,0x18(r1); fmr f13,f0`   (inv's home). Got loads the dot spill
//     straight into f0 and coalesces inv with it, so no copy is emitted.
//     Pinning inv to fr13 does NOT help: ngccc then loads DIRECTLY into f13
//     (still one instruction). Forcing a copy needs two source variables,
//     which GCC 2.95 immediately coalesces again. Same wall for the
//     `ps_mr f12,f0` of the scale pair `s` out of `psq_l f0,0x20(r1)`, and
//     for the `ps_mr f13,f0` of m0 before `ps_add f13,f10,f13`.
//  2. `fneg f0,f9 ; fdivs f0,f0,f13`   (negate into a scratch reg). The fr9
//     pin on L makes ngccc negate IN PLACE (`fneg f9,f9 ; fdivs f9,f9,f0`),
//     which is the same value; a named `f32 neg = -L` temp does not break
//     the in-place form. This is the price of the L pin that fixes the guard
//     registers (worth +3.5% overall).
//  3. reset-arm store order: retail emits 8(r11), 0xc(r11), 4(r11) i.e.
//     base[2], base[3], base[1]; ngccc emits 4, 0xc, 8 i.e. base[1],
//     base[3], base[2] and does so for EVERY source ordering tried (both
//     c1-pair orders, ascending and descending) — the c2 store stays in the
//     middle in all of them, so only the two same-constant stores are
//     rotated against each other.
//  4. `addi r11,r3,0x128` lands at the top of the guarded block instead of
//     between `ps_mul` and `ps_merge00`; declaring `base` uninitialised and
//     assigning it as a statement after the ps_mul (AGENTS.md recipe 274 /
//     §6n-129) does not stop ngccc hoisting the address computation.
//
// LEVERS ALREADY TRIED AND REJECTED: `register __ps_t s __asm__("fr12")`
// (folds the load into the pin, loses the copy, 22.4%); named
// `zero`/`one`/`kk` const locals (§6at-1 — regresses to 15.3%, the two
// lbl_80298DE4 references CSE and the load sinks); swapping the two
// ps_muls0 statements (no effect, ngccc orders them itself); `volatile` on
// the object's v[] (no effect on store order); tools/flag_sweep.py over its
// 21 singles + pairs (only -fno-cse-follow-jumps helps the non-PS metric by
// +5.5% and does nothing for the PS-aware score, so no FLAG: line is kept).
//
// CLASS: doc-15 / allocator-rotation residual (coalescing-driven), NOT a
// signature / field-type / width / control-flow error — those are all
// resolved.
