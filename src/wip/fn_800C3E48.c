// PARKED 2026-10-06: DIFF 10/165 (6.1%), unchanged.
// REFRESHED 2026-10-07 (FPR-pin RETARGET sweep): 6.0606% -> 9.0395%
//   the `c1` pin was retargeted fr28 -> fr16 (nothing else touched).  fr-pin REMOVAL
//   had been swept; retargeting had not.  Checked NOT size-exact before or after.  §6hk.
// Re-audited from the retail bytes this round; parking is honest here because the
// residual is the documented want-EXTRA-dead-insns wall (docs/parkings/33,
// recipes §6ax-229), not a source-shape or flag gap:
//  * 8 retail words are PROVABLY DEAD paired-single results — one `ps_mul f0,f0,f8`
//    at 0x800C3F34 whose value the very next `ps_merge00` overwrites, plus 7
//    `psq_st` spills into r1+0x10/0x18/0x20/0x28/0x30/0x38/0x40 that are never
//    read back.  cc1 DCEs dead PS results from every C spelling, so the object can
//    never reach 165 words.
//  * the remaining residual is post-RA: a 1-word prologue placement of
//    `addi r7,r7,-1` (retail keeps it between `cmpwi r7,0` and the `beq`; cc1
//    sinks it past the five constant loads) and the 13 stack slots at
//    r1+0x08..0x68, which cc1 splits into two non-contiguous address webs.
//    Every `-fno-schedule-ins*` / `-fno-sched-spec` / `-fno-gcse` /
//    `-fno-reorder-blocks` / `-fno-thread-jumps` variant measured WORSE.
// Body left byte-for-byte as the current best reconstruction — do not re-grind
// the PS block or the prologue; all 40 opcode-4 words were already hand-decoded
// and every one is emittable, the wall is scheduling + DCE.
//
// MEASUREMENT NOTE: build/ctx50/CTX_0x800C3E48.txt shows the want_got run
// raising `len(None)`, NOT a real compile failure — tools/want_got.py does not
// auto-append -mps-float for a `__builtin_ps_*` body, so its compile has no PS
// interface.  The real verdict comes from tools/test_wip_drafts.py --addr
// 0x800C3E48, which auto-appends -mps-float (__ps_t/__builtin_ps_ rule).
//
// WIP DRAFT (non-matching) — semantic rebuild of retail fn_800C3E48
// family=ps range=0x800C3E48-0x800C40DC size=660B   (0x800C3E48 + 0x294, symbols.txt)
// VERDICT: DIFF. masked 10/165 (6.1%); 49/165 (29.7%) of the want stream is
//   reproduced in order (word LCS); object 612B vs retail 660B. Needs
//   -mps-float.  The old m2c draft scored 2.2% and emitted a 500B object
//   (statics-DCE husk, Unk_* mis-typed slots, -Os).
//
// WHAT IS NOW CORRECT (was all wrong in the m2c draft):
//  * file-local true layouts.  Unk_B8EAF2F7.unk0x170 is s8 in the shared class
//    but is read with lfs (f32); Unk_5054608A.unk0xC0/0xD0/0xD4 are s32 in the
//    shared class but are read with lfs.  arg0+0x80/0x88/0x110/0x118/0x138/
//    0x140/0x148/0x150 and node+0x18/0x20/0x28/0x30/0x68/0x70 are 8-byte
//    paired-single pairs, not scalars.  (trap 1 / §6bb-286)
//  * node walk: 480-byte stride, DESCENDING (i = n-1..0), so the byte offset
//    is (i - (i<<4)) << 5 = -480*i, not +480*i as m2c had.
//  * then-arm (node->f4 == 1) is the manual int->float dance of §6j-1:
//    0x43300000 / value stored as an 8-byte pair at r1+0x68, lfd, fsub of the
//    game's own 2^52 rodata2 double (lbl_802990B8), frsp, then two fdivs and
//    an indexed stfsx at node+0x3C+(s8)idx*4.  References no private pool, so
//    it is promote-clean (no §4n/doc-14 .rodata hazard).
//  * the 10-element average: mtctr/bdnz, pointer walking DOWN from node+0x60
//    in 4-BYTE steps (m2c's `wp - 4` on an f32* was -16 bytes), accumulate into
//    node->avg, then divide by lbl_802990C8 (10.0f).
//  * the epilogue modulo is SIGNED: (s8)((idx+1) % 10) -> mulhw/srawi/subf/
//    mulli/subf/stb.  That 15-instruction tail is now byte-identical, as is the
//    whole prologue (stwu -0x90 + stfd f28..f31 + lwz/cmpwi) and the
//    480-byte index computation (slwi/subf/slwi/add).
//
// DISCLOSED register pins (last resort, no asm instruction templates):
//  `register f32 c1 __asm__("f32"); c2 fr31; c3 fr29; c4 fr30` — the four
//  loop-invariant rodata constants must live in callee-saved f28..f31 (retail
//  saves 4 FPRs and the frame is 0x90 = ngccc-native + 8*4, §4c/recipe 63).
//  Without the pins cc1 picks caller-saved f1/f2/f4, saves only f31 and the
//  frame comes out 0x78.
//
// PRECISE RESIDUAL (no source form or flag reaches it — do NOT re-grind):
//  1. 1-word prologue shift.  cc1 sinks the loop-index init `addi r7,r7,-1`
//     below the five loop-invariant constant loads; retail keeps it between
//     the `cmpwi r7,0` and the `beq`.  Every `-fno-schedule-ins*`,
//     `-fno-sched-spec`, `-fno-gcse`, `-fno-reorder-blocks`, `-fno-thread-jumps`
//     was measured and all score WORSE (masked 5-8 vs 10).
//  2. The ~30-operation paired-single block.  Retail interleaves psq_l /
//     ps op / psq_st one-per-line; cc1 sinks the pair loads, keeps values in
//     registers and reorders the merge00/merge01 -> mul -> madd -> sum0 chain.
//     8 of the retail words are PROVABLY DEAD and no C form can reproduce
//     them: the `ps_mul f0,f0,f8` at 0x800C3F34 whose result is overwritten by
//     the next `ps_merge00`, and 7 `psq_st` into stack slots
//     0x10/0x18/0x20/0x28/0x30/0x38/0x40(r1) that are never read back.
//     cc1 DCEs dead paired-single results from every form (§6ax-229), so the
//     object can never reach 165 words: this is the want-EXTRA-dead-insns park
//     class (docs/parkings/33, §6x-89).  All 40 opcode-4 words were hand
//     decoded and every one is emittable (ps_mul/madd/sum0/muls0/add/sub/
//     merge00/merge01/ps_mr) — the wall is scheduling, not emission.
//  3. Frame slots.  The 13 stack slots (r1+0x08..0x68) do not land
//     contiguously; cc1 splits volatile from non-volatile struct members and
//     interleaves them (retail: addi r5,r1,8 in the preheader, then 8(r5) and
//     8(r1) as two separate address webs).
//
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

