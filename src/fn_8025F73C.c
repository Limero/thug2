// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F73C-0x8025F764 size=40B
// range 0x8025F73C-0x8025F764 size=0x28 (40B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u8 *lbl_803CAB78;

void fn_8025F73C(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        lbl_803CAB78[arg0] = 1;
    } else {
        lbl_803CAB78[arg0] = 0;
    }
}
