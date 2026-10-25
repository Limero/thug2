// WIP DRAFT (non-matching) — hand reconstruction 2026-09-28 from DOL disasm.
// family=m2c range=0x802093E8-0x80209514 size=300B
// PARKED 2026-09-28 at NEAR 66.7% (50/75 words), size-exact 300B.
//   Rewritten from scratch off the disassembly (the m2c body was 44% and had a
//   bogus `spC = temp_r3;` chain).  The whole control flow, the register map
//   (r29=arg0 r31=arg1 r30=scratch), the five out-params (sp8/spC/sp10/sp14/
//   sp18), the "known-zero register reuse" for `spC/sp10/sp14 = 0`, the
//   `or.`-test forms and the ENTIRE tail (GetInteger path + epilogue) are now
//   byte-exact.  Raising 44% -> 66.7% was: correct prototypes for all four
//   script helpers (GetArray had none -> spurious crclr), the inverted
//   `if (sp14 == 0) {integer path} else {structure path}` so the structure arm
//   becomes the fall-through (58.7 -> 66.7), and literal `= 0` out-param inits
//   (GCC reuses the tested zero register, matching `stw r3,0xc(r1)` /
//   `stw r30,0x10(r1)` / `stw r30,0x14(r1)`).
//   RESIDUAL (all 25 diffs, one 26-instruction window 0x80209470-0x802094D4):
//   ngccc does not cross-jump the `return 1` of the GetArray test into the
//   block that is the fall-through of the GetStructure test, so it emits
//   `beq L; li r3,1; b epi` inline and HOISTS a duplicate `li r3,0` into the
//   QB_TRICKSLOT branch shadow; retail has one shared `li r3,1` block (target
//   of `bne` at 0x80209470) plus a single shared `li r3,0` at 0x802094FC.
//   Leaves tried, all identical or worse: `return GetStructure(...) != 0;`
//   inline, staged `v = GetStructure(...)`, inverted `if (... == 0) return 0;
//   return 1;` (55.8%), and -fno-thread-jumps (66.7% no-op).  -fno-crossjumping
//   / -fno-reorder-blocks / -fno-jump-to-epilogue do not exist in ProDG cc1.
//   Retry hint: find another DOL function where retail emits the SHARED
//   return-0 block for two `if (...) return 0;` sites and copy its source
//   shape (the sharing must be reachable from C, just not from these four
//   spellings).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Script-template reader: probes QB_SCR / QB_SCRIPTS / QB_TEMPLATE /
// QB_TRICKSLOT on arg1, then resolves the trick-slot through arg0->unk0xA6C
// either as a structure (fn_80125954) or an integer (fn_80128228).
// Return convention is "1 unless a probe/slot fails".
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetStructure(s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_802093E8(Unk_59E38960 *arg0, CStruct *arg1) {
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;

    sp8 = 0;
    if (GetChecksum_2(arg1, QB_SCR, &sp8, 0) != 0) {
        return 1;
    }
    if (GetChecksum_2(arg1, QB_SCRIPTS, &sp8, 0) != 0) {
        return 1;
    }
    spC = 0;
    if (GetArray(arg1, QB_TEMPLATE, &spC, 0) != 0) {
        return 1;
    }
    sp10 = 0;
    if (GetChecksum_2(arg1, QB_TRICKSLOT, &sp10, 0) == 0) {
        return 0;
    }
    sp14 = 0;
    GetChecksum_2(arg0->unk0xA6C, sp10, &sp14, 0);
    if (sp14 == 0) {
        sp18 = sp14;
        if (GetInteger(arg0->unk0xA6C, sp10, &sp18, 0) != 0) {
            return 1;
        }
        return 0;
    }
    if (GetStructure(sp14, 0) != 0) {
        return 1;
    }
    return 0;
}
