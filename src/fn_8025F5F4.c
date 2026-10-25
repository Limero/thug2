// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F5F4-0x8025F61C size=40B
// range 0x8025F5F4-0x8025F61C size=0x28 (40B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *fn_8025FB84(u32 arg0);

u32 fn_8025F5F4(u32 arg0) {
    return (fn_8025FB84(arg0)[1] >> 8) & 1;
}
