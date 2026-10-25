// WIP DRAFT (non-matching) — C body rewritten by hand from the retail bytes
// family=m2c range=0x800EED54-0x800EF030 size=732B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (w_800EED54): 6.56% (m2c draft) -> 23.16%. The m2c body
// was structurally fiction (a 4x4 nested loop of `var_ctr` spins and a bogus
// `GetChecksum_3(...,QB_SKELETON)` per iteration); this body is a real
// re-decompilation and matches retail's shape, but does NOT byte-match.
//
// WHAT WAS DECODED (all confirmed against the raw DOL):
//  * arg0->[0xC] -> GetChecksum_3(..., QB_MODEL) -> +0x210 -> fn_80062680.
//    The s32 that comes back is the base of a float blob, NOT a struct ptr.
//  * b+0x60 is one 64-byte record; b+0xb0+k*0x50 (k=3..0) are four more. Each
//    record is copied whole into a stack staging slot as EIGHT psq_l/psq_st
//    pairs (that is the `-mps-float` / `__ps_t` struct-copy idiom — an
//    `aligned(8)` f32 struct emits lwz/stw, NOT psq; only the PS-mode type
//    does). Only fields +0x30/+0x34/+0x38 (i.e. pair 6 and pair 7) are read
//    back out of the staging slot, and f12 is negated.
//  * locals, from the frame: [0x08] Sm loc[4] (0x10 stride), [0x48] the 64-byte
//    staging union `v`, [0x88] Sm t. Frame is exactly 0xd8 (locals 0..0xaf,
//    stmw r28 at 0xb0, f29/f30/f31 at 0xc0/0xc8/0xd0, LR at 0xdc = one word
//    PAST the frame, which is legal because a callee may clobber the caller's
//    parameter save area).
//  * `lbl_8029B024/28/2C` are 1.0f / 0.0f / -1.0f. They MUST be plain locals
//    (`f32 one/zero/mone` initialised at the top of the function): as `const`
//    globals GCC hoists them too, but then only f31 is live across the calls
//    and it allocates f0/f13 for the rest, saving ONE FPR and producing a 0xb8
//    frame. Getting 3 FPRs + the 0xd8 frame needs all three defined at entry.
//  * The final do-while writes 0x40-byte (4x4) records into
//    skeleton->[0x04], count = skeleton->[0x14]: record 0 = all-zero,
//    record 1 = row0 [1,0,0,0] row1 [0,-1,0,0] row2 [0,1,0,0] row3 = t,
//    record i>=2 = {-1,0,0,0, 0,1,0,0, 0,1,0, loc[i-2][0..3]}. The two
//    dead zero stores at +0x30/+0x34/+0x38/+0x3C before the pair store are in
//    the retail bytes, so they are in the source too.
//  * `-fno-strength-reduce` is REQUIRED: retail recomputes `slwi r10,4` and
//    `mulli r9,0x50` from the loop counter every iteration (no induction
//    variable) for the first loop, while still doing `addi r31,r31,0x40`
//    pointer bumps in the last one (that one is an explicit source pointer).
//  * the three `li r0,4; mtctr r0; bdnz <self>` triples are real
//    `s32 c = 4; while (--c) { }` empty loops (verified: ngccc emits a
//    SELF-targeting bdnz for `while (--c) {}`, ELF REL14 addend == its own
//    offset). Capstone's branch-target text is wrong for this toolchain —
//    trust the REL14 addend, not the printed operand.
//
// RESIDUAL (23.16% masked, 708B object vs 732B want = 6 words short):
//   1. length/alignment: retail spends 4 instructions in the prologue on ONE
//      constant (`lis r9` + `lfs f12`) and re-loads 1.0f again after the
//      second GetChecksum_3 (`fmr f30, f11`); this body keeps all three
//      constants live from entry, which costs 3 `lis` + 3 `lfs` up front and
//      still nets 6 words short. Moving the zero/mone loads after the calls
//      (to match retail's position) collapses the frame back to 0xb8 -> 6%.
//   2. loop-count: retail's empty loops are `li r0,4` (4 trips); ngccc counts
//      3 here no matter which of `while(--c)`/`for(c=0;c<4;c++)`/`do{}while(--c)`
//      is used, so every bdnz/mtctr pair is off by one.
//   3. k-loop header: retail wants `slwi` BEFORE `mulli`, `addi r0,r10,-1` +
//      `mr r10,r0` + `cmpwi r10,-1` (a copied counter); ngccc gives
//      `mulli`, `addic.`, and `or. r7,r0,r0`. Same for the loc base: retail
//      keeps it in r31 from the prologue, here it is `addi r9,r1,8` + `mr r6,r9`
//      inside the loop.
//   4. store order inside the i==1 / i>=2 arms: retail emits all eleven zero
//      stores in ascending order then 0x00/0x18/0x24/0x30/0x34; ngccc sinks
//      f[6] and f[7] to the end of the run.
//   5. the epilogue-adjacent pair copy in the i==1 arm reads `psq_l f0,136(r1)`
//      / `psq_l f13,144(r1)`; here it goes through f12 and the two lfs/pairs
//      land at 136/144 too but from the other operand order.
//
// RULED OUT: `aligned(8)` f32 structs (emit lwz/stw, not psq); `*(f32*)&ps`
// (ICEs in expmed.c:1115 — must go through a union's `f[]` view);
// `volatile`/store-order shuffles for the psq pairs (the l/s interleave and
// the f0/f13 rotation already match exactly); putting zero/mone behind the
// calls (loses 2 of 3 FPR saves, frame 0xb8); `asm` pins for r10/r31
// (not attempted — items 3 and 5 are the live blockers).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void *GetChecksum_3(s32, s32);
extern s32 fn_80062680(s32);
extern s32 fn_800C9780(s32);
extern s32 fn_80036960(s32);
extern s32 fn_80036968(s32);
extern const f32 lbl_8029B024[];
extern const f32 lbl_8029B028[];
extern const f32 lbl_8029B02C[];

