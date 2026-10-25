// PARKED 2026-10-17: 93.9% NEAR (31/33 words), size-exact 132B. Residual
// is a single adjacent swap at 0x34/0x38: want `addi r4,r4,0x2A40` before
// `psq_l f0,8(r11)`; the scheduler emits load-first (MEM > ALU priority).
// Probes this round (all reverted except the index-style scalar access,
// which scores identically and removes the char* casts): pure-C rewrite
// with one shared base + whole-struct copies scores 0.0%/120B (scalar
// lwz/stw, no pairs, single CSE base) — the opacity wedges and `+=`
// skeleton are load-bearing, not incidental; hoisting the p1 load into a
// temp before the d1[0] store collapses to 72.7% (f13 pressure, second
// copy changes color). Do not re-grind the swap without a new lever.
// WIP DRAFT (non-matching) — hand-rebuilt 2026-09-28, rewritten 2026-10-13.
// family=m2c range=0x800834E0-0x80083564 size=132B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Frameless leaf. Copies the 0x18-byte record at base+0x2A10 into BOTH
// base+0x2A28 and base+0x2A40, where base = arg0 + arg1*0x48. The record is
// {ps pair, ps pair, s32, u16, u16}; the per-member copies emit
// psq_l/psq_st for the two pairs and lwz/stw/lhz/sth for the scalar tail.
//
// 2026-10-13 rewrite: 93.9% NEAR (31/33 words), exact 132B size. The old
// "address-CSE wall" below was broken with three mechanisms:
//  1. `+=` compound assignment (b1/b2/b3/tmp) forces the in-place `add`
//     codegen while the pre-copies survive (cprop cannot propagate across
//     the modification) — reproduces want's mr/mr/add/add skeleton.
//  2. asm-output pointer wedges (`__asm__("" : "=r"(d1) : "r"(b1 + K))`,
//     doc-06 M5.0f/M5.0m technique) make each struct base CSE-opaque, so
//     the +8 second-pair access stays disp-form instead of bumping the
//     base with an extra `addi`.
//  3. `or %0,%1,%1` volatile asms force the three `mr` copies into their
//     pinned registers (r11/r8/r4). Plain C copies are DELETED by cprop
//     (measured: r11/r8 used uninitialised even under volatile empty asm),
//     and non-pinned copies coalesce to the wrong source register
//     (`mr r8,r10` instead of `mr r8,r11`). Precedent for real-asm single
//     moves: the frozen `__asm__ mtspr` window in fn_80145BB4.
// Residual (2 words, one adjacent swap at 0x34/0x38): want emits
// `addi r4,r4,0x2A40` (d2 formation) BEFORE `psq_l f0,8(r11)` (p1 load);
// 3.9.3's scheduler insists on load-first (MEM > ALU priority) under every
// source order tried (store/addi/load and addi/store/load both produce
// store/load/addi), with and without -fno-schedule-insns. Volatilising the
// d2 wedge fixes the swap but splits the scheduling region and breaks 4
// words upstream (81.8%). -fno-schedule-insns2 collapses to 63.6% (the
// post-regalloc pass is load-bearing for the matching tail). Genuine
// scheduler tie-break wall — do not re-grind without a new lever.
// 2026-10-15 probes (both REVERTED at 27.3%/164B, first-miss@8 — the mr/add
// skeleton is fragile, any perturbation breaks it early): whole-struct P16
// copy for the first pair (emits scalar lwz/stw instead of pairs, +32B),
// and hoisting `tmp += arg0` above the p0 load (breaks the or/add adjacency).
// Base 93.9% kept; the 0x34/0x38 swap stands.
// 2026-10-13 probes (all REVERTED, base 93.9% kept):
//  * memory barrier between d1[0] store and d1[1] load: 84.8% —
//    over-constrains, blocks p0's load hoist to 0x500 (want has it early).
//  * data-fence WITHOUT pins (s1b unpinned, depends on s1+d2): 81.8%, same
//    failure mode as pinned variant10 (d2 chain goes urgent, addi jumps to
//    0x28, s1b lands r9). Confirms urgency, not pinning, is the breaker.
// 2026-10-13 fence probe (variant10, REVERTED): routing the p1 load through
// an opacity fence (`s1b` pinned r11, `asm("" : "=r"(s1b) : "r"(s1),"r"(d2))`)
// to force [addi d2, load p1] order backfires — the s1->r11 pin flips the two
// `add` pairs (0x0C/0x10, 0x24/0x2C) and the fence makes the d2 chain urgent
// so d2's addi jumps above s2's (0x28/0x34 swap): 81.8%. Fence without the
// pins was not tried separately; the window-2 hybrid idea is also dead.
//
// OLD NOTE (2026-09-28, kept for the negative results): the first m2c body
// scored 0.0% (116B — scalar lwz/stw, no pairs: it lacked -mps-float and
// __ps_t members). Fully-inline `arg0 + arg1*0x48 + K` at all sites,
// offset-first shapes, whole-struct assignment, and a Blk-typed arg0 all
// fold to one shared base; `+r` barriers on the offsets collapse to 5%.
#include "types.h"

void fn_800834E0(char *arg0, s32 arg1) {
    register s32 b1 __asm__("r10");
    register s32 b2 __asm__("r11");
    register s32 b3 __asm__("r8");
    register s32 tmp __asm__("r4");
    register s32 w __asm__("r9");
    __ps_t *d1;
    __ps_t *s1;
    __ps_t *s2;
    __ps_t *d2;
    __ps_t p0;
    u16 h0;
    u16 h1;
    s32 w2;
    u16 h2;
    u16 h3;

    b1 = arg1 * 0x48;
    __asm__ volatile ("or %0,%1,%1" : "=r"(b2) : "r"(b1));
    __asm__ volatile ("or %0,%1,%1" : "=r"(b3) : "r"(b2));
    b1 += (s32)arg0;
    b2 += (s32)arg0;
    __asm__("" : "=r"(d1) : "r"(b1 + 0x2A28));
    __asm__("" : "=r"(s1) : "r"(b2 + 0x2A10));
    __asm__ volatile ("or %0,%1,%1" : "=r"(tmp) : "r"(b3));
    p0 = s1[0];
    b3 += (s32)arg0;
    __asm__("" : "=r"(s2) : "r"(b3 + 0x2A10));
    tmp += (s32)arg0;
    __asm__("" : "=r"(d2) : "r"(tmp + 0x2A40));
    d1[0] = p0;
    d1[1] = s1[1];
    w = ((s32 *)s1)[4];
    ((s32 *)d1)[4] = w;
    h0 = ((u16 *)s1)[10];
    ((u16 *)d1)[10] = h0;
    h1 = ((u16 *)s1)[11];
    ((u16 *)d1)[11] = h1;
    d2[0] = s2[0];
    d2[1] = s2[1];
    w2 = ((s32 *)s2)[4];
    ((s32 *)d2)[4] = w2;
    h2 = ((u16 *)s2)[10];
    ((u16 *)d2)[10] = h2;
    h3 = ((u16 *)s2)[11];
    ((u16 *)d2)[11] = h3;
}
