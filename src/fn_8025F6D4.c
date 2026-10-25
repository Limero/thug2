// Promoted from src/wip 2026-10-09 (mwcc region). family=hand range=0x8025F6D4-0x8025F6E4 size=16B
// range 0x8025F6D4-0x8025F6E4 size=0x10 (16B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

void fn_8025F6D4(u32 arg0) {
    asm {
        rlwinm r0, r3, 0, 14, 19
        tlbsync
        tlbie r0
    }
}
