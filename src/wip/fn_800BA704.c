// WIP DRAFT (non-matching) — hand rewrite from WANT disasm of 0x800BA704.
// Three transform loops over per-vertex 4-float rows: acc = row * M (3x3 rows at
// arg0+0x158/0x15C/0x160), output written as two 8-byte PS pairs per entry to
// lbl_8037E458 / lbl_8037E5D8 / lbl_8037E758; the 3rd loop is additionally
// gated on a flag word at row+0x20 and walks on a pointer sentinel.
// family=m2c range=0x800BA704-0x800BA9C8 size=708B
// FLAG: -mps-float
//
// VERDICT 2026-09-29: DIFF 98.3% masked, 174/177 words, got 708B == want 708B
// == symbols.txt size:0x2C4. Inline asm in the body: ZERO. Only 3 words differ,
// all of them the same single-instruction class (see RESIDUAL). Every other word
// of all three loops is byte-identical, and all 7 R_PPC_REL14 branch targets
// match want (verified against the DOL, §6bw method).
//
// HISTORY OF THIS FILE (score -> change):
//   25.4%  session-start baseline (696B, 3 words short per loop)
//   85.9%  output stores re-read the staged pair THROUGH THE STAGING POINTER
//   89.3%  loop 3 gets its own counter `m`
//   92.1%  loop 3 gets its OWN tp3/pp3/end3/stride3 (fixes the preheader
//          register rotation AND the whole loop-3 tail cascade)
//   98.3%  loop 3 also gets its own PS staging set pq3/P3/Q3/e33 (fixes the
//          loop-3 FPR rotation + the hoisted `psq_l f13,24(r1)`)
//  ============================================================================
// WHAT THE 89.3% -> 98.3% ROUND CHANGED, AND WHY (the generalisable part)
//  ============================================================================
//  RETAIL'S LOOP 3 USES DIFFERENT HARD REGISTERS FOR THE SAME ROLES AS LOOPS 1/2.
//  Loops 1 and 2 both want {pp=r6, tp=r7}; loop 3 wants {end=r6, pp=r7, tp=r8}.
//  That is a per-LOOP rotation, and cc1 gave loop 3 the SAME registers as loops
//  1/2 ({pp=r6, tp=r7}) with `end` relegated to r8.  The single reason cc1 could
//  reuse them is that the draft declared ONE `tp` / ONE `pp` / ONE `end` shared
//  by all three loops, so the allocator saw three copies of the same pseudos
//  (recycled from the same hardregs) instead of three fresh ones.
//  GIVING EACH LOOP ITS OWN SET OF POINTER VARIABLES is the whole fix —
//  separate `tp3/pp3/end3/stride3` alone took 89.3% -> 92.1% (the preheader
//  rotation AND its 12-word tail cascade, including the GPR of the second
//  output store's `psq_l`), and separate PS staging `pq3/P3/Q3/e33` took
//  92.1% -> 98.3% (the FPR rotation: retail loads the acc01 pair into the
//  register the acc[2] accumulator just died in — f13 in loops 1/2, f0 in
//  loop 3 — and cc1 could not reproduce that until the staging pseudos were
//  distinct, which also stopped sched1 from hoisting `psq_l ...,24(r1)` two
//  instructions early into the accumulator's slot).
//  This is §6an-3 / §6bu / §6al-184 ("one variable per web / per phase; shared
//  names merge webs") applied at the LOOP level instead of the statement level,
//  and it is the PS-mode twin of §6cx's GPR result. It is a SEMANTIC change
//  (no asm, no pin, no flag) and it is the only lever that moved these 11 words.
//  MEASURED (this round, loop-3 tail variants on the 92.1% base):
//    memory fence `__asm__ __volatile__("" ::: "memory")` before the pair load
//      92.1% (no-op; also swapped the acc[1] `lfs`/`fmadds` pair at 0x258/0x25C)
//    `pq`/`P` "=+f" barriers in 4 placements      83.6% / 83.6% / 91.0% / 92.1%
//    pair load moved before the acc[2] chain     92.1% (FPR shuffle, no gain)
//    `pairs[0]=P` before / after the acc[3] store 89.8% / 92.1% / 92.1% / 92.1%
//    `if (x)` vs `if (x != 0)`, file-local flag typedef, `*(s32*)((char*)pf+0x20)`
//      92.1% each (all no-ops)
//    inverted guard + `goto skip3`               92.1% (no-op)
//    `volatile __ps_t` pair read / `volatile f32` acc / volatile pair store
//      92.1% each (no-op)
//    full per-loop separation of stride/data/pf too (loops 1 AND 2 split)
//      78.5% — loop 2's stride then leaves r10 for r8, so only the THIRD loop
//      may be split off; loops 1/2 must keep sharing `stride`/`data`/`pf`.
//  ============================================================================
// RESIDUAL -- 3 words, all the same class, one per loop: the original emits
// a register-to-register pair copy where this build emits a memory reload of
// the same value out of the staging slot.
//
// The original 10-word loop tail loads the first accumulator pair, loads the
// scalar tail, stages the pair, stores the scalar, copies the staged pair
// through a register into the output, then loads the second accumulator pair,
// stages it, reloads it from the stage and stores it to the second output
// lane -- so the original emits one register copy plus one memory reload
// where this build emits two memory reloads. The word count is identical
// either way; the only defect is that one of the two loads is a copy in
// the original.
//
//  WHY IT IS NOT REACHABLE FROM PLAIN C (verified, not assumed):
//   * The word's kind is fixed by where the value lives, not by scheduling.
//     Staging through the array name then reading through the staging pointer
//     is the only spelling that yields the right length: reading by name lets
//     cc1 forward the store and the object collapses short (3 words short per
//     loop); reading through the pointer defeats the forward and forces a real
//     reload. Measured both lengths.
//   * Store and load through the same pointer spelling is not a way out -- a
//     standalone probe shows cc1 forwards the value into two back-to-back pair
//     stores with no load, which is the short case again. Only when the two
//     use different spellings does a reload survive, and a surviving reload
//     of a value cc1 believes is in memory is always a real load.
//   * A pair copy requires a copy of a vector value between two registers. This
//     cc1 coalesces every such copy constructed from plain C into the source
//     register and emits no copy at all. A copy is only emitted by the reload
//     pass when a value is both in a hard register and has a memory home,
//     i.e. its address escaped -- but an address-taken value is forced to
//     memory and then the reload is a load again.
//   * Explicit register-copy asm (one word per loop, a small fraction of the
//     function) is a loss, not a win: plain, volatile and early-clobber forms
//     all score far lower, with or without per-loop outputs. The extra word
//     changes the float allocation of the whole loop (the compiler picks
//     different float registers for the asm output and two accumulators swap
//     roles), which costs far more than the 3 words it fixes. Hard-register
//     pins to force the asm output's register either fail to build or are
//     silently dropped; without the tie they do not influence the choice.
//     There is no pair-copy builtin in this compiler (full builtin list
//     checked -- no copy builtin).
//
//  Best theory: this is the original register allocator making a suboptimal
//  choice (it copies between registers when it could have stored directly;
//  the reload pass evidently kept the value in a register and gave the store
//  a different destination instead of coalescing). This compiler never emits
//  a register copy for a copyable vector value, so the word has no plain-C
//  spelling here. Leaving the reload in place is the correct trade: it costs
//  exactly 3 of 177 words and keeps the object the right size.
//
// ---------------------------------------------------------------------------
// PARKED 2026-10-30: 98.3% -> 98.3% (no improvement; re-confirmed
// that 98.3% is the ceiling for every plain-C and 1-2-insn-asm spelling tried).
// TRIED 2026-10-14: pure pinned-FPR dest for the lane-1 copy (the one lever
// class the header had not measured — only asm-copies were). `register __ps_t
// d12 __asm__("fr0")` with `d12 = P; *tp = d12` in loops 1/2: 23.4% (700B —
// the stage store dies once pp[0] goes unread, exactly the predicted short
// case, plus recolor cascade). `volatile __ps_t pairs` alone: 74.0%.
// Pin + volatile combined: cc1 ICE (expr.c:2802). Pin decl alone is inert
// (98.3% — elided). All three outcomes close the pinned-dest route.
// family=m2c range=0x800BA704-0x800BA9C8 size=708B
// FLAG: -mps-float
//
// WHY PARKED: the residual is 3 words, one per loop, and all three are the SAME
// single-copy class: the original has a register copy where cc1 emits a memory
// reload of the same value out of the staging slot. Object length is already
// correct, every other word of all three loops is byte-identical, and the
// mechanism is the reload pass: the original output store reads a register
// while ours reads through the staging pointer. Confirmed by dumping the
// compiler's post-reload intermediate: a memory-to-memory move, which the
// backend splits into load plus store. Making that operand a register is not
// expressible: see the measured list.
//
// LEVERS TRIED (measured, all on the 98.3% base; the ONLY shapes that keep the
// object at the right length are the ones that leave the reload in place):
//   control (draft as inherited)                        98.3%  708B
//   out[0] from a register instead of through the stage  23.2% (forwarded)
//   staged plus direct register outputs (mixed)         23.2% (forwarded)
//   out[0] from the staging array name                   23.2%
//   out[0]/out[1] through volatile views                98.3% (inert)
//   volatile on the first stage store                   76.8% (*: shifts regs)
//   volatile on the second stage store                  91.5% (*: shifts regs)
//   volatile first store plus register output           23.2% (forwarded)
//   hard float-register pins on the staged value, many combos  23.2-25.4%
//   pins plus volatile store (10 combos)                23.2-25.4%
//   out[0] from a 2nd copy var of the staged value      23.2%
//   staging split into named values plus own pointers   22.6%
//   each output lane given its own base                 2.8% (severe)
//   register-copy plus store asm, plain / volatile / pinned  45-74% (708B)
//   fused copy-plus-store asm (replacing load plus store) 28.2%
//   flag sweep re-run on the 98.3% base: killing the scheduler overshoots,
//     every other flag combo exactly 98.3% or worse (inherited finding).
//   const-qualifying the matrix symbols: not applicable -- they are struct
//     fields, not extern globals, so the const lever has no declaration to
//     attach to here.
//
// UNTIED LEVER: the asm route is the only thing that produces a register copy
// at all, and it caps at 74.0% because the extra word changes the float
// allocation of the whole loop (one accumulator swaps registers and a frame
// reload lands in a different register). Per the pair-copy guidance, when a
// residual is exactly a reload where the original has a copy, stop: the length
// is already right and the word is the original allocator making a suboptimal
// choice. If someone finds a way to stop the float re-roll for a 1-word asm
// output, 74.0% is the base to attack -- do not re-run the pure-C
// store-source permutations.
//
// ============================================================================
// OTHER LEVERS CHECKED THIS ROUND (all 92.1%-base measurements unless noted)
//   Flag sweep on the 98.3% base: nothing beats the default. Killing the
//   scheduler overshoots badly (it does hoist the loop-3 reload, so killing
//   it fixes the position but destroys the rest of the function); other
//   scheduler / CSE / strength / jump flags are all no-ops; low opt levels
//   score far worse; several named flags do not exist in this compiler.
//   Latch form: countdown-unequal-zero is already right. Other latch spellings
//   and a signed counter all score far worse. Unsigned counter is required for
//   the expected compare kind.
//   Callee audit: this function makes no calls.
//   The row pointer must be read as a plain pointer, not a byte load, or the
//   compiler narrows it to a byte load plus sign extend.
//   L2 (pre-decrement latch): not applicable, see above.
//   INERT: not registered in splits.txt/configure.py — never compiled by the
//   build, not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
extern char lbl_8037E458[];
extern char lbl_8037E5D8[];
extern char lbl_8037E758[];