typedef float sn_ps __attribute__((mode(PS)));

typedef struct {
    f32   f_0;                        /* 0x00  lfsx f5, r6, r8         */
    s32   f4;                         /* 0x04  cmpwi r0, 1               */
    char  pad08[0x10];
    sn_ps p18, p20, p28, p30;          /* 0x18 0x20 0x28 0x30           */
    f32   avg;                         /* 0x38  accumulator / result    */
    f32   arr[10];                     /* 0x3C  + (s8)idx*4              */
    char  pad64[0x4];
    sn_ps p68, p70;                    /* 0x68 0x70                      */
    char  pad78[0x48];
    f32   c0;                         /* 0xC0                          */
    char  padC4[0xC];
    f32   d0;                         /* 0xD0                          */
    f32   d4;                         /* 0xD4                          */
} C3E48_N;

typedef struct {
    char  pad00[0x80];
    sn_ps a80, a88;                    /* 0x80  0x88                    */
    char  pad090[0x80];
    sn_ps a110, a118;                  /* 0x110 0x118                   */
    char  pad120[0x4];
    s8    idx124;                     /* 0x124  lbz + extsb, stb       */
    char  pad125[0x13];
    sn_ps a138, a140;                  /* 0x138 0x140                   */
    sn_ps a148, a150;                  /* 0x148 0x150                   */
    char  pad158[0x18];
    f32   f170;                        /* 0x170  lfs f13                */
    char  pad174[0x38];
    s32   n1ac;                        /* 0x1AC  lwz r11                */
    char  pad1B0[0x140];
    C3E48_N *nodes;                    /* 0x2F0  lwz r6                 */
} C3E48_A;

typedef struct {
    sn_ps   p0;
    sn_ps p1;
    sn_ps p2;
    sn_ps p3;
    sn_ps p4;
    sn_ps p5;
    sn_ps p6;
    sn_ps p7;
    union { sn_ps ps; f32 lo; } p8;
    union { sn_ps ps; f32 lo; } p9;
    union { sn_ps ps; f32 lo; } pa;
    union { sn_ps ps; f32 lo; } pb;
    union { s32 w[2]; f64 d; } cvt;
} C3E48_FR;

