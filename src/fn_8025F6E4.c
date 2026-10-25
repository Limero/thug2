// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F6E4-0x8025F710 size=44B
// range 0x8025F6E4-0x8025F710 size=0x2C (44B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *fn_8025FB84(u32 arg0);

u32 fn_8025F6E4(u32 arg0) {
    u32 w = fn_8025FB84(arg0)[1];

    return (w & 0x0FFFF000) + 0x80000000;
}
