// PARKED 2026-10-30: 2.7% -> 76.5% (object 204B == want 204B, size-exact)
//
// RESIDUAL: 12 of 51 words differ, in two independent clusters.
//  (1) REGISTER COLOUR (6 words): the 0x96969600 front-end literal takes r11 in
//      GOT but r10 in want; consequently the 2nd page anchor (0x80297310) takes
//      r10 in GOT but r11 in want.  The four 0x8029xxxx anchors and the literal
//      compete for the preference order {r9, r11, r10, r8, r7}: want gives the
//      literal the 3rd slot (2 anchors allocated first), GOT the 2nd (1 anchor
//      first).  MEASURED AND INERT: moving the literal's whole statement after
//      the float loads / after any of 7 individual stores (8 placements, all
//      76.5% or worse, 1 variant DIFF 11.8%); `volatile s32 v150` 3.8%;
//      file-scope W8 76.5%; swapping the `li 0xff` and the literal births 70.6%.
//      This is AGENTS §6ff's "reload anchor allocated before a front-end local,
//      so the local lands one slot off" in a SCRATCH register, not a callee-saved
//      one - no source shape tried moves the literal's slot, and a hard pin is
//      untried (see "next lever" below).
//  (2) STORE ORDER (6 words): want emits  160,16C,154,17C,150,184,1B8,178,164,170,158
//      GOT emits                  160,16C,1B8,17C,154,184,150,158,164,170,178.
//      The float stores rotate right within their value class and the
//      non-head members are DEFERRED to a second group, in source LUID order
//      (measured model, exact on 4 different orderings).  That H++T model cannot
//      produce want's order, because want has the int singleton 0x158 AFTER the
//      deferred float tails while every GOT variant puts it in the head group.
//      MEASURED: recipe-280 plateau walk over all 11 non-zero stores, 2 seeds,
//      ~20 rounds, 110 swap/cut neighbours per round, 12 workers - hard plateau
// at 76.5% initially. Hand candidates 'want-order' 64.7%, 'allrev' 66.7%
//      (pre-colour-fix), 4 others 64.7-66.7%.  DO NOT re-run the walk.
//
// SEMANTIC FIXES THAT MATTERED (2.7% -> 76.5%, all plain C):
//  * CALLEE ARITY AUDIT (AGENTS §6bf/§6di/§6ea-143).  m2c called
//    fn_800953AC with EIGHT args (0xFF, 0x80290000, 0x80290000, 1, ...).  The
//    promoted `src/fn_800953AC.c` shows it is `void fn_800953AC(void)` and
//    `src/fn_800964EC.c` (its only callee) is `void fn_800964EC(void)` - it
//    reads no argument register at all.  m2c's 8 phantom args each cost a
//    `crclr cr1eq` plus an `lis`/`addi` for the fabricated 0x80290000 literals.
//    fn_80092F2C is a 4-byte `blr` stub = 0-arg; fn_80023F94 is 1-arg
//    (`mr r28,r3`) and takes 0x73800.  Those 3 signatures are also in src/.
//  * FIELD WIDTHS (AGENTS §6eh2 TELL 1).  The seven `stfs` sites (0x160, 0x164,
//    0x16C, 0x170, 0x178, 0x17C, 0x184) were `s32` lvalues in the m2c draft, so
//    every float store compiled to `fctiwz`+`stfd`+`lwz`+`stw` - 4 surplus
//    instructions per site and an 8-byte-inflated frame.  `f32 *` lvalues.
//  * BASE SYMBOL (hazard 277).  The `(char *)0x8037B5E8 + off` literal became
//    `extern char lbl_8037B5E8[]` (a real `.bss` entry, size 0x28) held in a
//    named `char *o`, which gives want's `lis r30; addi r30,-0x4a18` pair and
//    also un-shares the 19 `base+off` address webs (§6dn/§6bf-4).
//  * THE DEAD `rlwimi` (0x150).  m2c read the word as `0x96969600 | 0xFF`.
//    Raw decode: `0x50CA063E` = `rlwimi r10, r6, 0, 24, 31` (BE layout, not
//    capstone's MB/ME field numbering) = an 8-bit bitfield insert of `r6`=0xFF
//    into LSB bits 0..7, so the stored value is 0x969696FF.  Reproduced with a
//    file-local `union { u32 w; struct { u32 hi24:24; u32 lo8:8; } b; }`; the
//    0xFF operand has to stay OPAQUE (a `__asm__("li %0,0xff" : "=r"(ff))`
//    birth) or GCC constant-folds the OR into `ori` and the word vanishes.
//    This is AGENTS §6x-89 / §6bq (want keeps a provably-dead-ish pair) plus
//    §6fp's `union` for a masked-merge + plain-constant store pair.
//
// INLINE ASM: 1 emitted instruction of 51 (`li r6,0xff`, 2.0%) - well under the
// 20% cap (§4g / recipe 180).  The `register`/barrier style would be 0, but no
// zero-code barrier reproduces this rlwimi (measured: the only zero-instruction
// form, `u.b.lo8 = 0xFF` with a `"+r"` barrier, folds the rlwimi away and
// leaves the object 1 word short).
//
// NEXT LEVER (untried): the literal's register slot wants 2 anchors allocated
// before it (want) vs 1 (GOT).  A hard `register s32 v150 __asm__("r10")` pin
// would colour the literal directly and leave the 4 anchors to take
// {r9,r11,r8,r7} = want's set - but the same pin on the 2nd anchor, or on
// `f11`, was not tried, and per §6fg/§6b6 a pin needs a single def pseudo
// (v150 has one, so it should bind).  The store-order cluster likely needs a
// different VALUE-CLASS STRUCTURE (not a permutation), e.g. splitting the three
// f0 stores across two source variables so the deferral groups change.
//
// Verified: object .text = 0xCC = 204B = symbols.txt `size:0xCC` = this header's
// range marker; only `.text` + `.rela.text` (no private .rodata, so no doc-14
// pool caveat).  NOT a 100% - parked.
// family=m2c range=0x800953CC-0x80095498 size=204B
// INERT: not registered in splits.txt/configure.py - never compiled.
#include "types.h"
extern char lbl_80297304[];
extern char lbl_80297308[];
extern char lbl_8029730C[];
extern char lbl_80297310[];
extern char lbl_8037B5E8[];
s32 fn_80023F94(s32);
void fn_800953AC(void);
void fn_80092F2C(void);
typedef union { u32 w; struct { u32 hi24:24; u32 lo8:8; } b; } W8;
void fn_800953CC(void) {
    f32 f0;
    f32 f11;
    f32 f12;
    f32 f13;
    s32 v150;
    s32 ff;
    char *o;
    W8 w;

    f0 = *(f32 *)lbl_8029730C;
    f11 = *(f32 *)lbl_80297310;
    f12 = *(f32 *)lbl_80297304;
    f13 = *(f32 *)lbl_80297308;
    o = lbl_8037B5E8;
    __asm__("li %0,0xff" : "=r"(ff));
    w.w = 0x96969600u;
    w.b.lo8 = ff;
    v150 = w.w;
    *(f32 *)((char *)o + (s32)0x160) = f12;
    *(f32 *)((char *)o + (s32)0x16C) = f13;
    *(s32 *)((char *)o + (s32)0x1B8) = 1;
    *(f32 *)((char *)o + (s32)0x164) = f11;
    *(f32 *)((char *)o + (s32)0x170) = f0;
    *(f32 *)((char *)o + (s32)0x178) = f0;
    *(f32 *)((char *)o + (s32)0x17C) = f0;
    *(s32 *)((char *)o + (s32)0x154) = 0x8F8F8FFFu;
    *(f32 *)((char *)o + (s32)0x184) = f11;
    *(s32 *)((char *)o + (s32)0x150) = v150;
    *(s32 *)((char *)o + (s32)0x158) = ff;
    *(s32 *)((char *)o + (s32)0x14C) = 0;
    *(s32 *)((char *)o + (s32)0x18C) = 0;
    *(s32 *)((char *)o + (s32)0x188) = 0;
    *(s32 *)((char *)o + (s32)0x1A8) = 0;
    *(s32 *)((char *)o + (s32)0x1AC) = 0;
    *(s32 *)((char *)o + (s32)0x1B4) = 0;
    fn_800953AC();
    fn_80092F2C();
    *(s32 *)((char *)o + (s32)0x1BC) = 0;
    *(s32 *)((char *)o + (s32)0x1C0) = 0;
    fn_80023F94(0x73800);
}
