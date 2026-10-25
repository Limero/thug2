// Promoted from src/wip 2026-10-09 (mwcc region). family=hand range=0x8025F988-0x8025FA60 size=216B
// range 0x8025F988-0x8025FA60 size=0xD8 (216B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u8 *lbl_803CAB78;

void fn_8025F988(void) {
    u32 i;

    for (i = 0; i < 0x1000; i++) {
        *(u8 *)((u8 *)lbl_803CAB78 + i) = 0;
    }
}
