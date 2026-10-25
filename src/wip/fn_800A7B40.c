// PARKED 2026-10-30: 59.8% -> 59.8% (no improvement found).
// family=m2c range=0x800A7B40-0x800A7C88 size=328B
//
// WHY PARKED: the residual is the RTL `sched` pass's choice of WHICH TWO of the
// next row's four `lfs` loads it hoists into the 2-slot gap between a row's 2nd
// and 3rd `fmadds`. ngccc's cost model ranks the column-1 load (m[1][r+1]) FIRST,
// so it hoists {m[1][r+1], m[0][r+1]}; retail hoists {m[0][r+1], m[2][r+1]}.
// The ranking is forced and is the OPPOSITE of retail's: the FMA contraction
// makes column 1 the operand of the *standalone* `fmuls`, so its load feeds one
// extra insn before the `fmadds` chain (dependent chain 5) while column 0 is an
// `fmadds` multiplicand (chain 4) — a "hoist the longest chain first" cost model
// must pick column 1, and it does. Verified: `-fno-schedule-insns` removes the
// hoisting entirely (40.2%), `-fno-schedule-insns2` shows `sched` (pre-reload)
// already made the {m1,m0} choice before the allocator runs, and the pre-sched
// RTL load order is FIXED by `expand` sinking each single-use temp into the
// multiply that uses it — so the source cannot reorder it. Hence every staging
// permutation (measured 4 temp orders x 3 decl orders + inline-vs-temp per
// column, 2D vs flat vs pointer bases) yields a byte-identical object.
// LEVERS TRIED (this round, all with the full base cflags + -mps-float):
//   59.8  baseline (unchanged, best body)
//   59.8  temp-assign orders 0123/1023/0213/1203 (58.5 for 3210) — all
//         byte-identical to baseline except 3210, which is worse
//   59.8  all four products inline (no temps)            58.5
//   59.8  column 1 inline / columns 0,2 temp            58.8
//   59.8  temps for cols 0+2 only (changes RTL order)    58.5
//   59.8  vec values into named v0..v3 temps per row     59.8
//   59.8  vec via `f32 *vp` alias                        59.8
//   50.0  col-1 volatile (cast / volatile f32* / char*)
//   48.8  col-2 volatile      43.9 col-3 volatile
//   50.0  `f32 (*M)[4]` 2-D base + flat cast for col 1  41.5 reversed product
//         spelling, 41.5 matrix-first product spelling, 50.0 flat f32[16]
//   3.7   ANY `register f32 x __asm__("frN")` pin: the whole FMA block is DCE'd
//         (16 single-variable pins across all 4 columns x 4 rows) — cc1 2.95.2
//         with -mps-float drops the pinned pseudo and the whole body with it
//   40.2  -fno-schedule-insns   47.6 -fno-schedule-insns2   31.7 -O1
//   42.7  -Os ; 59.8 (no-op) -O3, -mcpu 603/4050/440, -mtune generic,
//         -fno-sched-spec, -fno-sched-spec-load, -fno-sched-interblock,
//         -fsched-spec-load-dangerous, -fno-gcse, -fno-strength-reduce,
//         -fno-branch-count-reg, -fno-caller-saves, -fno-defer-pop,
//         -fno-expensive-optimizations, -fno-thread-jumps
//   all five in-tree ProDG (3.5 / 3.5b140 / 3.7 / 3.8.1 / 3.9.3) produce a
//         BYTE-IDENTICAL object -> not a compiler-version artefact
// UNTIED LEVER: nothing in C. Reaching retail's hoist set needs a cost model
//   that ranks m[0] above m[1], i.e. the col-1 load must NOT feed a separate
//   multiply — which the machine code (`fmuls f13,f13,f0` on vec[1]*m[1][r])
//   rules out. Strong evidence the block was scheduled in a different context
//   (an inlined/split origin) rather than as a standalone 4-row function.
//   If anyone revisits: the only 0-asm lever left is a `volatile double`/
//   `"+f"`-barrier trick on ONE col-1 load to make it unschedulable, which
//   forces the gap to be filled from {m0,m2,m3}; measured 50.0% because the
//   volatile also pins the load's own position inside its row, so the 3 per-row
//   vec/fma interleave windows break too.
//
// WIP DRAFT (non-matching) — hand reconstruction from DOL disasm
// family=m2c range=0x800A7B40-0x800A7C88 size=328B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Semantics: out[r] = sum_c vec[c] * M[c][r] over the f32 matrix at arg1+0x10
// (vec = fn_800A7B38(arg2) = arg2+8, a 4-float vector). If arg1->unk0x8 == 0
// the else-arm is skipped and arg0[0..15] = vec[0..15] (raw 16-byte pair copy,
// retail stores the first pair here and the second from the shared tail).
// Returns arg0. The merged Unk_C8FEE62D class types the matrix slots s32; the
// file-local Mat4 with f32 m[4][4] is required (lfs loads, no fctiwz phantom).
//
// STATUS: PARKED 2026-10-30 (r1/50) at 59.8% NEAR (test_wip_drafts.py),
// 49/82 words. Compiled .text 0x148 == symbols.txt size:0x148 == header marker
// (328B), only .text + .rela.text in the object (no .rodata/.data pool, so no
// doc-14 promote caveat), 0 inline-asm instructions, and all 4 relocations
// (REL14 type 11 +.text+0x3c at 0x24 -> 0x800A7B7C = want's `bne`;
//  REL24 -> fn_800A7B38 at 0x28 and 0x3c; REL24 +.text+0x12c at 0x38 ->
//  0x800A7C6C = want's `b`) agree with WANT's branch/call targets. All 8
// opcode-4 words are psq_l (OPCD 56) / psq_st (OPCD 60) — hand-decoded, NO
// VMX wall anywhere. Promote-clean-if-matched.
//
// MATCHES: prologue/guard/then-arm (0x00-0x38), row 0 of the FMA block
// (0x40-0x6C, byte-exact: addi r9 / t1 / m10 / m00 / t0 / fmuls / m20 / t2 /
// fmadds / m30 / t3 / fmadds), the mixed r9/r31 addressing (column 1 through
// the `m` pointer so the base folds to arg1+0x10 with 0x10..0x1c
// displacements; columns 0/2/3 off r31), every one of the 4 fmuls + 12 fmadds
// structurally, all 4 stfs at 0x18/0x1c/0x20/0x24, the 7-insn PS pack
// (0x114-0x12C) and the epilogue.
//
// RESIDUAL (33 words, all in rows 1-3 of the FMA block): WHICH two of a row's
// four matrix loads GCC 2.95 hoists above the PREVIOUS row's final `stfs`.
// WANT's global m-load emission order is (m10, m00, m20, m30 | m01, m21, m11,
// m31 | m02, m22, m12, m32 | m03, m23, m13, m33 | m04, m24, m14, m34) — i.e.
// per row the first two of the NEXT row (m0, m2) jump back over the store.
// GOT instead hoists (m1, m0) of the next row, which delays that row's m2/m3
// by 0x0C/0x04 and rotates every downstream FPR (f11 vs f0 for t1, f8 vs f13
// for m31, ...). First divergence, row 1:
//   At 0x800A7BB0 retail loads f10 from 0x14(r31) where the build loads it
//   from 0x14(r9), and at 0x800A7BB4 retail loads f9 from 0x34(r31) where
//   the build loads it from 0x14(r31). The next pair diverges further:
//   retail at 0x800A7BC0 loads f11 from 0x14(r9) and at 0x800A7BD4 f8 from
//   0x44(r31), while the build at 0x800A7BC4 loads f0 from 4(r3) and at
//   0x800A7BCC f8 from 0x34(r31).
// The instruction COUNT, addresses, arithmetic and stfs positions are all
// identical; only the 2-slot look-ahead choice (and the FPR colouring that
// follows from it) differs. It is a machine-scheduler/regalloc artefact, not a
// DAG difference: every source-level staging of the four loads (named temps in
// any of 4 orders, a full 8-value per-row staging, a next-row "prefetch",
// a `volatile f32 *` alias) produces BYTE-IDENTICAL objects for the same
// order, i.e. the front end folds them straight back into the same RTL.
//
// LEVERS TRIED (all with -mps-float, scores from tools/score_body.py):
//   53.7  baseline (term 1 first: vec[1]*m[1] then vec[0]*m[0] ...)
//   57.3  swap the first two products of every row (see AGENTS 6by: the
//         source's FIRST product is the one contracted into the fmadds, the
//         SECOND is the fmuls seed)  <-- the real fix, +3.6
//   58.5  + `volatile __ps_t sp10` on the pack temp, so the final
//         `psq_l f0,16(r1)` reloads the copy slot instead of CSE-ing back to
//         0x20(r1)   <-- +1.2
//   59.8  + read each row's four matrix slots into named f32 temps first
//         (order irrelevant — 4 orders measured, all byte-identical)  +1.3
//   50.0  volatile alias for the column-1 loads   (worse)
//   42.7  volatile alias for the columns 0/2/3 loads   (worse)
//   48.8  stage all four m values, order m0,m1,m2,m3   (worse)
//   46.3  right-associated sum   39.0  4-statement `acc` accumulator
//   40.2  products written matrix-first   35.4  `m` declared before `vec`
//   32.9  m before vec (strong -25 signal: declaration order matters here)
//   22.0  2D `arg1->m[1][r]` instead of the pointer (kills the r9 base entirely,
//         loads become 0x20(r31)/0x24(r31)...)
//   19.5  an unrolled-for-r loop (with and without -funroll-loops)
// Flags, all scored on the 57.3% baseline and on the final body: -fno-sched-spec,
// -fno-sched-interblock, -fno-gcse, -fno-expensive-optimizations,
// -fno-thread-jumps, -fno-cse-follow-jumps, -fno-strength-reduce,
// -fno-caller-saves, -fno-defer-pop, -fno-cse-skip-blocks,
// -fno-branch-count-reg, -fsched-spec-load, -fno-delayed-branch (all 59.8/57.3,
// no-ops); -fno-schedule-insns (42.7), -fno-schedule-insns2 (45.1),
// -O1 (39.0), -Os (41.5) (all worse); -O3, -mtune/-mcpu 440/750/4050,
// -mhard-float, `const Mat4 *arg1` (all no-ops). `-ffp-contract=`, `-mfma`,
// `-mno-fma`, `-fno-align-functions`, `-fno-reorder-blocks`, `-fno-cse`,
// `-fno-peephole2`, `-fno-if-conversion`, `-fno-crossjumping` do not exist in
// ProDG cc1 (compile error), so the contraction and the post-regalloc schedule
// are both un-disableable here.
//
// BEST THEORY: the residual is a sched2 (machine-dependent, post-regalloc)
// look-ahead decision in one straight-line basic block. The RTL is fully
// determined — the sum's association order is forced by want's fmuls/fmadds
// sequence, so no other C spelling exists — and it is invariant under every
// staging permutation measured. The only remaining handle would be perturbing
// the REGISTER allocation that sched2 consumes (want homes the m0 column in
// f10 and m2 in f9 for rows 1-2 but f7/f9 in row 3, so it is not a per-column
// pin either); a FPR hard-reg pin sweep and a per-object -mps-float schedule
// flag ladder would be the next thing to burn, but 33 words of a 328-byte
// straight-line float block is the classic parked tail for this pass.
#include "types.h"
#include "structs.h"

