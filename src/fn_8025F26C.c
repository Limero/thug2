// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F26C-0x8025F284 size=24B
// range 0x8025F26C-0x8025F284 size=0x18 (24B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *lbl_803CAB64;

void fn_8025F26C(s32 arg0) {
    lbl_803CAB64[(arg0 >> 12) & 0x1FFF] |= 0x80000000;
}
