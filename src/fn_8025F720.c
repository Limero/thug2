// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F720-0x8025F730 size=16B
// range 0x8025F720-0x8025F730 size=0x10 (16B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *lbl_803CAB74;

void fn_8025F720(s32 arg0, u32 arg1) {
    lbl_803CAB74[arg0] = arg1;
}
