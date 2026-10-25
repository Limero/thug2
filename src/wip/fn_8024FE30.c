// WIP DRAFT (non-matching) — PARKED 9%: hand-written assembly family
// family=m2c range=0x8024FE30-0x8024FEE0 size=176B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// BLOCKERS:
//  1. Hand-written prologue: stwu r1,-0x10, then body code (slwi r5,r5,4)
//     BEFORE the individual stw saves of r14/r15; LR held in r15 (mflr r15
//     mid-prologue / mtlr r15 epilogue). Re-probed 2026-10-03: ngccc 3.9.3 AND
//     mwcc GC/1.3.2 + 1.2.5n all always save LR as `mflr r0`+`stw r0` and group
//     saves into `stmw` — no pure-C shape reaches this.
//  2. GQR save/restore around quantized-PS helpers: mfspr r14,0x397 /
//     mtspr 0x397 (=0x70004) ... mtspr 0x397,r14. The callees
//     (fn_8024FEE0/fn_80250020/fn_80250170) were quantized-psq bodies and were
//     PARKED as a HARD WALL — that was WRONG. Recipe 240 (docs/parkings/41)
//     cracks them: FEE0 and 50020 are now byte-identical matches, 50170/F360/
//     FAD0 already were. Do not re-park the psq kernels on this claim.
//  3. NON-ABI register args at every call: destination pointers in r11
//     (fixed register), not r3+ — but file-scope `register s32 x __asm__("r11")`
//     pins reach these from C.
//
// Parked on blockers 1+3 only (prologue LR-dance + non-ABI sites). Those are
// ~11% asm, inside the 30% budget, so this is worth attempting — measured, not
// assumed.
// STRUCTURE (decoded from want):
//   info(r3): +4 u16 h; +8/+C/+10 plane ptrs. row(r4)<<6, col(r5)<<4.
//   Saves GQR7/LR, sets GQR7=0x70004, then per plane: fn_8024FEE0(line),
//   fn_8024FEE0(line+0x20), fn_80250020(line+8), after halving h/row/col
//   fn_80250020(line+0x28), and for planes +0xC/+0x10 fn_80250170(line +
//   acc) where acc = (h>>1)*(col>>1)... a 3-plane mip-flush driver.
#include "types.h"

void fn_8024FE30(void *arg0, s32 arg1, s32 arg2) {
    /* parked: see header — hand-written asm + GQR quantized-PS wall */
}
