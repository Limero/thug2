// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F730-0x8025F73C size=12B
// range 0x8025F730-0x8025F73C size=0xC (12B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u8 *lbl_803CAB78;

u8 fn_8025F730(s32 arg0) {
    return lbl_803CAB78[arg0];
}
