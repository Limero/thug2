// WIP DRAFT (non-matching) — 96.05% (74/77 words), size-EXACT (304B == size:0x130).
// family=m2c range=0x801F3A1C-0x801F3B4C size=304B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT IT IS: pure-GPR skater-state reader (no paired-single words in the
// original, no FPR saves). Reads the QB_COMBO_SETS array, writes the count to
// arg0+0x328, then per element fills the 4-byte record at arg0+0x300:
//   +0 set_index (QB_SET_INDEX), +1 spin/180 (QB_SPIN), +2 num_taps
//   (QB_NUM_TAPS), +3 require_perfect flag (QB_REQUIRE_PERFECT).
// The loop pointer is arg0+0x301; the four stores are r31[-1], r31[+1],
// r31[+2], r31[0], i.e. plain source order.
//
// SEMANTICS (all verified against the original's argument registers and the
// callees' prologues; the m2c body was 21.8% because it had every one wrong):
//  * GetInteger is 4-arg and the first call's arg0 is the chained return of
//    fn_80129528 (no `mr r3` between the calls).
//  * the four hash constants are r4 values (lis+ori), not pointers.
//  * GetInteger/ContainsFlag are s32-returning prototypes (declared here);
//    the return type decides the argument-setup order.
//  * the guard is variable-vs-count (`var_r28 < arg0->unk0x328`), the count is
//    written back before the guard branch, and the latch re-reads +0x328
//    (not cached in a local).
//  * the +0x328 count field, the 0x0490F171/QB_COMBO_SETS hash and the /180
//    signed-division magic (mulhw+add+srawi7+subf) are all reproduced exactly.
// Frame 0x30 / stmw r25,0x14 / CR save at 0x34 falls out of the two s32 locals.
//
// PARKED RESIDUAL: exactly 3 words, all in the loop PREHEADER (the other 74
// words, including the whole loop body, frame and epilogue, are byte-identical).
// The original births the out-param address (`&spC`, r29) second, completes the
// /180 constant's low half third, and births the record pointer (r31) last;
// this body births the record pointer second, the address third and the
// constant's low half last. Register assignment (r25..r31), the frame/save
// span and the loop shape are already correct.
//
// WHY IT IS A FLOOR, NOT A SCHEDULING COIN — three independent mechanisms were
// isolated against post-reload RTL dumps:
//  1. A loop preheader is emitted as [source statements, in source order] ++
//     [loop-optimizer-hoisted insns, in body-creation order], so a pointer
//     defined in the preheader can never reach the last slot, while a pointer
//     defined in the body lands in the hoisted set at its body-scan rank. The
//     body needs the record pointer at its first byte store, so the only sound
//     spelling is a loop-carried pointer born in the preheader — slot 2.
//  2. The /180 constant is `lis`+`ori`, and reload hoists the `lis` anchor to
//     the top of the preheader while the `ori` stays in its body-scan slot;
//     that split is produced by two different passes.
//  3. An index-based pointer expression (`arg0 + 0x301 + i*4`) does put the
//     `addi` last, but IV rotation always moves the step to the body top and
//     pre-decrements the pre-loop value by one step (base 0x2fd + step, or
//     base 0x305 + step, which is semantically wrong). The ordering is proven;
//     the rotated step is the blocker.
//
// LEVERS MEASURED AND REJECTED (all on this body, size stayed 0x130 unless
// noted): moving the record-pointer init through 6 source positions and into
// the loop body (inert at 96.05%, or 80.26% as the last body statement);
// declaration-order permutations; preheader declaration initialisers; named
// preheader address pointer (correct addi order but an extra copy — 308B,
// 27.27%, identical with and without a register pin); one-insn asm anchor
// (breaks the division constant's hoisting); `volatile s32 zero` (26.58%);
// s32[2] out-param (25.97%); guard/latch variants that break the +0x328
// re-read (92.11%); while/wrap-the-guard/goto state machine (88.16%, 96.05%,
// 48.68%); six IV spellings (40-59 diffs); a 16-flag sweep (all no-ops or
// worse: -fno-schedule-insns2 82.89%, -fno-schedule-insns 71.05%, -Os 38.16%).
//
// VERIFIED: object has only .text (304B) and .rela.text — no private .rodata.
// All 9 relocations audited: the 6 R_PPC_REL24 calls name GetArray,
// fn_80129528, GetInteger x3 and ContainsFlag (real symbols.txt entries), and
// the 3 R_PPC_REL14 addends resolve to the original's two guard exits and the
// loop head, so the residual is a pure 3-instruction permutation with no
// control-flow difference. No inline instructions, no register pins, no FLAG.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_80129528(CStruct *, s32);
void fn_801F3A1C(Unk_7258DEBD *arg0, CStruct *arg1) {
    s32 spC;
    CStruct *sp8;
    s32 temp_r30;
    s32 temp_r4;
    s32 var_r28;
    s32 zero;
    char *var_r31;
    sp8 = NULL;
    if (GetArray(arg1, QB_COMBO_SETS, (s32 *)&sp8, 0) != 0) {
        var_r28 = 0;
        arg0->unk0x328 = sp8->unk0x4;
        if (var_r28 < (s32) arg0->unk0x328) {
            zero = 0;
            var_r31 = (char *)arg0 + 0x301;
            do {
                temp_r4 = var_r28;
                var_r28 += 1;
                temp_r30 = fn_80129528(sp8, temp_r4);
                spC = zero;
                GetInteger(temp_r30, QB_SET_INDEX, &spC, 0);
                *(u8 *)((char *)var_r31 - 0x1) = (u8) spC;
                spC = zero;
                GetInteger(temp_r30, QB_SPIN, &spC, 0);
                *(u8 *)((char *)var_r31 + 0x1) = (u8) (spC / 180);
                spC = zero;
                GetInteger(temp_r30, QB_NUM_TAPS, &spC, 0);
                *(u8 *)((char *)var_r31 + 0x2) = (u8) spC;
                *(u8 *)var_r31 = (u8) ContainsFlag(temp_r30, QB_REQUIRE_PERFECT);
                var_r31 += 4;
            } while (var_r28 < (s32) arg0->unk0x328);
        }
    }
}
