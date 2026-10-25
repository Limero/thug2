// family=m2c range=0x80045DC8-0x80045FA8 size=480B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-03: NEAR 84.2% (was DIFF 14.6%), .text 480B == symbols.txt size.
//
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80045DC8
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/want_vs_got.py 0x80045DC8
//
// Object has only .text (0x1E0 = 480B) + .rela.text — no private .rodata,
// 0 inline asm, 0 flags. 31 raw word diffs, of which 17 are real (the rest
// are REL14/REL24 + ADDR16_HA/LO which masked_pct covers).
//
// WHAT IS ALREADY EXACT: frame (-0x48 / stmw r24,0x18 / stw r0,0x4c), the
// whole GPR colour map (self=r30, pf=r31, eb=r29, q1=r26, q2=r25, q3=r24,
// zero=r27, ctr3=r28), both loops' shapes, all 55 block-4 store offsets and
// nearly all of their order, the epilogue.
//
// UPDATE 2026-10-18: q3 tail pair `q3->c;q3->b` -> `q3->b;q3->c` fixed the
// +17C stfs pair (84.2% -> 85.8%). The a/b float-load swap was tried and
// measured WORSE (82.5%, lis-base rotation) — reverted. Emptying the ctr2
// loop (invariants moved after) is CATASTROPHIC (DIFF: empty loop deleted,
// counter demoted to r9, regalloc churn) — the non-empty loop is load-bearing
// for the bdnz + r0 counter. Reverted. Unhandled: loop-window addi packing
// (11 words), 27E8/27F0 lfs order (2), g/h store pair (2).
//
// REMAINING DIFFS
// 1. +064..+084 (11 words, the biggest item): want has the empty 4-iteration
//    countdown loop body (`li r0,4; addi r26; mtctr r0; [addi r25][addi r24];
//    bdnz .`) and computes pf/eb AFTER the two `lfs`. Got parks pf/eb INSIDE
//    that loop body (`addi r31,0x1a0; addi r29,0x190; bdnz .`) and emits the
//    bdnz one word later, so everything in +064..+084 is shifted.
// 2. +0cc/+0d4 (2 words): the first two block-4 float loads emit in want's
//    source order (27F0, then 27E8); got emits 27E8 then 27F0 (the *registers*
//    f12/f0 are already assigned correctly — only the two lfs are swapped).
// 3. +134/+138 (2 words): the `0x570/0x574` store pair. Source order [g,h]
//    emits as [h,g]; source order [h,g] emits as [g,h] but then flips which
//    of f11/f12 each constant gets, so the two are coupled and 2 of 4 diffs
//    survive either way.
// 4. +1b4/+1b8 (2 words): q3's `0x8/0x4` store pair — same rotate-right rule
//    as (3) but for a sub-struct group; the 0x510 and 0x538 groups now match.
//
// RULED OUT (do not redo)
// * `extern f32 lbl_X;` vs `extern char lbl_X[]` + `*(f32*)` (recipes §6ek-1):
//   byte-identical object here, the colour map did not move at all.
// * Moving pf/eb out of the dummy countdown loop (so the loop body is empty
//   like want's): 84.2% -> 20.5%. It re-adds 2 reload copies
//   (`mr r29,r0` / `mr r30,r4`) => 488B AND rotates the whole colour map
//   (self back to r31). pf/eb MUST be inside that loop for r30/r31.
// * Reordering the dummy loop body ([q2,q3,pf,eb] vs [pf,eb,q2,q3]): no
//   change, GCC always keeps pf+eb as the body and hoists q2/q3.
// * `register ... __asm__("r30")` pin on the base pointer: 84.2% -> 5.8%.
//   ngccc also rejects `register` on a *parameter* (parse error), so a pin
//   has to go on a local alias, and that alias is enough to wreck the map.
// * `volatile double _dummy` x2 for the +16B frame: WORKS (frame is exact).
//   A single one gives -0x44.
// * Loop 3 as `for (c = 0x19; c; c--)` with an extra `c--` in the body:
//   emits `addic. r28,r28,-2`. The plain `do {...; ctr3--; ...} while (ctr3);`
//   form is what produces want's single mid-body `addic. r28,r28,-1` with no
//   pre-test. Do NOT "fix" that into a for-loop.
//
// MOST PROMISING NEXT IDEA
// Items 2/3/4 are all the same rule (store/load runs through one derived base
// emit rotate-right; recipes 24/64/159/206) fighting a register allocator that
// picks the FPR from the STORE order rather than the load order. The way out
// is probably to give f570/f574 and the q3 0x8/0x4 pair *different* source
// values (two distinct f32 locals both initialised from the same .rodata
// label) so the two runs stop being a "same-constant run" and stop rotating.
// Item 1 needs the loop optimizer to hoist pf/eb past an empty body, which
// may be reachable by making the countdown body's two assignments depend on
// ctr2 (e.g. indexed off the induction variable) so they are not loop
// invariant, then finding the source order that puts them back after the lfs.
#include "types.h"
#include "qb_constants.h"

extern char lbl_802927E8[];
extern char lbl_802927EC[];
extern char lbl_802927F0[];
extern char lbl_802927F4[];
extern char lbl_802927F8[];
extern char lbl_80292870[];

