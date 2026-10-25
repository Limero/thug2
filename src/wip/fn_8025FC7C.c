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
// family=hand range=0x8025FC7C-0x8025FCA8 size=44B
// INERT: not wired in configure.py — never compiled.
// Translation restore: SDR1 = arg0, MSR |= 0x30 (DR/IR on) via SRR1,
// SRR0 = 0x8025FCA4 (own trailing nop — falls through into FCAC), rfi.
// Full-asm draft for mwcc.
#include "types.h"

void fn_8025FC7C(u32 sdr1) {
    asm {
        sync
        mtspr 0x19, r4
        sync
        mfmsr r3
        ori r3, r3, 0x30
        mtspr 0x1b, r3
        lis r5, 0x8026
        addi r5, r5, -0x35c
        mtspr 0x1a, r5
        rfi
        nop
    }
}
