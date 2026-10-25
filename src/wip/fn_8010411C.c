// WIP DRAFT (non-matching) — hand-shaped C, scored 88.0% (44/50 words)
// family=hand range=0x8010411C-0x801041E4 size=200B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED: residual is 6 words, all in three spots (see below).
//
// What matches: frame/prologue, both paired-single init rounds (scalar store
// order [2],[1],[0], the four psq_l/psq_st pairs), the branch layout, the
// whole loop tail and the epilogue.
//
// Load-bearing: `register char *b9 __asm__("r9")` — the carried `arg0+0x10`
// pointer. Pinning it is worth one word (86.0 -> 88.0): the second block's
// first psq_st now uses 16(r9). The same construct without the pin puts the
// pointer in r3 and the third const-pool base in r9.
//
// Remaining residual, with the shape each word needs:
//  * the second const-pool base (`lbl_8029C9D8`) is materialised in r11 (the
//    register the previous constant's base just died in) and scheduled after
//    b9's addi; want materialises it in r10 and before it. The two are a
//    scheduler/allocation tie: b9's addi is hoisted two slots early in this
//    build, and the free-register choice for the pool base follows it.
//  * the last block-2 store folds to `psq_st 40(r30)` (same address as
//    `24(r9)`) and swaps with the `lhz` condition load, because the folded
//    address lets it leave the block earlier.
//  * the loop call's first argument is passed as `mr r3,r31` (the loop's
//    current element pointer) where want recomputes `addi r3,r30,0x10`.
//
// Probed and inert (measured on this body, private LEAF_TMPDIR): b9 pins to
// r8/r10/r11 (86.0), a `+r` barrier on b9 before/after the assignment (88.0 /
// 25.5 - it spills and breaks the frame), moving the b9 assignment to four
// other positions (88.0 each), moving the `C = lbl_8029C9D8;` load to the top
// (60.0), and the full single-flag matrix (no flag improves on 88.0).
#include "types.h"
#include "structs.h"
extern f32 lbl_8029C9D0;
extern f32 lbl_8029C9D4;
extern f32 lbl_8029C9D8;
void fn_8000728c(void *, s32);
void fn_80104408(Unk_87891B5F *, void *);
void fn_8010411C(Unk_87891B5F *arg0, void *arg1) {
    register char *p28 __asm__("r28");
    register s32 p29 __asm__("r29");
    register char *p30 __asm__("r30");
    register char *p31 __asm__("r31");
    f32 sp8[4];
    __ps_t t0;
    __ps_t t1;
    register char *b9 __asm__("r9");
    f32 A;
    f32 B;
    f32 C;

    p30 = (char *)arg0;
    p28 = (char *)arg1;
    A = lbl_8029C9D0;
    B = lbl_8029C9D4;
    sp8[2] = A;
    b9 = p30 + 0x10;
    sp8[1] = A;
    p29 = 0;
    sp8[0] = A;
    sp8[3] = B;
    t0 = ((__ps_t *)sp8)[0];
    ((__ps_t *)p30)[2] = t0;
    t1 = ((__ps_t *)sp8)[1];
    ((__ps_t *)p30)[3] = t1;
    sp8[3] = B;
    C = lbl_8029C9D8;
    sp8[2] = C;
    sp8[1] = C;
    sp8[0] = C;
    t0 = ((__ps_t *)sp8)[0];
    ((__ps_t *)b9)[2] = t0;
    t1 = ((__ps_t *)sp8)[1];
    ((__ps_t *)b9)[3] = t1;
    if (p29 < *(u16 *)(p30 + 6)) {
        p31 = p28;
        do {
            fn_8000728c(p30 + 0x10, p31);
            p29 += 1;
            p31 += 0x10;
        } while (p29 < *(u16 *)(p30 + 6));
    }
    fn_80104408((Unk_87891B5F *)p30, (void *)p28);
}