extern f32   lbl_802990B4;   /* 386.4f                                     */
extern f64   lbl_802990B8;   /* 2^52, the int->float subtract constant     */
extern f32   lbl_802990C0;   /* 1.0f                                       */
extern f32   lbl_802990C4;   /* 0.0f                                       */
extern f32   lbl_802990C8;   /* 10.0f, the averaging divisor               */
extern sn_ps lbl_80298F18;   /* 0x3C-byte matrix; only the first pair used */

void fn_800C3E48(C3E48_A *arg0) {
    volatile C3E48_FR fr;
    s32 i;
    register f32 c1 __asm__("fr16");
    register f64 c2 __asm__("fr31");
    register f32 c3 __asm__("fr29");
    register f32 c4 __asm__("fr30");
    sn_ps *mtx;
    s32 t16;
    s32 magic;

    i = arg0->n1ac;
    if (i != 0) {
        i = i - 1;
        c1 = lbl_802990B4;
        c2 = lbl_802990B8;
        c3 = lbl_802990C4;
        c4 = lbl_802990C8;
        mtx = &lbl_80298F18;
        magic = 0x43300000;
        for (;;) {
            C3E48_N *node;
            t16 = i << 4;
            node = (C3E48_N *)((char *)arg0->nodes + ((i - t16) << 5));
            if (node->f4 == 1) {
                f32 *dst;
                i = i - 1;
                dst = node->arr;
                fr.cvt.w[1] = arg0->n1ac;
                fr.cvt.w[0] = magic;
                dst[arg0->idx124] = c1 / arg0->f170 / (f32)(fr.cvt.d - c2);
            } else {
                sn_ps t, s, g, a, u;
                f32 res;
                f32 *wp;
                s32 ctr;
                i = i - 1;

                a = arg0->a80;
                fr.p0 = a;
                fr.p1 = arg0->a88;
                t = __builtin_ps_mul(node->p70, node->p30);
                t = __builtin_ps_mul(node->p30, mtx[0]);
                s = __builtin_ps_merge00(mtx[0], mtx[0]);
                g = __builtin_ps_madd(node->p28, s, node->p68);
                t = __builtin_ps_merge00(t, t);
                a = __builtin_ps_madd(node->p68, a, t);
                g = __builtin_ps_sum0(g, g, g);
                a = __builtin_ps_sum0(a, a, a);
                fr.p9.ps = g;
                fr.p8.ps = a;
                res = -node->d0 * (node->c0 - node->f_0) * fr.p8.lo
                    + (-node->d4) * fr.p9.lo;
                fr.pa.lo = res;
                s = __builtin_ps_muls0(node->p68, fr.pa.ps);
                t = __builtin_ps_muls0(node->p70, fr.pa.ps);
                fr.p2 = s;
                fr.p3 = t;
                arg0->a140 = __builtin_ps_add(arg0->a140, t);
                arg0->a138 = __builtin_ps_add(arg0->a138, s);
                u = __builtin_ps_merge01(t, t);
                t = __builtin_ps_merge00(s, s);
                g = __builtin_ps_sub(node->p18, arg0->a110);
                a = __builtin_ps_sub(node->p20, arg0->a118);
                fr.p6 = g;
                fr.p7 = a;
                u = __builtin_ps_merge01(g, g);
                t = __builtin_ps_mul(g, a);
                s = __builtin_ps_mul(t, node->p68);
                a = __builtin_ps_merge00(a, a);
                t = __builtin_ps_sub(t, s);
                g = __builtin_ps_merge00(t, t);
                a = __builtin_ps_mul(a, s);
                fr.pb.ps = g;
                fr.pb.lo = lbl_802990C0;
                a = __builtin_ps_merge01(a, a);
                a = __builtin_ps_sub(a, a);
                u = __builtin_ps_merge01(t, t);
                fr.p4 = u;
                arg0->a148 = __builtin_ps_add(arg0->a148, u);
                t = fr.pb.ps;
                a = t;
                fr.p5 = a;
                arg0->a150 = __builtin_ps_add(arg0->a150, a);

                node->arr[arg0->idx124] = res;

                ctr = 0xA;
                wp  = (f32 *)((char *)node + 0x60);
                node->avg = c3;
                do {
                    node->avg = node->avg + *wp;
                    wp = (f32 *)((char *)wp - 4);
                    ctr = ctr - 1;
                } while (ctr != 0);
                node->avg = node->avg / c4;
            }
            if (i == -1) break;
        }
    }
    arg0->idx124 = (s8)((arg0->idx124 + 1) % 10);
}
