// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025FB84-0x8025FB9C size=24B
// range 0x8025FB84-0x8025FB9C size=0x18 (24B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 lbl_803CAB70;

u32 fn_8025FB84(u32 arg0) {
    return lbl_803CAB70 | ((arg0 & 0x3FF000) >> 6) | ((arg0 & 0x1C00000) >> 19);
}
