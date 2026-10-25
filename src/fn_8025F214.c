// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F214-0x8025F234 size=32B
// range 0x8025F214-0x8025F234 size=0x20 (32B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *lbl_803CAB64;

u32 fn_8025F214(s32 arg0) {
    return (lbl_803CAB64[(arg0 >> 12) & 0x1FFF] & 0x7FFFFFFF) != 0;
}
