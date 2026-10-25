// Promoted from src/wip 2026-10-09 (mwcc region). family=hand range=0x8025FBB8-0x8025FC10 size=88B
// range 0x8025FBB8-0x8025FC10 size=0x58 (88B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

void fn_8025FBB8(void) {
    asm {
        li r3, 0
        tlbsync
        li r0, 8
        mtctr r0
    loop:
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        tlbie r3
        addi r3, r3, 0x1000
        bdnz loop
    }
}
