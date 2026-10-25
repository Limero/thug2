// WIP DRAFT (non-matching) — PARKED 2026-10-30 at 84.62%
//
// Baseline was 45.05% (DIFF, 360 B object, 49 masked diffs, frame already exact).
// Progression, all SEMANTIC plus one promoted-exemplar idiom:
//   45.05 -> 73.6  volatile int->double cvt union + `__asm__ volatile("":::
//                 "memory")` fence between the two cvt word stores.  This is
//                 the §6ag-5 / §6ac-3 form (a volatile-qualified f64 member is
//                 what stops TBAA eliminating the lo/hi store pair); the memory
//                 fence is the §6bz-1 "freeze only the store" trick. Without
//                 the fence the compiler CSEs the two stores of cvt.w[0] and
//                 the whole dance collapses (360 B, one word short).
//   73.6  -> 80-84  staging mag/kf/thr into named locals so the three
//                 constant loads are independent defs, plus the want-only dead
//                 copy reproduced with a 1-word asm wedge (pinned register to
//                 register). The original has this dead copy with the source
//                 never written; the same idiom is in the address-adjacent
//                 sibling src/wip/fn_802403AC.c (bias setup plus dead copy
//                 plus sign-bit flip) and in promoted src/fn_801FA318.c, so
//                 it is a real family artifact, not a decode error.
//   84.62 = best.  Object is EXACTLY 364 B (== symbols.txt size:0x16C) and the
//                 float-register chain is byte-correct. 14 of 91 words still
//                 differ.
//
// WHY PARKED (exact residual, original 0x80240548-0x80240590 vs this build):
//   Same operation multiset, same length, same float-register roles. The
//   original interleaves the int-to-float conversion stores with the three
//   constant loads; this build groups the three constant loads into a
//   contiguous run after their page setups, and spreads the conversion stores
//   around them. Two root causes:
//   (1) doc-73 page-anchor COLOUR: the original spreads three same-page
//       constant-page setups over three distinct base registers; the compiler
//       picks a different three from its reload-pseudo preference set, and no
//       C spelling moves it - 6 extern-declaration orders are all
//       byte-identical, and pinning the anchors via a register variable fed
//       a literal page is CATASTROPHIC (2.20%, 89 diffs) because a register
//       var is live-from-entry and the page then crosses the two calls,
//       forcing two extra callee-saved registers. Pinning the bias constant
//       is also inert or negative (45-50%). This is doc 73's "not producible
//       by any C spelling" for a 3-anchor block.
//   (2) sched2 GROUPS the three independent constant loads into a contiguous
//       run right after their three page setups, where the original
//       interleaves them with the conversion stores.
// (dump at <scratch>) shows the
//       post-reload RTL is already in source order, so this is a post-reload
//       cheap-ready-first tie, not an ordering choice.
//
// LEVERS TRIED AND MEASURED (all on the final body or its immediate parent):
//   * 36-flag sweep on the 79% body: every scheduling/GCSE/thread-jump/
//     strength-reduce flag is a no-op; -fno-schedule-insns2 drops to 70.33,
//     -fno-sched-spec/-fno-sched-interblock/-fno-gcse/-fno-thread-jumps/
//     -fno-rerun-cse-after-loop/-O3 neutral, -Os 75.82.  -fno-sched-round and
//     -fno-tree-pre do not exist in ProDG cc1 (ERR).
//   * 248-variant sweep9: fence position x staged-assignment position
//     (mag/kf/thr before the dance, after cvt.w[0], after w1, after the
//   num) -> best 83.52.
//   * 96-variant sweep10: 1/2/3 pinned page anchors x 4 bias pins x dead-copy
//     wedge on/off x 2 fence positions -> best 83.52, all pin sets <= 50%.
//   * 48-variant dead-copy wedge position x fence position x bias pin ->
//     best 84.62 (wedge between the two conversion word stores, fence after
//     the staging).
//   * 12-variant wedge position x fence position, pinned vs unpinned copy ->
//     unpinned copy is strictly worse (79-82%).
//   * 6 extern-declaration orders -> all byte-identical.
//   * -mps-float irrelevant: the original has no pair-single words in this
//     range (pair-disasm tool clean).
// All ~350 scratch variants live under <scratch>
//
// UNTIED LEVER: the doc-73 3-anchor colour set. If a 3-simultaneously-live
// page-address block in this ProDG build can be shown to reach the original
// register set, apply it there; the source already mentions all three
// constants exactly once each, so no source rewrite would be needed - only
// the colour rule.
//
// Inline asm emitted: 1 word of 91 (the dead-copy wedge, 1.1%, well under
// the 30% budget). Plus two zero-word memory fences. The fences follow
// promoted exemplars (src/fn_801FA318.c, src/fn_801B5DC4.c); the dead-copy
// wedge follows src/fn_801FA318.c's dead-copy trio.
//
// INERT: not registered in splits.txt/configure.py — never compiled by the
// build, not counted in objdiff progress.  activate via tools/wip.py.
// family=m2c range=0x802404A8-0x80240614 size=364B
#include "types.h"
#include "qb_constants.h"
extern s32 lbl_80306090;
extern char lbl_80306018[];
extern s32 lbl_802FFE98;
extern char lbl_802B1038[];
extern char lbl_802B1078[];
extern char lbl_802B1090[];
extern char lbl_802B0FD0[];
extern char lbl_802B0FF0[];
extern f64 lbl_802B10A8;
extern f32 lbl_802B10B0;
extern f64 lbl_802B10B8[];
typedef struct M118_b { char pad[0x34]; s32 unk0x34; } M118_b;
typedef struct M118_a { char pad[0x118]; M118_b *v118; } M118_a;
s32 MemAvailable(M118_b *);
s32 fn_8023FB5C(s32, s32);
void fn_8023FC44(void *);
s32 fn_802404A8(s32 arg0, s32 arg1) {
    union {
        u64 a[15];
        s32 w[30];
    } sp8u;
    volatile union {
        u32 w[2];
        f64 d;
    } cvt;
    s32 rng;
    s32 lim_a;
    s32 lim_b;
    s32 t2;
    s32 t3;
    f32 num;
    f32 den;
    s32 *b18;
    f64 mag;
    f32 kf;
    f64 thr;

    rng = arg1 - arg0;
    if (rng > fn_8023FB5C((s32)lbl_802B1038, -1) - lbl_80306090) {
        return 0;
    }
    lim_a = rng * fn_8023FB5C((s32)lbl_802B1078, -1);
    lim_b = rng * fn_8023FB5C((s32)lbl_802B1090, -1);
    fn_8023FC44(&sp8u.w[0]);
    b18 = (s32 *)lbl_80306018;
    if (*(b18 + 1) < lim_a) {
        return 0;
    }
    if (*(b18 + 2) < lim_b) {
        return 0;
    }
    t2 = fn_8023FB5C((s32)lbl_802B0FD0, -1);
    cvt.w[1] = (*(b18 + 2) - lim_b) ^ 0x80000000;
    {
        register s32 dc11 __asm__("r11");
        register s32 dc10 __asm__("r10");
        __asm__ volatile("mr %0,%1" : "=r"(dc10) : "r"(dc11));
    }
    cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
    mag = lbl_802B10A8;
    kf = lbl_802B10B0;
    thr = lbl_802B10B8[0];
    __asm__ volatile("" ::: "memory");
    num = (f32)(cvt.d - mag);
    cvt.w[1] = t2 ^ 0x80000000;
    cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
    __asm__ volatile("" ::: "memory");
    den = (f32)(cvt.d - mag);
    if (!(kf - num / den >= thr)) {
        goto ok;
    }
    return 0;
ok:
    t3 = fn_8023FB5C((s32)lbl_802B0FF0, -1);
    if (lim_b > 0) {
        t3 += lim_b;
    }
    return MemAvailable(((M118_a *)lbl_802FFE98)->v118->unk0x34) >= t3;
}
