// WIP DRAFT (non-matching) — hand-rebuilt from the retail disassembly
// family=m2c range=0x80037CF4-0x80037F88 size=660B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (store-schedule): 2.2% -> 44.85% masked (official
// verdict DIFF, want_got: got 660B = exact want size, 74/165 words match).
// WHAT IS SOLVED (all verified against the retail bytes):
//  * frame 0x30, f30/f31/r31 save set, mflr/stw order, mr r31,r3;
//  * `andis. r9,r0,0x800` + beq on arg0->unk0x0 & 0x08000000;
//  * the FIRST search loop is byte-exact for 0x80037CF4-0x80037D98
//    (guard `cmpw r10,r0/bge`, preheader `lis/lwz 0x18(r31)/lfs f13/
//    addi r11,0x30/li r9,0x40`, the 3-way 0.0f test, `lwz r4,-0x10(r11)`,
//    `add r8,r0,r9`, latch order i/off/p). The key was typing the node
//    pointer as `f32 *` and indexing f[0..2] — with a `Pos *` + `->x/y/z`
//    struct GCC emits an extra `mr r9,r11` copy and shifts the whole
//    allocation down one register (docs: strength-reduced IV duplication).
//  * `fn_8003951C(void*,s32,void*)` 3-arg prototype (no crclr), arg2 read
//    from the biased node, arg3 = (char*)arg0->unk0x4 + 0x30;
//  * the +0x30/+0x38 pair copies as `((__ps_t*)dst)[6/7] = ((__ps_t*)src)[6/7]`
//    under -mps-float (recipes M5.0c/d) — the first block's psq_l/psq_st
//    quadruple is instruction-for-instruction want's;
//  * `lbl_80291EF8`=1.0f / `lbl_80291EF4`=0.0f as f30/f31 locals kept live
//    across the call (globals in f30/f31 do NOT work — GCC reloads them
//    after the bl, breaking the second loop's `fmr f13,f31` shape);
//  * second loop: `for (k=0;k<count;k++)` with eoff=k*0x20 / moff=k*0x40
//    (NOT pre-initialised counters) so both land in the loop preheader as
//    `li r10,0` / `li r8,0` after the guard, and the node pointer biased
//    +0x10 so the three loads become `lfs 0x10/0x14/0x18` off one `add`.
// RESIDUAL (91 words) — two independent blockers, both order/allocation:
//  (1) 21 words at 0x80037D9C-0x80037DEC: the first fill block's 7-word
//      prologue. WANT `[lis r11][lwz r9,4(r31)][lfs f30][lis r10][mr r3,r31]
//      [stfs f30,0(r9)][lfs f31]`; GOT puts BOTH `lis` up front, loads
//      f31(=0.0) before f30, and sinks the mats `lwz` to last, reusing r11
//      for it. Every ordering of the one/zero/mats statements was tried
//      (6 permutations) and ngccc is invariant; the extern-vs-literal form
//      only changes which of f30/f31 loads first.
//  (2) 65 words in the two 28-store fill blocks (0x80037D9C-0x80037E44 and
//      0x80037EA4-0x80037F50). WANT's first block emits
//      00,3C,04,08,0C,10,14,18,1C,20,24,28,2C,30,34,38 and WANT's loop block
//      emits 00,30,34,3C,04,0C..2C,38. ngccc 3.9.3 applies a fixed
//      perturbation to ANY flat 16-statement source of these stores: it emits
//      src[0..4] in order, then pulls the store to offset 0x20 and the LAST
//      source store into slots 5 and 6, pushes src[1] (or src[1..3] in the
//      loop) down to slot 7, and leaves the rest ascending. Reproduced on 6
//      different source orders (forward, reverse, ascending, row-w-first)
//      plus a `volatile f32` field variant (which changes, but does not
//      remove, the perturbation). Because slot 5 is ALWAYS the 0x20 store,
//      WANT's order is unreachable from any flat 16-statement source — the
//      game's source must be structurally different (nested/row helper or a
//      struct copy), so this needs new evidence, not a permutation search.
//  (3) 5 words: loop-2 register swap (want k=r7/eoff=r8, got k=r8/eoff=r7)
//      and want's `fmr f13,f31` / `fmr f12,f30` preheader copies (got
//      re-loads 0.0f from the pool; declaring `f32 a=one,b=zero` before or
//      inside the loop gives `fcmpu …,f31` with no fmr and loses 2 words).
// RULED OUT: -fno-gcse/-fno-thread-jumps/-fno-expensive-optimizations (no
// change), -fno-cse/-fno-schedule2/-fno-crossjumping/-fno-tree-* (rejected
// by cc1), Pos*->x/y/z typing, &arg0->nodes[i].p, ((Node*)p-1)->handle,
// extern-vs-literal 1.0f/0.0f, m2c's statement order, volatile fields,
// explicit vs strength-reduced eoff/moff, and every ordering of the
// one/zero/mats prologue.
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_80291EF4;
extern f32 lbl_80291EF8;

