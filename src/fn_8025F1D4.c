// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F1D4-0x8025F214 size=64B
// range 0x8025F1D4-0x8025F214 size=0x40 (64B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *lbl_803CAB64;
void fn_8025F234(s32 arg0);

u32 fn_8025F1D4(s32 arg0) {
    u32 v = lbl_803CAB64[(arg0 >> 12) & 0x1FFF] & 0x7FFFFFFF;

    if (v != 0) {
        return v;
    }
    fn_8025F234(arg0);
    return 0;
}