void fn_800BA704(Unk_8A4B2B78 *arg0) {
    __ps_t pq;
    __ps_t pairs[2];
    f32 acc[4];
    unsigned n;
    unsigned m;
    char *tp;
    __ps_t *pp;
    s32 stride;
    char *data;
    char *tp3;
    __ps_t *pp3;
    char *end3;
    s32 stride3;
    f32 *pf;
    __ps_t P;
    f32 e3;
    __ps_t Q;
    __ps_t pq3;
    __ps_t P3;
    __ps_t Q3;
    f32 e33;

    n = arg0->unk0x94;
    if (n-- != 0) {
        tp = (char *)lbl_8037E458 + (n << 4);
        stride = n << 4;
        pp = pairs;
        do {
            data = (char *)arg0->unk0x64;
            pf = (f32 *)(stride + (s32)data);
            acc[0] = (*(f32 *)(stride + (s32)data) * arg0->unk0x158)
                   + pf[1] * arg0->unk0x168
                   + pf[2] * arg0->unk0x178;
            acc[1] = (*(f32 *)(stride + (s32)data) * arg0->unk0x15C)
                   + pf[1] * arg0->unk0x16C
                   + pf[2] * arg0->unk0x17C;
            acc[2] = (*(f32 *)(stride + (s32)data) * arg0->unk0x160)
                   + pf[1] * arg0->unk0x170
                   + pf[2] * arg0->unk0x180;
            stride -= 0x10;
            pq = *(__ps_t *)&acc[0];
            P = pq;
            e3 = pf[3];
            pairs[0] = P;
            acc[3] = e3;
            *(__ps_t *)tp = pp[0];
            Q = *(__ps_t *)&acc[2];
            pairs[1] = Q;
            *(__ps_t *)(tp + 8) = pp[1];
            tp -= 0x10;
        } while (n-- != 0);
    }
    n = arg0->unk0x9C;
    if (n-- != 0) {
        stride = n * 0x18;
        tp = (char *)lbl_8037E5D8 + (n << 4);
        pp = pairs;
        do {
            data = (char *)arg0->unk0x98;
            pf = (f32 *)(stride + (s32)data);
            acc[0] = (*(f32 *)(stride + (s32)data) * arg0->unk0x158)
                   + pf[1] * arg0->unk0x168
                   + pf[2] * arg0->unk0x178;
            acc[1] = (*(f32 *)(stride + (s32)data) * arg0->unk0x15C)
                   + pf[1] * arg0->unk0x16C
                   + pf[2] * arg0->unk0x17C;
            acc[2] = (*(f32 *)(stride + (s32)data) * arg0->unk0x160)
                   + pf[1] * arg0->unk0x170
                   + pf[2] * arg0->unk0x180;
            stride -= 0x18;
            pq = *(__ps_t *)&acc[0];
            P = pq;
            e3 = pf[3];
            pairs[0] = P;
            acc[3] = e3;
            *(__ps_t *)tp = pp[0];
            Q = *(__ps_t *)&acc[2];
            pairs[1] = Q;
            *(__ps_t *)(tp + 8) = pp[1];
            tp -= 0x10;
        } while (n-- != 0);
    }
    m = arg0->unk0xA4;
    if (m-- != 0) {
        stride3 = m * 0x28;
        tp3 = (char *)lbl_8037E758 + (m << 4);
        end3 = (char *)lbl_8037E758 - 0x10;
        pp3 = pairs;
        do {
            data = arg0->unk0xA0;
            pf = (f32 *)(stride3 + (s32)data);
            if (((Unk_C7387A53 *)pf)->unk0x20 != 0) {
                acc[0] = (*(f32 *)(stride3 + (s32)data) * arg0->unk0x158)
                       + pf[1] * arg0->unk0x168
                       + pf[2] * arg0->unk0x178;
                acc[1] = (*(f32 *)(stride3 + (s32)data) * arg0->unk0x15C)
                       + pf[1] * arg0->unk0x16C
                       + pf[2] * arg0->unk0x17C;
                acc[2] = (*(f32 *)(stride3 + (s32)data) * arg0->unk0x160)
                       + pf[1] * arg0->unk0x170
                       + pf[2] * arg0->unk0x180;
                pq3 = *(__ps_t *)&acc[0];
                P3 = pq3;
                e33 = pf[3];
                pairs[0] = P3;
                acc[3] = e33;
                *(__ps_t *)tp3 = pp3[0];
                Q3 = *(__ps_t *)&acc[2];
                pairs[1] = Q3;
                *(__ps_t *)(tp3 + 8) = pp3[1];
            }
            tp3 -= 0x10;
            stride3 -= 0x28;
        } while (tp3 != end3);
    }
}
