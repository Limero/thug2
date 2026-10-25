// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F710-0x8025F720 size=16B
// range 0x8025F710-0x8025F720 size=0x10 (16B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *lbl_803CAB74;

u32 fn_8025F710(s32 arg0) {
    return lbl_803CAB74[arg0];
}
