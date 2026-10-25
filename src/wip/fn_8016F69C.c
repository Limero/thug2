// WIP DRAFT (non-matching) — hand-rebuilt from the original's disassembly.
// family=m2c range=0x8016F69C-0x8016F820 size=388B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress.  activate via tools/wip.py.
//
// PARKED: NEAR 97.94% — object is EXACTLY 388B and 95 of 97 words are
// byte-identical.  The two residual words ARE the first GetChecksum_2 call
// window: `addi r5,r1,0x18` (arg2 = &sp18) and `stw r30,0x18(r1)` (the
// `sp18 = temp_r30` store) are emitted store-first here and address-first in
// the original.  The identical construct in the second window (sp1C) IS
// store-first in the original, so the two windows genuinely differ and only
// the first one is a cc1 2.95 `sched2` ready-list tie between two equal-cost
// movsi insns: the post-reload RTL already has the address first, and all
// five ProDG builds in tree (3.5 / 3.5b140 / 3.7 / 3.8.1 / 3.9.3) emit the
// same 388B object.
//
// MEASURED LEVERS (all on this 97.94% body unless noted; do not re-run):
//   * naming + pinning the sp2C value to r5 was the 92.78 -> 97.94 fix (see
//     the sp8[3] note in the body); r9/r11/r0/r10/r3 pins score 92.78 /
//     90.72 / 88.66 / 94.85 / 90.72, and the name without the pin 92.78.
//   * dropping the temp_r30 r30 pin: 82.47% — still load-bearing.
//   * flags: -fno-sched-spec / -fno-sched-interblock / -fno-gcse /
//     -fno-thread-jumps / -fno-rerun-cse-after-loop / -fno-caller-saves /
//     -fdelayed-branch / -O3 inert; -Os 93.81%, -fno-schedule-insns 38.14%,
//     -fno-schedule-insns2 72.16%, -fno-expensive-optimizations 6.32% (380B).
//   * address forms, all 97.94%: folding sp18/sp1C into `s32 sp8[6]`;
//     function-scope and nested `register s32 p18 __asm__("r5")` holding
//     &sp18 (address-first in RTL, still store-first in emit); two chained r5
//     pins; `(s32 *)`/`(void *)`/`(volatile s32 *)` arg spellings; `sp18 = 0`
//     / `| 0` / `*(volatile s32 *)&sp18 = temp_r30`; chained assignment;
//     comma-in-arg2; a shared or literal zero per window; var_r27 moved to
//     the function top; the GetChecksum_2/GetInteger param-type matrix;
//     declaration-order permutations; sp2C read as `*(volatile u32 *)`.
//   * zero-code levers, all worse: "+r" barriers on temp_r30 (81.44% each),
//     a memory fence before (87.63%) / after (92.78%) the store,
//     "+r"(sp18) / "r"(&sp18) (6.19% / 5.15% — they spill the slot and break
//     the frame).
//   * one-instruction `addi` asm births for &sp18 land at the top of the
//     block (11.5%, 384B) in every spelling tried (volatile, non-volatile,
//     with a QB input, sharing r5 with v2C).
//
// No untried lever is known; the honest park reason is the sched2 cost tie.
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_8016F820(void *, void *, void *, s32, s32, s32, s32, s32);
void fn_8016F69C(void *arg0, CStruct *arg1) {
    u32 sp34;
    u32 sp30;
    Unk_12E59EE9 sp2C;
    u32 sp28;
    Unk_12E59EE9 sp24;
    u32 sp20;
    s32 sp18;
    s32 sp1C;
    /* Retail's out-param block for fn_8016F820 is ONE 16-byte object at
       r1+0x8..0x17: [0] holds sp34 (a store retail keeps although the
       value is dead), [1] is never touched, [2]/[3] receive the two 4-byte
       colour words copied out of sp24/sp2C and are passed as arg1/arg2.
       m2c split it into three scalars and lost the 8 bytes, which is why
       the inherited frame was 0x48 instead of 0x50.  Declaring it as a
       4-element array restores both the frame AND the dead store (the
       array's address escapes, so the store is not DCE'd). */
    s32 sp8[4];
    /* Named + pinned: puts the sp2C value in r5 (see header). */
    register s32 v2C __asm__("r5");
    s32 var_r27;
    /* ONE web reused for three roles (retail's `li r30,0` at the top,
       `stw r30,0x18` / `stw r30,0x1c` in the two GetChecksum_2 arg
       windows, then recycled for the ContainsFlag result and finally
       copied to r9 for arg6).  Without the reuse GCC folds the two
       zeroes onto var_r27 and rotates the whole callee-saved map. */
    register s32 temp_r30 __asm__("r30");
    temp_r30 = 0;
    sp18 = temp_r30;
    GetChecksum_2(arg1, QB_LIGHT_GROUP, &sp18, 0);
    var_r27 = 0;
    sp1C = temp_r30;
    GetChecksum_2(arg1, QB_RESET_LIGHT_GROUP, &sp1C, 0);
    temp_r30 = ContainsFlag(arg1, QB_UNKNOWN_0xE5B6C568);
    GetInteger(arg1, QB_COLOR, &sp20, 1);
    /* sp20 is written by the callee through a pointer, and the four reads
       below are four separate loads in retail (no CSE) — the volatile u16
       read is the only spelling that stops cc1 2.95 from narrowing the
       16-bit load to a byte load (it would read byte 3, not byte 0). */
    *((u8 *)&sp24) = *((u8 *)&sp20 + 0x3);
    sp24.unk0x1 = (s8) (sp20 >> 8U);
    sp24.unk0x2 = (s8) *(volatile u16 *) &sp20;
    sp28 = sp20;
    if (GetInteger(arg1, QB_SKY, &sp28, 0) != 0) {
        var_r27 = 1;
        *((u8 *)&sp2C) = *((u8 *)&sp28 + 0x3);
        sp2C.unk0x1 = (s8) (sp28 >> 8U);
        sp2C.unk0x2 = (s8) *(volatile u16 *) &sp28;
    }
    sp30 = -1U;
    sp34 = -1U;
    GetInteger(arg1, QB_UNKNOWN_0xDF1A695F, &sp30, 0);
    GetInteger(arg1, QB_UNKNOWN_0x8F639F94, &sp34, 0);
    v2C = *(u32 *)&sp2C;
    sp8[3] = v2C;
    sp8[2] = *(u32 *)&sp24;
    sp8[0] = sp34;
    fn_8016F820(arg0, &sp8[2], &sp8[3], var_r27, sp18, sp1C, temp_r30, sp30);
}
