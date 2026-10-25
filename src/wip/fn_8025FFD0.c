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
// family=hand range=0x8025FFD0-0x80260110 size=320B
// INERT: not wired in configure.py — never compiled.
// ISI exception handler (naked: no prologue, entered from the 0x400
// vector via FCAC). Mirrors FE28 (DSI) but tests SRR0 (0x1A) instead of
// DAR against [0x7E000000, 0x80000000) with the SRR1 (0x1B) bit1 check.
// Debugger path fills the current context and rfis to the full-save
// continuation at 0x802600C4; the fallthrough full-save path spills
// r0-r2 + stmw r6..r31 + GQRs and ends `b 0x80260110` (fn_80260110).
// The 0x8025FFBC/0x8025FFC0 trampoline words (FCAC) sit inside this range.
// Full-asm draft for mwcc.
#include "types.h"

void fn_8025FFD0(void) {
    asm {
        mtspr 0x110, r4
        mtspr 0x111, r5
        mtspr 0x112, r6
        mfcr r4
        mtspr 0x113, r4
        mfspr r5, 0x1a
        li r6, 0x7e
        slwi r6, r6, 24
        cmplw r5, r6
        blt skip_dbg
        mfspr r5, 0x1a
        li r6, 0x80
        slwi r6, r6, 24
        cmplw r5, r6
        bge skip_dbg
        mfspr r5, 0x1b
        rlwinm r6, r5, 0, 1, 1
        cmplwi r6, 0
        beq skip_dbg
        mfspr r4, 0x113
        mtcrf 0xff, r4
        mfspr r4, 0x110
        mfspr r5, 0x111
        mfspr r6, 0x112
        mtspr 0x110, r4
        lwz r4, 0xc0(0)
        stw r3, 0xc(r4)
        mfspr r3, 0x110
        stw r3, 0x10(r4)
        stw r5, 0x14(r4)
        lhz r3, 0x1a2(r4)
        ori r3, r3, 2
        sth r3, 0x1a2(r4)
        mfcr r3
        stw r3, 0x80(r4)
        mflr r3
        stw r3, 0x84(r4)
        mfctr r3
        stw r3, 0x88(r4)
        mfxer r3
        stw r3, 0x8c(r4)
        mfspr r3, 0x1a
        stw r3, 0x198(r4)
        mfspr r3, 0x1b
        stw r3, 0x19c(r4)
        mr r5, r3
        mfmsr r3
        ori r3, r3, 0x30
        mtspr 0x1b, r3
        lwz r3, 0xd4(0)
        lis r5, 0x8026
        addi r5, r5, 0xc4
        mtspr 0x1a, r5
        rfi
    skip_dbg:
        mfspr r4, 0x113
        mtcrf 0xff, r4
        mfspr r4, 0x110
        mfspr r5, 0x111
        mfspr r6, 0x112
        nop
        nop
        stw r0, 0(r3)
        stw r1, 4(r3)
        stw r2, 8(r3)
        stmw r6, 0x18(r3)
        mfspr r0, 0x391
        stw r0, 0x1a8(r3)
        mfspr r0, 0x392
        stw r0, 0x1ac(r3)
        mfspr r0, 0x393
        stw r0, 0x1b0(r3)
        mfspr r0, 0x394
        stw r0, 0x1b4(r3)
        mfspr r0, 0x395
        stw r0, 0x1b8(r3)
        mfspr r0, 0x396
        stw r0, 0x1bc(r3)
        mfspr r0, 0x397
        stw r0, 0x1c0(r3)
        b fn_80260110
    }
}
