// PARKED 2026-09-30: 53.5% -> 55.6% (55/99). One of the four
// `__asm__ ... "memory"` barriers was STALE SCAFFOLDING and is now deleted
// (barriers 1,2,4 kept, #3 removed) - see MEASURED LEVERS below.
// Object audit: .text 0x18C = 396B = symbols.txt size = this header's size=;
// the object has NO .rodata/.data (so masked-EXACT would be promote-clean) and
// ZERO relocations of any kind (leaf: no `bl`, no branch, every address is a
// displacement off r3 / an `addi r1`), so the REL14/REL24/label audits of
// "BEFORE YOU CLAIM 100%" are vacuous here - there is nothing relocation-
// masked to hide. Inline asm emitted: 0 instructions (3 zero-code barriers).
//
// FINDING (the one real gain, worth keeping):
//   The 4 barriers are at (1) after block1's t[] stores, (2) after
//   `arg2 = t[0..1]`, (3) after block2's t[] stores, (4) after `buf[2]=t[2..3]`.
//   Barrier #3 forced ALL FOUR t[] stores of block 2 to precede the buf reads.
//   WANT does NOT do that: at 0x800FD960 want's `psq_l f0,0x18(r1)` (the pair
//   read of t[0..1]) sits BETWEEN the t[3] store (0x800FD958) and the t[2]
//   store (0x800FD964) - only t[0]/t[1] precede it, because those are the only
//   ones it reads. Deleting #3 is exactly right and is worth +2.1 points; the
//   previous note's claim that all four barriers are load-bearing is CORRECTED.
//   Full 16-subset sweep of the barrier positions (mask = bits 1,2,3,4):
//     none 25.3 | {1} 39.0 | {2} 12.1 | {3} 47.5 | {4} 48.5 | {1,2} 47.5
//     {1,3} 39.0 | {1,4} 39.0 | {2,3} 18.2 | {2,4} 33.3 | {3,4} 48.5
//     {1,2,3} 39.0 | {1,2,4} 55.6 <-- BEST | {1,3,4} 39.0 | {2,3,4} 18.2
//     {1,2,3,4} 53.5 (old baseline)
//
// RESIDUAL (44/99 words) - UNCHANGED AND STILL THE WALL:
//   Block 1 is byte-exact for all 40 compute instructions; only its 5-word tail
//   differs (want [stfs t0][stfs t1][fmadds t3][stfs t3][psq_l][stfs t2] vs
//   got [stfs t0][fmadds t3][stfs t1][stfs t2][stfs t3][psq_l]) - i.e. the t2/t3
//   store order (want t0,t1,t3,t2; got t0,t1,t2,t3) plus the fmadds position.
//   Block 2 (0x800FD8E0..0x800FD96C, ~39 words) is t-MAJOR in want: chain
//   t[0] runs to completion and stores (0x800FD8F4), then t[1] (0x800FD950),
//   then t[3] (0x800FD958), then t[2] (0x800FD964). GOT is k-MAJOR: all four
//   k=0 products, then all four k=1 fmadds, etc. Per-chain the k-order is
//   IDENTICAL in both blocks (1,0,2,3) and in both arms, so the association and
//   the expression shape are NOT the cause - only the inter-chain scheduling of
//   block 2 is. It is a pure `sched` ready-list decision inside one basic block.
//
// MEASURED LEVERS (do not re-grind; all on the 55.6% body):
//   Flag sweep, 14 flags, NONE better and 4 much worse:
//     -fno-sched-spec / -fno-sched-interblock / -fno-gcse / -fno-thread-jumps
//     / -fno-expensive-optimizations / -fno-rerun-cse-after-loop / -O3
//     / -fno-strength-reduce / -fno-branch-count-reg  = all 55.6% (no-ops)
//     -fno-schedule-insns 16.2 | -fno-schedule-insns2 32.3 | -Os 35.4 | -O1 14.1
//     -fno-sched-round: not a cc1 option (FAIL).
//   Oracle found and ported (§6dc/§6dr/§6fn - there are NO callees, so the
//   search had to be by shape): src/fn_8010E6DC.c is a PROMOTED, byte-exact
//   4x4x4 transform. It schedules the same four chains t-MAJOR with the store
//   right after each chain - i.e. retail's scheduler does produce this shape
//   for this computation. Its source is right-nested with k=3 outermost:
//     (in[3]*m[..]) + ((in[2]*m[..]) + ((in[0]*m[..]) + (in[1]*m[..])))
//   Porting that EXACT parenthesisation to both blocks (R1), to block 2 only
//   (R2) and to block 1 only (R3) all score 55.6% - cc1 2.95's expand_expr
//   canonicalises all three to the same k-order 1,0,2,3, so the association is
//   NOT a lever here. The oracle's Quad/Pair union result idiom
//   (`union {__ps_t p[2]; f32 f[4];}`, results read back as .p[0]/.p[1]) is the
//   same idiom this draft already uses via t[] + pb[1]; porting it verbatim
//   (G_union) did not compile - the union needs its own typedef of __ps_t.
//   Per-block named multipliers s0..s3 (E) 53.5; + FPR register pins for
//   disjoint block-1/block-2 allocation - the hypothesis was that want's two
//   blocks use DISJOINT multiplier registers (block1 {f0,f10,f11} vs block2
//   {f5,f6,f7,f8}) while got reuses block 1's, which is what forces got's
//   k-major (k-major needs 12 live FPRs, t-major only ~7): P_s1 (s1->fr8) 54.5,
//   P_full (all four pinned to fr8/fr6/fr7/fr5) 54.5, P_s0 53.5, P_s3 53.5,
//   P_s1s0/P_s1s3 54.5, and on top of the 55.6% body Q_named 54.5,
//   Q_s1/Q_s1s0/Q_full 55.6. The pins DO bind (each is worth ~1 word) but they
//   do not change the schedule. Naming both blocks' multipliers (F) 45.5.
//   Named scalar results per block (H) 53.5, H_namedres 53.5.
//   Replacing the "memory" barrier with a `+f` register barrier on the four
//   results (H2) collapses to 13.1% - a register barrier does NOT hold the
//   float MEMORY ops, so the memory barrier is genuinely required for the FPR
//   ordering; H3 (mixed) did not compile.
//   `volatile f32 *m0 = arg0->m[0]` for block 2's k=0 row (T1) 3.0, for all
//   four rows (T2) 0.0, rows 0-1 (T3) 1.0 - volatile pins those loads to
//   program order but destroys the whole block. Do not retry.
//   Block-2 t[] statements reordered to want's store order t0,t1,t3,t2 (Q_store)
//   55.6 - neutral. Barrier 3's absence already gives got the t2-store freedom.
//   So: the residual is `sched`'s choice of t-major vs k-major for block 2
//   only, unreachable by any flag, pin, barrier, volatile, association or
//   variable-naming lever measured here. Next untried idea: a 1-instruction
//   non-volatile `asm` freeze on block 2's FIRST k=0 `fmuls` to break the
//   equal-cost tie that lets the other three hoist above it (§6fs r2/r3 says
//   the freeze and the non-volatility are an AND).
//
// UPDATED 2026-09-25: genuine semantic reconstruction. 21.2% -> 53.5% (53/99),
// exact 396B size, and `-fno-expensive-optimizations` is no longer needed (only
// `-mps-float`). Re-scored with tools/ps_diff.py (the PS-aware tool).
// WIP draft - still PARKED, see the residual below.
//
// Semantics recovered (this is a 4x4 matrix * 8-float transform):
//   t[j] = arg1[0]*m[0][j] + arg1[1]*m[1][j] + arg1[2]*m[2][j] + arg1[3]*m[3][j]
// with m[k][j] at arg0+0x60+16k+4j (arg0->m is a plain f32[4][4] at 0x60).
//   block 1: out[0..1] = t[0..1], out[2..3] = buf[2..3] (= t[2..3])
//   block 2: out[4..5] = buf[2..3] (= t[2..3]), out[6..7] = t[0..1]
// The block-2 shuffle is a REAL retail mis-index (out[4..5] gets t[2..3] and
// out[6..7] gets t[0..1], i.e. the pairs are swapped) - it is what the bytes
// say, not a decompiler artifact. Frame is 0x28: buf(4 f32) at r1+0x08,
// t(4 f32) at r1+0x18, 8-byte save area, no callee-saved GPRs, no FPRs.
//
// THREE GENUINE BUGS FIXED IN THE PREVIOUS DRAFT (all found by hand-decoding want):
//  1. `pb[2]` was wrong. `buf` is 4 f32 = exactly TWO `__ps_t`, so the second
//     pair is `pb[1]`; `pb[2]` read 8 bytes PAST buf, i.e. it aliased t[0..1].
//     The old body therefore computed out[2..3] = t[0..1] (wrong values) and
//     emitted `psq_l 24(r1)` where want has `psq_l 8(r9)`. Fixed -> pb[1].
//  2. `pb` has to be a REAL, assigned pointer (`= (volatile __ps_t *)buf`) so
//     that want's `addi r9, r1, 8` + `psq_l f0, 8(r9)` addressing materialises,
//     while the two pair STORES must still be spelled through `buf` (r1
//     displacement). That exact split (`buf` for the stores, `pb` for the
//     volatile load) reproduces all 8 tail instructions in both blocks plus the
//     prologue addi - verified byte-exact.
//  3. Sum operand order: GCC 2.95 expand_expr SWAPS THE FIRST TWO OPERANDS of
//     a commutative FP add (probed on a 1-statement reduction: text 0,1,2,3
//     emits 1,0,2,3; text 1,0,2,3 emits 0,1,2,3). want's multiplier order is
//     k=1,0,2,3, so the source must be written 0,1,2,3 - which is also the
//     natural reading of the matrix.
//
// The four `__asm__ __volatile__("" ::: "memory")` barriers are LOAD-BEARING,
// not decoration: they emit no code but block the FPR scheduler from
// re-interleaving the four independent dot products. With them the whole
// 40-instruction block-1 compute (and its exact register allocation f9/f8/f4/
// f11/...) matches want instruction-for-instruction; without the post-compute
// one GCC issues the k=0 group out of order (m[0][1] before m[0][0], t[1]
// before t[0]) and the score drops to 25%.
// SEARCHED: 24x24 (k-term x t-statement) permutations - natural (0,1,2,3) is
// the best at 53%; a 16x16 sweep with block 1 / block 2 statement orders
// decoupled does not beat it; ~10 scheduling flags (insns/insns2/spec/
// interblock/gcse/rerun-cse/schedule-insns/stalled-insns) are all no-ops or
// worse at this shape; 4 scalar accumulators, a union-typed t, __ps_t[2] buf,
// volatile t[], decl-order permutations of buf/t/pb, and the earlier `pb[2]`
// aliasing form were all tried and are worse.
//
// REMAINING BLOCKER (53.5%, 46/99 words): pure ngccc 2.95 FPR scheduling inside
// one basic block, in two places, with no known source form or flag:
//  (a) block-1 tail, 3 words: want issues [stfs t0][stfs t1][fmadds t3]
//      [stfs t3][psq_l t01][stfs t2] - the t[3] multiply lands one slot early
//      and the t[2] store one slot late versus this body. The 8 tail
//      instructions themselves (psq_l/psq_st, incl. the volatile pb[1]
//      round-trip) already match.
//  (b) block-2 compute, ~39 words: want completes the t[0] chain first and then
//      schedules t[1..3] k-major (3 muls, then 3 fmadds, then k=2, then k=3),
//      whereas this body schedules all four k-major. Block 1 wants k-major and
//      block 2 wants t[0]-first from the SAME source text, i.e. the two blocks
//      differ only by the register pressure the scheduler sees at the top of
//      block 2 - a scheduling/allocator-order artifact, not a source-shape one.
// extra_cflags: -mps-float
// family=m2c range=0x800FD81C-0x800FD9A8 size=396B
#include "structs.h"
struct G5Mtx { char _pad[0x60]; f32 m[4][4]; };
void fn_800FD81C(struct G5Mtx *arg0, f32 *arg1, Unk_C1F9F519 *arg2) {
    f32 buf[4];
    f32 t[4];
    volatile __ps_t *pb = (volatile __ps_t *)buf;
    t[0] = arg1[0] * arg0->m[0][0] + arg1[1] * arg0->m[1][0] + arg1[2] * arg0->m[2][0] + arg1[3] * arg0->m[3][0];
    t[1] = arg1[0] * arg0->m[0][1] + arg1[1] * arg0->m[1][1] + arg1[2] * arg0->m[2][1] + arg1[3] * arg0->m[3][1];
    t[2] = arg1[0] * arg0->m[0][2] + arg1[1] * arg0->m[1][2] + arg1[2] * arg0->m[2][2] + arg1[3] * arg0->m[3][2];
    t[3] = arg1[0] * arg0->m[0][3] + arg1[1] * arg0->m[1][3] + arg1[2] * arg0->m[2][3] + arg1[3] * arg0->m[3][3];
    __asm__ __volatile__("" ::: "memory");
    *(volatile __ps_t *)&buf[0] = *(__ps_t *)&t[0];
    *(__ps_t *)arg2 = *(__ps_t *)&t[0];
    __asm__ __volatile__("" ::: "memory");
    *(volatile __ps_t *)&buf[2] = *(__ps_t *)&t[2];
    arg2->unk0x8 = pb[1];
    t[0] = arg1[4] * arg0->m[0][0] + arg1[5] * arg0->m[1][0] + arg1[6] * arg0->m[2][0] + arg1[7] * arg0->m[3][0];
    t[2] = arg1[4] * arg0->m[0][2] + arg1[5] * arg0->m[1][2] + arg1[6] * arg0->m[2][2] + arg1[7] * arg0->m[3][2];
    t[1] = arg1[4] * arg0->m[0][1] + arg1[5] * arg0->m[1][1] + arg1[6] * arg0->m[2][1] + arg1[7] * arg0->m[3][1];
    t[3] = arg1[4] * arg0->m[0][3] + arg1[5] * arg0->m[1][3] + arg1[6] * arg0->m[2][3] + arg1[7] * arg0->m[3][3];
    *(volatile __ps_t *)&buf[0] = *(__ps_t *)&t[0];
    *(volatile __ps_t *)&buf[2] = *(__ps_t *)&t[2];
    __asm__ __volatile__("" ::: "memory");
    arg2->unk0x10 = *(__ps_t *)&t[0];
    arg2->unk0x18 = pb[1];
}
// 2026-10-22: 56.6% (was 55.6%): rows written t[0], t[2], t[1], t[3].
