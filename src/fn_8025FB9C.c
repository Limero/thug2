// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025FB9C-0x8025FBB8 size=28B
// range 0x8025FB9C-0x8025FBB8 size=0x1C (28B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 lbl_803CAB70;

u32 fn_8025FB9C(u32 arg0) {
    u32 d = arg0 - lbl_803CAB70;

    return 0x7E000000 | ((d & 0x38) << 19) | ((d & 0xFFC0) << 6);
}
