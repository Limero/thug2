// PARKED 2026-09-28 (b2_06): best 60.3% (was 60.3%). PS lerp helper. 73 diff words, ~55 of
// them ONE FPR-colouring global allocation tie-break (want t in fr6, cc1 gives fr7, cascading
// through all 4 byte-lerps + the field loads). Prior agent swept 8 declaration orders x 24
// load orders + frN pins (strictly worse) + flags — not steerable from C. Three smaller
// residuals: cror+bns for the t<f10 test (no C spelling yields it with want's block order),
// v0/v1 stack-slot store order, and an lfs/lwz 2-word window. Family: FPR regalloc + doc-15.
// See the full analysis below.
// fn_800B77A0 @ 0x800B77A0 — full hand rebuild from disasm (2026-09-27).
// VERDICT: 111/184 insns (60.3%) masked, SIZE-EXACT (retail 736B / compiled
//   .text 0x2E0 = 736B), no register pins, no inline asm, one per-object
//   flag (-mps-float, marker at the bottom).
//   tools/test_wip_drafts.py --addr 0x800B77A0 -> NEAR 60.3%.
// WHAT THIS IS (semantics, all recovered from the disasm):
//   A "lerp a packed value" helper on a light/param object:
//     t  = (f32)u32[arg0->unk0x4C+0x20] / (f32)u32[arg0->unk0x4C+0x24]
//     if (arg0->unk0x48 != -1.0f)                       /* lbl_80298B58      */
//         t = (t < arg0->unk0x48) ? t/arg0->unk0x48
//                                : (t-arg0->unk0x48)/(1.0f-arg0->unk0x48);
//     v0 (4 bytes @+0x21) and v1 (4 bytes @+0x29) are the two endpoints of a
//     BYTEWISE lerp; arg0+0x25 replaces one of them when the rescale happens.
//     The 4 result bytes go to sub->unk0x28, and the four f32 fields
//     0x30/0x38/0x3C/0x44 (with 0x34/0x40 substituted on rescale) are lerped
//     into sub->unk0x24, sub->unk0x1C and sub->unk0x20 (= 1/f5, or 1e10 when
//     f5 == 0.0f).  A 16-byte psq pair copy runs obj->unk0x0C+0x58 ->
//     sub+8.  Sibling src/fn_800B7A80.c (Script dynamic-light command) is the
//     same family and is already byte-identical.
// FIXES THAT MATTERED (each was worth 5-12 words):
//   1. The two (f32)(f64)u32 conversions in WANT have NO `xoris`, so the
//      source operand is UNSIGNED (m2c's `(s32)` spelling was wrong).
//   2. `t*(b-a)+a` is RE-ASSOCIATED by cc1 into `t*(a-b)+b` (one extra `fmr` +
//      wrong fsubs/fmadds operand order in all four byte lerps).  Writing the
//      addend FIRST — `a + t*(b-a)` — blocks the rewrite and reproduces
//      WANT's `fsubs f0,f0,f13 / fmadds f0,t,f0,f13` verbatim.  38.8% -> 47.9%.
//   3. Typing the receiver + the +0x1C sub-object + the +0x4C source with
//      FILE-LOCAL typedefs (real f32 / real offsets) instead of the shared
//      Unk_* mega-classes: the frame, the stack slots (v0@0x8, v1@0xc,
//      col@0x10, cvt@0x20) and the whole prologue all fall out.  6.5% -> 39%.
//   4. The final `f5 == 0.0f ? 1e10 : 1/f5` must be written INVERTED
//      (`if (f5 != 0.0f) 1/f5 else 1e10`) to get WANT's `beq` to the
//      out-of-line 1e10 block instead of `bne`.
//   5. The last two float stores go through a local `q = arg0->unk0x1C` so
//      cc1 CSEs the pointer for sub->0x1C and sub->0x20 (WANT loads
//      0x1c(r31) once at 0x800B7A3C and reuses r3); the 0x28 and 0x24 stores
//      stay inline so GCC still reloads for them, exactly like WANT.
//      54.8% -> 60.3% AND -2 instructions (744B -> 736B, size-exact).
//   6. The psq pair copy DOES need per-object -mps-float (marker below): with
//      it the compiled .text is 736B == retail; without it cc1 emits 6 extra
//      instructions (760B) around the 16-byte copy.  Safe here because this
//      function saves NO FPR (stmw r25..r31 only), so the §4c +8 FPR-frame
//      quirk cannot fire; the flag must stay per-object, never in cflags_game.
// RESIDUAL (73 words) — one root cause + three small ones:
//   (a) FPR COLOURING, worth ~55 of the 73.  WANT's t lives in fr6; cc1 gives
//       it fr7, and that single difference cascades: every later use of t
//       (all 4 byte lerps' fmadds) and the four 0x30/0x38/0x3C/0x44 field
//       loads (WANT fr4/fr3/fr5/fr9, got fr5/fr3/fr6/fr4) are shifted with it,
//       as are the byte-1..3 `fctiwz` destination registers (WANT fr8/fr7,
//       got fr9/fr8).  The set of 12 FPRs used is IDENTICAL to WANT's, so this
//       is a permutation of the same allocation, not a missing/extra value.
//       Not steerable from C: 8 declaration orders x 24 load orders, decl-init
//       form, num/den temporaries, `f32*` base walk, array-typed float field,
//       two-statement divide, all 5 `-fno-schedule*` / `-fno-gcse` /
//       `-fno-expensive-optimizations` / `-O1` / `-O3` flags, and frN
//       `register ... __asm__("frN")` pins on t/f4/f3/f5/f9/f10 (p1..p5) all
//       leave t in fr7 or shift the whole map and lose 6-18 words.  Pure
//       global-register-allocation tie-break; the pins version was strictly
//       worse so NO pins are used.
//   (b) 0x800B7858/0x800B785C: WANT has `cror cr0un,cr0eq,cr0lt / bns` for
//       the `t < f10` test.  `if (!(t <= f10))` DOES produce the cror but
//       with `bso` and the two arms laid out mirrored; `if (t < f10)` /
//       `if (t <= f10)` / `if (t > f10)` / `if (!(t > f10))` all fold to
//       blt/ble/bgt and drop the cror.  No C spelling yields cror+bns with
//       WANT's block order (all 6 forms measured).
//   (c) 0x800B789C/0x800B7894: the v0/v1 STACK SLOTS.  The two default stores
//       and the two in-if stores are each individually right, but cc1 orders
//       the two conditional stores inversely to WANT unless the default pair
//       is swapped, and the default LOAD order flips with it.  2 vs 3 words;
//       the current spelling is the better of the two.
//   (d) 0x800B7A9C/0x800B7AA0: `lfs f0,0.0f` and the `lwz/stfs` of sub->0x1C
//       come out in the opposite order (a 2-word window, count unchanged).
// NOT PROMOTED.  Pool note: the synthesized 2^52 double lands in the object's
//   own `.rodata` (8B) — fine, because tools/fix_fp_pool.py retargets that
//   HA/LO pair onto lbl_80298B50, which is already real C data in
//   src/r2d_80298B4C.c (splits.txt `.rodata2 0x80298B4C-0x80298B78`).  The
//   §4n doc-14 "pool must be in .rodata2" blocker does NOT apply here.
// WIP DRAFT (non-matching) — INERT: not in splits.txt/configure.py.
// family=m2c range=0x800B77A0-0x800B7A80 size=736B
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0[0x1C];
    f32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    s32 unk0x28;
    s32 unk0x2C;
} B77A0_SUB;

