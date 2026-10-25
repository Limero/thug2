// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F764-0x8025F76C size=8B
// range 0x8025F764-0x8025F76C size=0x8 (8B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern s32 lbl_803CAB7C;

void fn_8025F764(s32 arg0) {
    lbl_803CAB7C = arg0;
}
