// ======================= PARK 2026-10-09: ASM WALL ========================
// mwcc GC/1.3.2 CANNOT emit this function from C/SDK source:
//  * the body needs privileged/RFI opcodes (mfsr/mtsr/mfmsr/mfspr/rfi/tlbie);
//  * an mwcc `asm { }` block is only an in-C wedge — the compiler still emits
//    its own prologue/epilogue around it (probe: an asm-only body came out
//    120B for this 84B function, wrapped in stwu/stw r0/`mr r10,r1` restore),
//    and `asm void f(){}` behaves the same;
//  * referencing an external function label from an asm block needs a C
//    declaration first, and the object is then larger than the split.
// House rule (AGENTS §5 + recipe 219/21393) keeps whole-body asm
// transcriptions out of src/*.c, so this function stays an assembly unit
// (the DOL is byte-identical either way).
// =========================================================================
// WIP DRAFT (non-matching) — hand-written from disasm 2026-10-09.
// family=hand range=0x8025FC10-0x8025FC64 size=84B
// INERT: not wired in configure.py — never compiled.
// Real-mode entry: SR7 = 0 (old SR7 saved to CAB84), SDR1 saved to CAB88,
// then FC64(msr & ~0x30 [DR/IR off], (SDR1 & 0xFFFF) + (*CAB70 & ~1), 0).
// Privileged (mfsr/mtsr/mfmsr/mfspr) — full-asm draft for mwcc; the ngccc
// sweep reports FAIL, expected.
#include "types.h"

extern u32 lbl_803CAB70;
extern u32 lbl_803CAB84;
extern u32 lbl_803CAB88;
extern void fn_8025FC64(u32 a, u32 b, u32 c);

void fn_8025FC10(void) {
    asm {
        li r3, 0
        mfsr r0, 7
        mtsr 7, r3
        stw r0, lbl_803CAB84@sda21(r13)
        mfmsr r3
        mfspr r4, 0x19
        lwz r0, lbl_803CAB70@sda21(r13)
        clrlwi r5, r4, 16
        stw r4, lbl_803CAB88@sda21(r13)
        rlwinm r0, r0, 0, 1, 15
        rlwinm r3, r3, 0, 28, 25
        add r4, r5, r0
        li r5, 0
        bl fn_8025FC64
    }
}