typedef struct {
    f32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
} Vec4;

typedef struct {
    char pad0x0[0x8];
    s32 unk0x8;
    char pad0xC[0x4];
    f32 m[4][4];
} Mat4;

Vec4 *fn_800A7B38(s32 arg);

__ps_t *fn_800A7B40(__ps_t *arg0, Mat4 *arg1, s32 arg2) {
    struct { __ps_t sp8; volatile __ps_t sp10; f32 res[4]; } loc;
    if (arg1->unk0x8 == 0) {
        Vec4 *vec = fn_800A7B38(arg2);
        arg0[0] = ((__ps_t *)vec)[0];
        arg0[1] = ((__ps_t *)vec)[1];
    } else {
        Vec4 *vec = fn_800A7B38(arg2);
        f32 *m = (f32 *)((char *)arg1 + 0x10);
        f32 a0, b0, c0, d0, a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3;
        a0 = arg1->m[0][0];
        b0 = m[4];
        c0 = arg1->m[2][0];
        d0 = arg1->m[3][0];
        loc.res[0] = vec->unk0x0 * a0 + vec->unk0x4 * b0 + vec->unk0x8 * c0 + vec->unk0xC * d0;
        a1 = arg1->m[0][1];
        b1 = m[5];
        c1 = arg1->m[2][1];
        d1 = arg1->m[3][1];
        loc.res[1] = vec->unk0x0 * a1 + vec->unk0x4 * b1 + vec->unk0x8 * c1 + vec->unk0xC * d1;
        a2 = arg1->m[0][2];
        b2 = m[6];
        c2 = arg1->m[2][2];
        d2 = arg1->m[3][2];
        loc.res[2] = vec->unk0x0 * a2 + vec->unk0x4 * b2 + vec->unk0x8 * c2 + vec->unk0xC * d2;
        a3 = arg1->m[0][3];
        b3 = m[7];
        c3 = arg1->m[2][3];
        d3 = arg1->m[3][3];
        loc.res[3] = vec->unk0x0 * a3 + vec->unk0x4 * b3 + vec->unk0x8 * c3 + vec->unk0xC * d3;
        loc.sp10 = *(__ps_t *)&loc.res[2];
        loc.sp8 = *(__ps_t *)&loc.res[0];
        arg0[0] = loc.sp8;
        arg0[1] = loc.sp10;
    }
    return arg0;
}