typedef struct {
    f32 x, y, z;
} Pos;

typedef struct {
    s32 handle;
    char pad[0x10];
    Pos p;
} Node;

typedef struct {
    f32 f00, f04, f08, f0C, f10, f14, f18, f1C;
    f32 f20, f24, f28, f2C, f30, f34, f38, f3C;
} Mat;

typedef struct {
    s32 flags;
    Mat *mats;
    s32 p08, p0C, p10;
    s32 count;
    Node *nodes;
} Comp;

void fn_8003951C(void *, s32, void *);

void fn_80037CF4(Comp *arg0) {
    f32 one, zero;
    s32 idx, i, k, moff, eoff;
    Mat *m, *mm, *m2;
    Pos *p;
    f32 *f;

    if (arg0->flags & QB_UNKNOWN_0x08000000) {
        i = 1;
        m = 0;
        idx = 0;
        for (; i < arg0->count; i++) {
            f = (f32 *)((char *)arg0->nodes + i * 0x20 + 0x10);
            if (f[0] != 0.0f || f[1] != 0.0f || f[2] != 0.0f) {
                idx = ((s32 *)f)[-4];
                m = (Mat *)((char *)arg0->mats + i * 0x40);
                break;
            }
        }
        if (m != 0) {
            zero = lbl_80291EF4;
            one = lbl_80291EF8;
            mm = arg0->mats;
            mm->f00 = one;
            mm->f3C = one;
            mm->f04 = zero;
            mm->f08 = zero;
            mm->f0C = zero;
            mm->f10 = zero;
            mm->f14 = one;
            mm->f18 = zero;
            mm->f1C = zero;
            mm->f20 = zero;
            mm->f24 = zero;
            mm->f28 = one;
            mm->f2C = zero;
            mm->f30 = zero;
            mm->f34 = zero;
            mm->f38 = zero;
            mm = arg0->mats;
            mm->f0C = one;
            mm->f00 = zero;
            mm->f04 = zero;
            mm->f08 = zero;
            mm = arg0->mats;
            mm->f10 = zero;
            m2 = (Mat *)((char *)mm + 0x10);
            m2->f0C = one;
            m2->f04 = zero;
            m2->f08 = zero;
            mm = arg0->mats;
            mm->f20 = zero;
            m2 = (Mat *)((char *)mm + 0x20);
            m2->f0C = one;
            m2->f04 = zero;
            m2->f08 = zero;
            mm = arg0->mats;
            ((__ps_t *)mm)[6] = ((__ps_t *)m)[6];
            ((__ps_t *)mm)[7] = ((__ps_t *)m)[7];
            fn_8003951C(arg0, idx, (void *)((char *)arg0->mats + 0x30));
            for (k = 0; k < arg0->count; k++) {
                eoff = k * 0x20;
                moff = k * 0x40;
                p = (Pos *)((char *)arg0->nodes + eoff + 0x10);
                if (p->x == 0.0f && p->y == 0.0f && p->z == 0.0f) {
                    mm = arg0->mats;
                    *(f32 *)((char *)mm + moff) = one;
                    m2 = (Mat *)((char *)mm + moff);
                    m2->f30 = zero;
                    m2->f34 = zero;
                    m2->f3C = one;
                    m2->f04 = zero;
                    m2->f08 = zero;
                    m2->f0C = zero;
                    m2->f10 = zero;
                    m2->f14 = one;
                    m2->f18 = zero;
                    m2->f1C = zero;
                    m2->f20 = zero;
                    m2->f24 = zero;
                    m2->f28 = one;
                    m2->f2C = zero;
                    m2->f38 = zero;
                    mm = arg0->mats;
                    *(f32 *)((char *)mm + moff) = zero;
                    m2 = (Mat *)((char *)mm + moff);
                    m2->f0C = one;
                    m2->f04 = zero;
                    m2->f08 = zero;
                    mm = arg0->mats;
                    m2 = (Mat *)((char *)mm + moff);
                    m2->f10 = zero;
                    m2 = (Mat *)((char *)m2 + 0x10);
                    m2->f0C = one;
                    m2->f04 = zero;
                    m2->f08 = zero;
                    mm = arg0->mats;
                    m2 = (Mat *)((char *)mm + moff);
                    m2->f20 = zero;
                    m2 = (Mat *)((char *)m2 + 0x20);
                    m2->f0C = one;
                    m2->f04 = zero;
                    m2->f08 = zero;
                    mm = arg0->mats;
                    m2 = (Mat *)((char *)mm + moff);
                    ((__ps_t *)m2)[6] = ((__ps_t *)mm)[6];
                    ((__ps_t *)m2)[7] = ((__ps_t *)mm)[7];
                }
            }
        }
    }
}
