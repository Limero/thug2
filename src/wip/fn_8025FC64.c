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
// family=hand range=0x8025FC64-0x8025FC7C size=24B
// INERT: not wired in configure.py — never compiled.
// Real-mode hop: SRR1 = arg0, SRR0 = 0x0025FC7C (physical alias of FC7C;
// the clrlwi clears the top bit), rfi. Extra args from the FC10 call site
// (computed SDR1 value, 0) are ignored. Full-asm draft for mwcc.
#include "types.h"

void fn_8025FC64(u32 a, u32 b, u32 c) {
    asm {
        mtspr 0x1b, r3
        lis r5, 0x8026
        addi r5, r5, -0x384
        clrlwi r5, r5, 1
        mtspr 0x1a, r5
        rfi
    }
}
