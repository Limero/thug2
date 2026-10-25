// PARKED 2026-10-04 (task 0x80059C18): NEAR/DIFF 4.2% (body below).
// Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80059C18
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/want_got.py 0x80059C18
// The m2c bulk draft that used to live here scored ~5% with garbage bodies
// (`*(s32 *)((char *)var_r31 + 0x803008B8)` etc.). The body below is a full
// hand reconstruction: EVERY basic block of the want now has the right shape
// and the right LENGTH (no block is off by a single word anywhere), and the
// whole 664-0x298 region is emitted. What is left is 100% ngccc register
// allocation, which this project's matched siblings only reach with
// `register ... __asm__("frN"/"rN")` pins (banned for this task).
//
// WHAT IS NOW KNOWN (do not re-derive):
//  * Semantics. arg0 = a 4-float point. For every object in lbl_80300498[0..
//    lbl_80300898), skip unless obj->f[0x24] > lbl_802934C0 and obj->i[0x2C] !=
//    0; then compute a squared distance, skip if it exceeds (obj->f[0x1C])^2,
//    sqrtf() it (result dead - it is overwritten by the vcall below), and keep
//    an ascending-insertion-sorted top-`arg1` list in the three parallel
//    globals lbl_803008B8 (f32), lbl_80300934 (index) and the caller's arg2
//    (pointer), returning the count.
//  * The preheader needs BOTH tests: `if (lbl_80300898 > 0)` for the want's
//    `cmpwi r0,0 ; ble`, plus the plain `for (i=0; i<count; i++)` whose loop
//    rotation emits the (provably dead) `cmpw n,count ; bge` guard. Got.
//  * obj->i[0x2C] must be materialised as a boolean, not tested directly:
//    `ok = 1; if (obj->unk0x2C == 0) ok = 0; if (ok)` reproduces want's
//    5-instruction `li r11,1 ; cmpwi r0,0 ; bne ; li r11,0 ; cmpwi r11,0 ; beq`
//    verbatim. `if (obj->unk0x2C != 0)` gives only `cmpwi r0,0 ; beq` (-4B).
//  * All comparisons must be spelled POSITIVELY (`if (a > b) { body }`).
//    Spelled as `if (a <= b) continue;` ngccc emits an extra
//    `cror cr0un,cr0eq,cr0lt` + inverted branch; want has a bare `ble`/`bgt`.
//  * lbl_802934C0 must be a local initialised BEFORE the loop - that is what
//    puts it in callee-saved f31 (`stfd f31,0x70(r1)` / `lfd` in the epilogue
//    and `fcmpu cr0,f0,f31` inside the loop) instead of reloading it per
//    iteration.
//  * The vcall is THUG2's compressed-vtable form: vtable+0x18 is an s16 `this`
//    delta (`lha r0,0x18(r9)`) and vtable+0x1c the f32-returning entry
//    (`lwz`+`mtlr`+`blrl`). A file-local typedef with both fields at those
//    offsets is what produces `lha`+`add`+`mtlr`+`blrl` (recipes 9836).
//  * The PS block is the fn_8000714C idiom (that function is matched and shows
//    the identical `ps_mul -> ps_merge00(.,zero) -> ps_madd -> ps_sum0` chain):
//        m = sp8;                       /* volatile __ps_t -> real psq_l reload */
//        m = __builtin_ps_mul(m, m);
//        m = __builtin_ps_merge00(m, lbl_80293458);   /* 0x80293458 = {0.0,0.0}*/
//        dot = __builtin_ps_madd(p, p, m);            /* p = the ORIGINAL pair  */
//        dot = __builtin_ps_sum0(dot, dot, dot);
//    The load-bearing detail: the `ps_madd` multiply operand must be the
//    pre-store copy `p`, while the `ps_mul` operand is the *reloaded* volatile.
//    Using the reloaded value for both (the obvious spelling) makes ngccc CSE
//    them and the madd comes out as `ps_madd f0,f10,f10,f0` instead of want's
//    `ps_madd f13,f13,f13,f0`. With the volatile split, madd+sum0+psq_st match
//    want byte for byte.
//  * sp8/sp16 must be `volatile __ps_t` (want stores f13 and f0 to 8(r1)/16(r1)
//    and re-loads only 8(r1); without volatile the stores vanish entirely).
//  * The sum0 result must be read out of a NON-volatile union
//    (`union { __ps_t ps; struct { f32 lo, hi; } w; } sp24;`).
//    A *volatile* union gives `lfs f1,0x18(r1)` - one word short of want.
//    The non-volatile union reproduces want's
//    `lfs f0,0x18(r1) ; fmr f1,f0 ; fcmpu cr0,f1,f10` exactly. This is the
//    project-known "non-volatile union read gets the load+copy pair" effect
//    (recipes 11037/17933) and it is the single most useful find here.
//  * The shift loop is a chain of three SWAPS (not shifts): want's
//    `lwz r9,-4(r6) ; lwzx r0,r10,r29 ; stwx r9,r10,r29 ; stwu r0,-4(r6)` is
//    `t=out[k-1]; out[k-1]=out[k]; out[k]=t;`. `for (k = n; k > j; k--)` with
//    explicit temps is the spelling that gives want's countdown
//    (`mr r5,r31` then `addi r5,r5,-1 ; cmplw r30,r5`).
//  * `lbl_80300934[n]`, `lbl_803008B8[n]`, `arg2[n]` (NOT `[0]`) in the n==0
//    seed: want uses `stwx r26,r17,r31` (indexed by n), not `stw r,0(rX)`.
//
// MEASURED (base flags -O2 -G0 -mcpu=750 -fno-common + per-object -mps-float):
//  test_wip_drafts.py -> DIFF. want_got.py -> 4.40% / 636B (-28B); the
//  PS-aware diff (tools/ps_diff.py decoder applied want|got) -> 4.22% / 636B.
//  Block lengths match want
//  everywhere; the -28B is 7 words spread over the insertion sort (want's shift
//  loop is 18 words, the swap of lbl_803008B8/lbl_80300934 wants materialised
//  &d[k]/&idx[k] pointers r8/r7 while ngccc keeps byte offsets, and the
//  j-loop preheader is 12 words in want vs 10 here).
//  Flags tried, all neutral or worse: -fno-schedule-insns2, -fno-schedule-insns,
//  -mcpu=603, -O1 (7.2%), -O3, volatile/non-volatile _dummy frame padding.
//  An UNFAITHFUL variant - hoisting `dist = sqrtf(sq);` ABOVE the test, i.e.
//  calling sqrtf on the skip path too - measures 22.29% / 644B. That number is
//  an artifact: the extra 16 bytes are 2 more `stfd`/`lfd` pairs (3 callee-saved
//  FPRs instead of 1, because sq and r2^2 then live across the sqrtf call) and
//  that padding happens to re-align the head of the function. It is NOT left in
//  the file: want branches around the `bl sqrtf`, and a decomp that calls sqrtf
//  on the skip path misrepresents the original control flow.
//
// REMAINING BLOCKER (no plain-C lever found):
//  1. Register allocation of 17 loop-carried pseudos. want dedicates
//     r15=page(lbl_80300898) r16=&lbl_80293458 r17=&lbl_80300934 r18=sp+8
//     r19=page(0x80300000) r20=&lbl_803008B8 r21=&lbl_80300498 r22=arg0
//     r23=i+1 r24=arg1 r25=&lbl_80300498 r27=&lbl_803008B8 r28=&lbl_80300934
//     r29=arg2 r30=i*4 r31=n, i.e. `stmw r15` and frame 0x78; this body gets
//     r18..r31 and frame 0x68. Three of want's pseudos (the duplicated &pool,
//     &d and &idx bases created in the j-loop preheader) simply do not exist
//     here, so GCC never needs the extra registers.
//  2. `addi r18,r1,8` - want hoists the address of the sp8 local out of the
//     loop and reloads through it (`psq_l f0,8(r18)`); plain C only ever emits
//     the frame-pointer-offset form `8(r1)`. This is the loop-invariant-address
//     pseudo the project's matched PS functions force with a register pin.
//  3. In the PS block ngccc's scheduler emits the four pair loads as
//     v0,p,v1,q; want's order (== the source order here) is v0,v1,p,q.
//  4. The insertion-sort address forms: want materialises &d[k] and &idx[k] as
//     pointers walking down (`addi r8,r8,-4`) and only uses indexed operands for
//     the [k] halves; ngccc keeps byte offsets and uses indexed operands for
//     both halves.
//
// Follow-up ideas not yet tried: reorder the j-loop preheader so &pool/&d/&idx
// are re-taken after the store-at-j path (to force the duplicate address
// pseudos want has); spell the shift loop with explicit `f32 *pd = &d[k-1]`
// style locals; and, if pins ever become legal for this function, the
// r15-r31/r16/r18 assignment above is the whole remaining diff.
// family=m2c range=0x80059C18-0x80059EB0 size=664B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

