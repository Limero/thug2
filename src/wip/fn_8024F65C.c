// WIP DRAFT (non-matching) — PARKED 0%: hand-written assembly family
// family=m2c range=0x8024F65C-0x8024F794 size=312B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// BLOCKERS (do not re-grind without a new idea):
//  1. Hand-written prologue: stwu r1,-0x20 is followed by BODY code
//     (slwi r5,r5,4) BEFORE the individual stw saves of r14-r18, and the LR
//     lives in r18 (mflr r18 mid-prologue, mtlr r18 in the epilogue).
//     Re-probed 2026-10-03: ngccc 3.9.3 AND mwcc GC/1.3.2 + 1.2.5n ALL always
//     save LR as `mflr r0`+`stw r0` and group saves into `stmw`, so no pure-C
//     shape reaches this.
//  2. NON-ABI register calling convention: every bl fn_8024F794 passes its
//     arguments in FIXED registers r11/r12/r15 (never r3+), so plain C calls
//     cannot reproduce the call sites.
//  3. The callee (fn_8024F794) is wall-to-wall QUANTIZED paired-single:
//     psq_l/psq_st with I-field 6/7 addressing GQR6/GQR7, which THIS function
//     programs via mtspr 0x396 (=0x40004) / 0x397 (=0x70000) after saving the
//     old values in r16/r17. NOTE: GQR is NOT unreachable — see recipe 240 /
//     docs/parkings/41. The displaced-load split (builtin for d=0, raw asm for
//     d!=0) already cracked the psq kernels FAD0/F360/50170/50020/FEE0.
//     This function is parked on blockers 1+2 (prologue + non-ABI call sites),
//     which are 10% asm and inside budget — worth an attempt, not a park.
//
// This is an ASM-CORE DRIVER, not a dead end: only 8 of 78 insns (10%) need asm,
// well inside the 30% budget. Do NOT re-prove "unreachable from C" — measured.
//
// STRUCTURE (decoded from want, for reference):
//   info(r3): +4 u16 h; +8/+0xC/+0x10 plane pointers.
//   row(r4)<<6, col(r5)<<4 select the destination offset; r6 = source ptr;
//   r7 = flag bits. Saves GQR6/GQR7 + LR, then for each set bit of r7
//   (0x20,0x10,8,4,2,1 ascending) calls fn_8024F794(dst_line, dst_line+
//   h*4, src+K) with K = 0/0x80/0x100/0x180/0x200/0x280 — a 6-plane
//   conditional texture blend dispatch. Restores GQRs/LR/registers at end.
#include "types.h"

void fn_8024F65C(void *arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4) {
    /* parked: see header — hand-written asm + quantized-PS wall */
}
// RE-TRIAGE 2026-10-12: hand-asm/non-ABI blockers stand; no body change.