typedef struct {
    char pad0[0x20];
    s32 unk0x20;
    s32 unk0x24;
} B77A0_SRC;

typedef struct {
    char pad0[0x0C];
    char *unk0x0C;
    char pad1[0x0C];
    B77A0_SUB *unk0x1C;
    char pad2[0x10];
    f32 unk0x30;
    f32 unk0x34;
    f32 unk0x38;
    f32 unk0x3C;
    f32 unk0x40;
    f32 unk0x44;
    f32 unk0x48;
    B77A0_SRC *unk0x4C;
} B77A0_T;

extern f32 lbl_80298B58;
extern f32 lbl_80298B5C;
extern f32 lbl_80298B60;
extern f32 lbl_80298B64;
B77A0_SUB *fn_800596E4(s32);
void fn_800B77A0(B77A0_T *arg0) {
    s32 v1;
    s32 v0;
    f32 t;
    f32 f4;
    f32 f3;
    f32 f5;
    f32 f9;
    f32 f10;
    struct {
        s8 c0;
        s8 c1;
        s8 c2;
        s8 c3;
    } col;
    B77A0_SUB *sub;
    B77A0_SUB *q;
    __ps_t *ps;
    __ps_t *pd;

    if (arg0->unk0x1C == (B77A0_SUB *)0) {
        sub = fn_800596E4(1);
        arg0->unk0x1C = sub;
        sub->unk0x2C = *(s32 *)((char *)arg0->unk0x0C + 0x18);
    }
    t = (f32) (f64) *(u32 *)((char *)arg0->unk0x4C + 0x20) / (f32) (f64) *(u32 *)((char *)arg0->unk0x4C + 0x24);
    v0 = *(s32 *)((char *)arg0 + 0x21);
    v1 = *(s32 *)((char *)arg0 + 0x29);
    f4 = arg0->unk0x30;
    f3 = arg0->unk0x38;
    f5 = arg0->unk0x3C;
    f9 = arg0->unk0x44;
    f10 = arg0->unk0x48;
    if (f10 != lbl_80298B58) {
        if (!(t < f10)) {
            v0 = *(s32 *)((char *)arg0 + 0x25);
            t = (t - f10) / (lbl_80298B5C - f10);
            f4 = arg0->unk0x34;
            f5 = arg0->unk0x40;
        } else {
            v1 = *(s32 *)((char *)arg0 + 0x25);
            t = t / f10;
            f3 = arg0->unk0x34;
            f9 = arg0->unk0x40;
        }
    }
    col.c0 = (s8) ((f32) (f64) (u8) ((u8 *) &v0)[0] + t * ((f32) (f64) (u8) ((u8 *) &v1)[0] - (f32) (f64) (u8) ((u8 *) &v0)[0]));
    f9 = t * (f9 - f5) + f5;
    col.c1 = (s8) ((f32) (f64) (u8) ((u8 *) &v0)[1] + t * ((f32) (f64) (u8) ((u8 *) &v1)[1] - (f32) (f64) (u8) ((u8 *) &v0)[1]));
    f5 = t * (f3 - f4) + f4;
    col.c2 = (s8) ((f32) (f64) (u8) ((u8 *) &v0)[2] + t * ((f32) (f64) (u8) ((u8 *) &v1)[2] - (f32) (f64) (u8) ((u8 *) &v0)[2]));
    col.c3 = (s8) ((f32) (f64) (u8) ((u8 *) &v0)[3] + t * ((f32) (f64) (u8) ((u8 *) &v1)[3] - (f32) (f64) (u8) ((u8 *) &v0)[3]));
    ps = (__ps_t *)((char *)arg0->unk0x0C + 0x58);
    pd = (__ps_t *)((char *)arg0->unk0x1C + 8);
    pd[0] = ps[0];
    pd[1] = ps[1];
    *(s32 *)((char *)arg0->unk0x1C + 0x28) = *(s32 *)&col;
    *(f32 *)((char *)arg0->unk0x1C + 0x24) = f9;
    q = arg0->unk0x1C;
    q->unk0x1C = f5;
    if (f5 != lbl_80298B60) {
        q->unk0x20 = lbl_80298B5C / f5;
    } else {
        q->unk0x20 = lbl_80298B64;
    }
}