typedef struct Vt59C18 {
    char pad0x0[0x18];
    s16 this_off;
    f32 (*fn)(void *);
} Vt59C18;

typedef struct Obj59C18 {
    char pad0x0[0x8];
    f32 unk0x8;
    f32 unk0xC;
    f32 unk0x10;
    f32 unk0x14;
    f32 unk0x18;
    f32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    f32 unk0x28;
    s32 unk0x2C;
    char pad0x30[0x4];
    Vt59C18 *vt;
} Obj59C18;

typedef union {
    __ps_t ps;
    struct {
        f32 lo;
        f32 hi;
    } w;
} PSVal59;

extern s32 lbl_80300898;
extern Obj59C18 *lbl_80300498[0x100];
extern f32 lbl_803008B8[0x1F];
extern s32 lbl_80300934[0x1F];
extern f32 lbl_802934C0;
extern __ps_t lbl_80293458;

f32 sqrtf(f32);

s32 fn_80059C18(f32 *arg0, s32 arg1, Obj59C18 **arg2) {
    s32 n = 0;
    s32 i;
    s32 j;
    s32 k;
    f32 thresh = lbl_802934C0;
    Obj59C18 *obj;
    __ps_t p;
    __ps_t q;
    __ps_t v0;
    __ps_t v1;
    __ps_t m;
    __ps_t dot;
    volatile __ps_t sp8;
    volatile __ps_t sp16;
    PSVal59 sp24;
    f32 r2;
    f32 sq;
    f32 dist;
    f32 tv;
    void *tvp;
    s32 ti;
    s32 ok;

    if (lbl_80300898 > 0) {
        for (i = 0; i < lbl_80300898; i++) {
            obj = lbl_80300498[i];
            if (obj->unk0x24 > thresh) {
                ok = 1;
                if (obj->unk0x2C == 0) {
                    ok = 0;
                }
                if (ok) {
                    v0 = *(__ps_t *)((char *)obj + 8);
                    v1 = *(__ps_t *)((char *)obj + 16);
                    p = *(__ps_t *)arg0;
                    q = *(__ps_t *)(arg0 + 2);
                    r2 = obj->unk0x1C;
                    p = __builtin_ps_sub(p, v0);
                    q = __builtin_ps_sub(q, v1);
                    sp8 = p;
                    sp16 = q;
                    r2 = r2 * r2;
                    m = sp8;
                    m = __builtin_ps_mul(m, m);
                    m = __builtin_ps_merge00(m, lbl_80293458);
                    dot = __builtin_ps_madd(p, p, m);
                    dot = __builtin_ps_sum0(dot, dot, dot);
                    sp24.ps = dot;
                    sq = sp24.w.lo;
                    if (sq > r2) {
                        continue;
                    }
                    dist = sqrtf(sq);
                    dist = lbl_80300498[i]->vt->fn((void *)lbl_80300498[i] +
                                                   lbl_80300498[i]->vt->this_off);
                    if (n == 0) {
                        lbl_80300934[n] = i;
                        lbl_803008B8[n] = dist;
                        arg2[n] = lbl_80300498[i];
                        n = 1;
                    } else if (n < arg1 || dist < lbl_803008B8[n - 1]) {
                        j = 0;
                        while (j < n) {
                            if (dist > lbl_803008B8[j]) {
                                for (k = n; k > j; k--) {
                                    tvp = arg2[k - 1];
                                    arg2[k - 1] = arg2[k];
                                    arg2[k] = tvp;
                                    tv = lbl_803008B8[k - 1];
                                    lbl_803008B8[k - 1] = lbl_803008B8[k];
                                    lbl_803008B8[k] = tv;
                                    ti = lbl_80300934[k - 1];
                                    lbl_80300934[k - 1] = lbl_80300934[k];
                                    lbl_80300934[k] = ti;
                                }
                                lbl_803008B8[j] = dist;
                                lbl_80300934[j] = i;
                                arg2[j] = lbl_80300498[i];
                                if (n < arg1) {
                                    n++;
                                }
                                break;
                            } else if (n < arg1) {
                                lbl_803008B8[n] = dist;
                                lbl_80300934[n] = i;
                                arg2[n] = lbl_80300498[i];
                                n++;
                            }
                            j++;
                        }
                    }
                }
            }
        }
    }
    return n;
}