// 64-byte PS staging slot: the pair view is what produces psq_l/psq_st, the
// f32 view is how the individual fields get read back out of it.
typedef union {
    __ps_t p[8];
    f32 f[16];
} Big;

// 16-byte record (0x10 stride in `loc`).
typedef union {
    __ps_t p[2];
    f32 f[4];
} Sm;

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
} Arg0;

// extra_cflags: -mps-float
// FLAG: -fno-strength-reduce
void fn_800EED54(Arg0 *arg0) {
    s32 i;
    s32 k;
    Sm loc[4];
    Big v;
    Sm t;
    f32 *b;
    s32 sk;
    s32 c1;
    s32 c2;
    s32 c3;
    f32 zero = lbl_8029B028[0];
    f32 mone = lbl_8029B02C[0];
    f32 one = lbl_8029B024[0];

    b = (f32 *)fn_80062680(*(s32 *)((char *)GetChecksum_3(arg0->unk0xC, QB_MODEL) + 0x210));
    c1 = 4;
    while (--c1) { }
    for (k = 3; k >= 0; k--) {
        const Big *s = (const Big *)((const char *)b + k * 0x50 + 0xb0);
        c2 = 4;
        while (--c2) { }
        v.p[0] = s->p[0];
        v.p[1] = s->p[1];
        v.p[2] = s->p[2];
        v.p[3] = s->p[3];
        v.p[4] = s->p[4];
        v.p[5] = s->p[5];
        v.p[6] = s->p[6];
        v.p[7] = s->p[7];
        loc[k].f[0] = -v.f[12];
        loc[k].f[1] = v.f[14];
        loc[k].f[2] = one;
        loc[k].f[3] = -v.f[13];
    }
    c3 = 4;
    while (--c3) { }
    {
        const Big *q = (const Big *)((const char *)b + 0x60);
        v.p[0] = q->p[0];
        v.p[1] = q->p[1];
        v.p[2] = q->p[2];
        v.p[3] = q->p[3];
        v.p[4] = q->p[4];
        v.p[5] = q->p[5];
        v.p[6] = q->p[6];
        v.p[7] = q->p[7];
        t.f[0] = -v.f[12];
        t.f[1] = v.f[14];
        t.f[2] = -v.f[13];
        t.f[3] = one;
    }
    sk = (s32)GetChecksum_3(arg0->unk0xC, QB_SKELETON);
    fn_800C9780(sk);
    i = 0;
    {
        Big *o = (Big *)fn_80036960(sk);
        s32 n = fn_80036968(sk);
        Sm *lp = loc - 2;
        do {
            if (i == 0) {
                o->f[0] = zero;
                o->f[1] = zero;
                o->f[2] = zero;
                o->f[3] = zero;
                o->f[4] = zero;
                o->f[5] = zero;
                o->f[6] = zero;
                o->f[7] = zero;
                o->f[8] = zero;
                o->f[9] = zero;
                o->f[10] = zero;
                o->f[11] = zero;
                o->f[12] = zero;
                o->f[13] = zero;
                o->f[14] = zero;
                o->f[15] = zero;
            } else if (i == 1) {
                o->f[1] = zero;
                o->f[2] = zero;
                o->f[3] = zero;
                o->f[4] = zero;
                o->f[5] = zero;
                o->f[7] = zero;
                o->f[8] = zero;
                o->f[11] = zero;
                o->f[12] = zero;
                o->f[14] = zero;
                o->f[15] = zero;
                o->f[0] = one;
                o->f[6] = mone;
                o->f[9] = one;
                o->f[12] = zero;
                o->f[13] = zero;
                o->p[3] = t.p[0];
                o->p[4] = t.p[1];
            } else {
                o->f[1] = zero;
                o->f[2] = zero;
                o->f[3] = zero;
                o->f[4] = zero;
                o->f[5] = zero;
                o->f[7] = zero;
                o->f[8] = zero;
                o->f[11] = zero;
                o->f[12] = zero;
                o->f[14] = zero;
                o->f[15] = zero;
                o->f[0] = mone;
                o->f[6] = one;
                o->f[9] = one;
                o->f[12] = zero;
                o->f[13] = zero;
                o->p[3] = lp->p[0];
                o->p[4] = lp->p[1];
            }
            o++;
            lp++;
            i++;
        } while (i < n);
    }
}