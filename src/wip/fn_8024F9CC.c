// WIP DRAFT (non-matching) — PARKED 0%: hand-written assembly family
// family=m2c range=0x8024F9CC-0x8024FAD0 size=260B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// BLOCKERS:
//  1. Hand-written prologue: stwu r1,-0x20, then body code (slwi r5,r5,4)
//     BEFORE the individual stw saves of r14-r18; LR held in r18
//     (mflr r18 mid-prologue / mtlr r18 epilogue). ngccc always groups
//     callee-saves first and saves the LR to the frame — unreachable from C.
//  2. NON-ABI register calling convention: each bl fn_8024FAD0 receives its
//     two stream pointers in FIXED registers r11/r12.
//  3. Float argument passed OUT-OF-BAND: lfs f8, 0(r9) loads the constant at
//     lbl_8024FD8C into f8 before the calls; fn_8024FAD0 multiplies with it
//     (ps_madd fN,fN,f8,f8). No C prototype can convey an f8 argument.
//  4. Callee is quantized-PS wall-to-wall (psq I-field 6/7 via GQR7, which
//     this function programs: mtspr 0x397 = 0x40004).
//
// STRUCTURE (decoded from want):
//   info(r3): +4 u16 h; +8/+C/+10 plane ptrs; info2(r6): +8/+C/+10 second
//   set of plane ptrs. row(r4)<<6 + col(r5)<<4 offsets both sets. Sets
//   GQR7=0x40004, loads f8 = *(f32 *)lbl_8024FD8C, then six fn_8024FAD0(r11,
//   r12) calls walking both plane lists in parallel (+0x20 line steps,
//   +h*8 plane stride), halving h/row/col after the fourth call — a dual
//   6-plane texture blend driver.
#include "types.h"
extern f32 lbl_8024FD8C;

void fn_8024F9CC(void *arg0, s32 arg1, s32 arg2, void *arg3) {
    /* parked: see header — hand-written asm + f8 out-of-band arg + PS wall */
}
