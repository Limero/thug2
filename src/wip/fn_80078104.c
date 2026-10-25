// WIP DRAFT (PARKED, non-matching) — 94.1% (32/34 insns), size-exact 136B.
// Re-verified 2026-09-26 (no regression; no improvement found).
// family=hand range=0x80078104-0x8007818C size=136B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Semantics (fully confirmed from the DOL, no caller available): a 64-byte
// texture-tile byte fetch. arg0 = tile-array base, arg1 = width in texels,
// arg2 = x, arg3 = y. off = tile*0x40 + sub*2 where
//   tile = (y>>2)*(w>>2) + (x>>2)   and   sub = (y%4)*4 + (x%4)
// then four byte reads at off+0/+1/+0x20/+0x21 — i.e. the byte pairs of two
// vertically adjacent texels — with the +0 read guarded by arg7 and the
// +0x20/+0x21 reads by arg5/arg6.  arg4's store is unconditional.
//
// Matching keys found (all 32 reachable insns agree):
//   * `% 4` must NOT be written as `x % 4` (that folds to clrlwi/andi, 2.9%) —
//     want derives it from the already-live quotient: `x - ((x >> 2) << 2)`.
//   * `(arg0 + off + k)` must be written with the pointer FIRST, otherwise the
//     address add comes out `add r11, r4, r3` instead of want's `add r11, r3, r4`.
//   * arg2/arg3 are u32 (srwi), arg1 is s32 (`arg1 >> 2` -> srawi).  The tile
//     accumulator must be UNSIGNED (`slwi r4,r4,6`, not srawi); the sub `*2`
//     must be written `* 2` — `<< 1` emits `slwi r6,r6,1`, not `add r6,r6,r6`.
//   * arg2>>2 must land in a callee-saved reg (r30) — the frame, stmw/lmw span
//     and the arg0[off] lbzx operand roles all already agree.
//
// 2026-10-08: the "inline b into the off statement" route predicted by
// this note was MEASURED and confirms it -- writing off as one expression
// `(tile << 6) + (((y%4)*4 + x%4) * 2)` with the tile chain first gives
// 88.24% (4 diffs): the two adds are right but `slwi r4,r4,6` jumps ahead of
// `add r6,r6,r6`. Do not re-try; the current sub-first order is optimal.
// PARKED on an irreconcilable 2-insn tie between two INDEPENDENT 3-operand
// adds. The want computes the tile partial sum in r4 from r4 and r30 at
// address 0x80078130 and the sub partial sum in r6 from r6 and r5 at
// address 0x80078134. The current output computes those same two partial
// sums in the opposite order, issuing the r6 from r6 and r5 computation at
// 0x80078130 and the r4 from r4 and r30 computation at 0x80078134.
// The two chains are completely disjoint, so this is a pure sched1 ready-list
// tie-break and it is result-irrelevant.
//
// CORRECTED DIAGNOSIS (this round; supersedes "post-reload/sched2 ordering"):
// the final order equals sched1's order here — sched2 is a no-op reordering
// for this block.  Proved by compiling with -fno-schedule-insns2 and reading
// the pre-RA sequence: sched1 emits [... slwi r6,r6,2 | S1 | T1 | S2 | T2 | R]
// and sched2 preserves exactly that relative order.  Note -fno-schedule-insns2
// is NOT a usable lever: dropping the post-RA pass changes register allocation
// wholesale (the arg2>>2 web lands in scratch r11, so r30 is never saved) and
// the whole function collapses to 2.9%.
//
// The tie is one-sided in a way no source shape can flip: the tile add's last
// input (`arg2>>2`, want insn 4 `srwi r30,r5,2`) is ready many instructions
// before the sub add's last input (`x%4`, want insn 8 `subf r5,r11,r5`), yet
// sched1 issues the SUB add first in every spelling tried — so the ready list
// is not stable-in-our-favour and there is no textual ordering that reverses
// it.  Corollary: any variant that does put the tile expression first in the
// source ALSO drags `slwi r4,r4,6` up ahead of `add r6,r6,r6`, costing a 2nd
// pair of diffs — i.e. the current sub-first statement order is the best of
// the reachable layouts, not an arbitrary choice.
//
// No recipe can be mined: the 5-insn tail window at 0x80078130 and the 4-insn
// window are each UNIQUE in the whole of .text (verified by byte scan), and
// twin_scan/near_twin_scan find no matched sibling.  The function also has NO
// direct `bl` caller anywhere in .text (it is pointer-dispatched) — an
// apparent hit at 0x80078064 is a `b` branch inside the unrelated
// bppp->bytes helper at 0x80077FEC-0x8007808C, not a call — so the argument
// semantics above come from the DOL alone.
//
// 2026-10-19: "+r" order wedge tried (named s3/t2/s2/t3 + add/add window):
// frame blows 0x10->0x18 with extra stmw (named temps spill), DIFF. The wedge
// needs low-pressure call-arg sites, not tight arithmetic. Reverted.
// Tried this round, ALL 94.1% with the identical 2-word residual (or worse):
// tile-first in every split (2-stmt, 3-stmt, single expression, `<<6`-first,
// `off +=`) -> 88.2%; sub chain typed s32 -> 88.2%; full 4-way split of all
// intermediates (t/s/m3/m2 named) -> 94.1%; `mullw` operand order swapped ->
// 91.2%; `u8 *p = arg0 + off` base-pointer restructure -> 94.1%; local
// declaration order swapped -> 94.1%; `<< 1`/`<< 2` shift forms -> 91.2%
// (`<< 1` breaks the doubling opcode); `x % 4` -> 2.9%.
// Flags: -fno-schedule-insns2 / -fno-schedule-insns / the pair -> 2.8-8.3%
// (all break RA, see above); -O1 10.3%; -O3, -fno-sched-interblock,
// -fno-thread-jumps, -fno-strict-aliasing, -fno-gcse, -fno-strength-reduce
// -> 94.1% unchanged.  -fno-ree / -fno-move / -fno-cse / -fno-crossjumping /
// -fno-delete-null-pointer-checks / -fno-if-conversion do not exist in ProDG
// cc1 (compile error).  Earlier round also swept -fschedule-insns*,
// -fno-delayed-branch, -mcpu=740/745/7450/7410/603/601/602, -mtune=*,
// -mpowerpc-gfxopt, -fno-omit-frame-pointer.
//
// Classified as the doc-15 "pure scheduler tie / call-arg-setup coin-flip"
// wall (see AGENTS.md recipe 51) — parking is the correct outcome, not a
// missing recipe.
// 2026-10-21: the two-add tie was re-measured; -fno-schedule-insns2 and
// -fno-schedule-insns still break register allocation (2.8-8.3%), and the
// sub-chain-first statement order remains the only 94.1% layout.
#include "types.h"

void fn_80078104(u8 *arg0, s32 arg1, u32 arg2, u32 arg3, u8 *arg4, u8 *arg5, u8 *arg6, u8 *arg7) {
    u32 off;
    u32 b;

    b = (((arg3 - ((arg3 >> 2) << 2)) * 4) + (arg2 - ((arg2 >> 2) << 2))) * 2;
    off = ((((arg3 >> 2) * (arg1 >> 2)) + (arg2 >> 2)) << 6) + b;
    *arg4 = *(arg0 + off + 1);
    if (arg7 != NULL) {
        *arg7 = arg0[off];
    }
    if (arg5 != NULL) {
        *arg5 = *(arg0 + off + 0x20);
    }
    if (arg6 != NULL) {
        *arg6 = *(arg0 + off + 0x21);
    }
}
