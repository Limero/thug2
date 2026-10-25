// PARKED 2026-10-17 (WIP DRAFT, non-matching) — best body: 65/85 words byte-exact after resolving
// the REL14/REL24 targets (= 76.5% true; the masked sweep reports 77.6% because
// it blanks every branch word), got=340B=want. Everything before 0x80093034 is
// byte-identical; the remaining 20 words are one block-order mirror.
// RECONSTRUCTED 2026-10-05 from the DOL disasm. The inherited m2c draft scored
// 0.0% (wrong struct offsets: it read 0x150/0xa instead of 0x54/0x8).
//
// This is a 3-way sort comparator: (s32 (*)(S**, S**)) — x = (*arg0)->0x54,
// y = (*arg1)->0x54; k1/k2 = x|y->0x1C->0x20->0x8 (u16); the decision keys are
// d = 0x5E - 0x60 (u16 diff, computed as a 32-bit sub of two lhz) and, when the
// d's tie and d > 0, a pair of f32s at ->0x58[i]->0x14->0x4->0x8.
//
// Score ladder (masked / TRUE-reloc-applied): m2c 0.0 → struct 25.9 → cache
// k1/k2 + `!(a<b)` spelling 52.9 → `return d1 > d2 ? 1 : -1` 60.0/65.1 →
// `k1 > k2 ? 1 : -1` (see below) 67.1 → SEPARATE d temps in the else branch
// 76.5.  The whole first 0xF0 bytes are now byte-identical.
//
// Two findings worth keeping (both confirmed with a 6-line micro-test compiled
// by ngccc, see below):
//  1. Ternary spelling is NOT cosmetic for the u16 compare:
//       `k1 <= k2 ? -1 : 1`            -> cmplw; li r3,1; bgtlr; li r3,-1; blr
//       `k1 > k2 ? 1 : -1`             -> cmplw; li r3,-1; blelr; li r3,1; blr
//     want uses the second shape (and, because `blelr` needs the -1 materialised
//     right before it, the compiler CANNOT share that `li r3,-1` with the
//     else-branch `return -1` — which is exactly why want has a dedicated
//     `li r3,-1; blr` at 0x80093038 instead of reusing the tail).
//     Micro-test (u16 a,b): `a<=b?-1:1` gave 1-first/bgtlr, `a>b?1:-1` gave
//     -1-first/blelr; for s32 it is the mirror (`a<=b?-1:1` -> 1-first).
//  2. The else branch MUST use its own temporaries (d3/d4), not the d1/d2 of
//     the first branch: sharing them cost 9 points (67.1 -> 76.5) and, more
//     importantly, re-coloured the WHOLE true path (r9/r11 swap on the 0x60
//     loads + the slwi order). With d3/d4 the true path is byte-exact.
//
// Remaining 20 words are one block-order mirror in the else region, no semantic
// gap (verified: 65/85 with all branch targets resolved, see below):
//   want 0x80093024: cmpwi/beq 0x3038(lwz/cmpwi/ble 0x3040)/li r3,-1; blr at
//        0x3038 inline -> [k2 test][y test][-1][k1k2 test][d-cmp][k-tail @end]
//   got:  beq/bgt to a SHARED `li r3,-1` at the very end ->
//        [k2 test][y test][k1k2 test][k-tail][d-cmp][-1 @end]
// i.e. want falls INTO the -1 exit and branch-false over it, got jumps to it.
// Everything tried to steer it (25+ variants): `k2==0||y>0`/`y<=0&&k2!=0`/two
// separate ifs/`goto`-labelled -1/nested else/`k1==k2`-body vs `k1!=k2`-body,
// -fno-schedule-insns/-insns2, -fno-reorder-blocks (INVALID flag on ngccc —
// like -jump-optimize/-optimize-sibling-calls), -fno-branch-probabilities
// (no-op). All plateaux at 65/85.
// 2026-10-17 re-triage: early-return else (`if (k2==0||y>0) return -1;`)
// shortens 340B->324B (merges harder, worse); s32 k1/k2 locals shorten to
// 320B (u16 locals are load-bearing for size). Nested u16 form stays best;
// residual is a cross-jumping tail-merge (two `li r3,-1; blr` folded to one
// shared tail), not source shape.
//
// NOTE (tooling): the masked sweep reports a higher % here because it masks
// every REL14/REL24 word. ngccc emits a reloc for EVERY internal branch whose
// addend is the target's .text offset, so the raw field is a placeholder and
// the branch target it decodes to is bogus — resolve it as (S + A - P) before
// believing a disasm. tools/reloc_diff.py now does this (2026-10-05), so its
// want/got branch targets are directly comparable: use it instead of reading
// the masked score for anything that contains a branch.
// family=hand range=0x80092F30-0x80093084 size=340B
#include "types.h"

typedef struct K92F30 {
    char pad0x0[8];
    u16 unk0x8;
} K92F30;
typedef struct M92F30 {
    char pad0x0[0x20];
    K92F30 *unk0x20;
} M92F30;
typedef struct G92F30 {
    char pad0x0[8];
    f32 unk0x8;
} G92F30;
typedef struct F92F30 {
    char pad0x0[4];
    G92F30 *unk0x4;
} F92F30;
typedef struct E92F30 {
    char pad0x0[0x14];
    F92F30 *unk0x14;
} E92F30;
typedef struct S92F30 {
    char pad0x0[0x1C];
    M92F30 *unk0x1C;
    char pad0x20[0x58 - 0x20];
    E92F30 **unk0x58;
    u16 unk0x5A;
    u16 unk0x5E;
    u16 unk0x60;
    char pad0x62[0x6C - 0x62];
    s32 unk0x6C;
} S92F30;
typedef struct R92F30 {
    char pad0x0[0x54];
    S92F30 *unk0x54;
} R92F30;

s32 fn_80092F30(R92F30 **arg0, R92F30 **arg1) {
    S92F30 *x;
    S92F30 *y;
    u16 k1;
    u16 k2;
    s32 d1;
    s32 d2;
    s32 d3;
    s32 d4;
    G92F30 *p;
    G92F30 *q;

    x = (*arg0)->unk0x54;
    y = (*arg1)->unk0x54;
    k1 = x->unk0x1C->unk0x20->unk0x8;
    k2 = y->unk0x1C->unk0x20->unk0x8;
    if (k1 == 0 || x->unk0x6C > 0) {
        if (k2 == 0 || y->unk0x6C > 0) {
            d1 = x->unk0x5E - x->unk0x60;
            d2 = y->unk0x5E - y->unk0x60;
            if (d1 == d2) {
                if (d1 > 0) {
                    p = x->unk0x58[x->unk0x60]->unk0x14->unk0x4;
                    q = y->unk0x58[y->unk0x60]->unk0x14->unk0x4;
                    if (p != 0 && q != 0) {
                        if (p->unk0x8 > q->unk0x8) {
                            return 1;
                        }
                        if (!(p->unk0x8 < q->unk0x8)) {
                            return 0;
                        }
                        return -1;
                    }
                }
                return 0;
            }
            return d1 > d2 ? 1 : -1;
        } else {
            return 1;
        }
    } else {
        if (k2 != 0 && y->unk0x6C <= 0) {
            if (k1 != k2) {
                return k1 > k2 ? 1 : -1;
            }
            d3 = x->unk0x5E - x->unk0x60;
            d4 = y->unk0x5E - y->unk0x60;
            if (d3 == d4) {
                return 0;
            }
            return d3 > d4 ? 1 : -1;
        }
        return -1;
    }
    return 0;
}
