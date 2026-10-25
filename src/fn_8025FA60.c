// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025FA60-0x8025FAD8 size=120B
// range 0x8025FA60-0x8025FAD8 size=0x78 (120B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u8 *lbl_803CAB74;

void fn_8025FA60(void) {
    u32 i;

    for (i = 0; i < 0x4000; i += 4) {
        *(u32 *)(lbl_803CAB74 + i) = 0;
    }
}