void fn_8003F360(void *);
void CObject_RemoveRefLink(void *, void *);
void fn_8009E274(void *, s32);

/* 0x20-byte link node + transform slot at self+0x190 */
typedef struct {
    s32 pRef;
    s32 pPrev;
    s32 pNext;
    s32 padC;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} b28_Elem;

/* 0x10-byte 4-float sub-struct used at +0x510 / +0x538 / +0x558 */
typedef struct {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
} b28_Quad;

typedef struct {
    char pad0[0x8];
    void *vtbl;
    char padC[0x184];
    b28_Elem e[25];
    s32 z4b0;
    f32 f4b4, f4b8, f4bc, f4c0, f4c4, f4c8, f4cc;
    f32 f4d0, f4d4, f4d8, f4dc;
    f32 f4e0, f4e4, f4e8, f4ec, f4f0, f4f4, f4f8, f4fc;
    f32 f500, f504, f508, f50c;
    b28_Quad q510;
    s32 z520, z524, z528;
    char pad52c[0xC];
    b28_Quad q538;
    char pad548[0x10];
    b28_Quad q558;
    f32 f568;
    s32 z56c;
    f32 f570, f574;
    s32 z578, z57c, z580;
    char pad584[0x4];
    f32 f588;
    s32 z58c;
} b28_Self;

void *fn_80045DC8(b28_Self *arg0) {
    volatile double _dummy;
    volatile double _dummy2;
    b28_Elem *e;
    b28_Elem *eb;
    f32 *pf;
    b28_Quad *q1;
    b28_Quad *q2;
    b28_Quad *q3;
    s32 ctr;
    s32 ctr2;
    s32 ctr3;
    f32 v0;
    f32 v1;
    f32 a;
    f32 b;
    f32 c;
    f32 g;
    f32 h;

    fn_8003F360(arg0);
    arg0->vtbl = lbl_80292870;
    e = (b28_Elem *)((char *)arg0 + 0x190);
    for (ctr = 0x19; ctr != 0; ctr--) {
        e->pPrev = 0;
        e->pNext = 0;
        e->pRef = 0;
        e++;
    }
    q1 = (b28_Quad *)((char *)arg0 + 0x510);
    for (ctr2 = 4; ctr2 != 0; ctr2--) {
        pf = (f32 *)((char *)arg0 + 0x1A0);
        eb = (b28_Elem *)((char *)arg0 + 0x190);
        q2 = (b28_Quad *)((char *)arg0 + 0x538);
        q3 = (b28_Quad *)((char *)arg0 + 0x558);
    }
    v0 = *(f32 *)lbl_802927E8;
    v1 = *(f32 *)lbl_802927EC;
    ctr3 = 0x19;
    do {
        if (((b28_Elem *)(pf - 4))->pRef != 0) {
            CObject_RemoveRefLink((void *)((b28_Elem *)(pf - 4))->pRef, (void *)eb);
            ((b28_Elem *)(pf - 4))->pRef = 0;
        }
        ((b28_Elem *)(pf - 4))->pRef = 0;
        eb++;
        pf[0] = v0;
        ctr3--;
        pf[1] = v0;
        pf[2] = v0;
        pf[3] = v1;
        pf += 8;
    } while (ctr3 != 0);
    a = *(f32 *)lbl_802927F0;
    b = *(f32 *)lbl_802927E8;
    c = *(f32 *)lbl_802927EC;
    arg0->f4b4 = a;
    arg0->z524 = 2;
    arg0->f4b8 = b;
    arg0->f4bc = b;
    arg0->f4c0 = b;
    arg0->f4c4 = b;
    arg0->f4c8 = b;
    arg0->f4cc = b;
    arg0->q510.a = b;
    arg0->z4b0 = ctr3;
    arg0->z520 = ctr3;
    h = *(f32 *)lbl_802927F8;
    g = *(f32 *)lbl_802927F4;
    q1->b = b;
    q1->c = b;
    q1->d = c;
    arg0->f570 = g;
    arg0->f574 = h;
    arg0->f588 = b;
    arg0->f568 = c;
    arg0->f4d0 = c;
    arg0->f4d4 = b;
    arg0->f4d8 = b;
    arg0->f4dc = b;
    arg0->z528 = ctr3;
    arg0->z57c = ctr3;
    arg0->z580 = ctr3;
    arg0->z578 = ctr3;
    arg0->z56c = ctr3;
    arg0->z58c = ctr3;
    arg0->f4e0 = b;
    arg0->f4e4 = c;
    arg0->f4e8 = b;
    arg0->f4ec = b;
    arg0->f4f0 = b;
    arg0->f4f4 = b;
    arg0->f4f8 = c;
    arg0->f4fc = b;
    arg0->f500 = b;
    arg0->f504 = b;
    arg0->f508 = b;
    arg0->f50c = c;
    arg0->q538.a = b;
    q2->b = b;
    q2->c = b;
    q2->d = c;
    arg0->q558.a = b;
    q3->b = b;
    q3->c = b;
    q3->d = c;
    fn_8009E274(arg0, QB_ELEMENT3D);
    return arg0;
}