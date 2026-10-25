// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F7D8-0x8025F808 size=48B
// range 0x8025F7D8-0x8025F808 size=0x30 (48B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *lbl_803CAB74;
void *OSGetArenaLo(void);
void OSSetArenaLo(void *);
void fn_8025FA60(void);

void fn_8025F7D8(void) {
    u32 *t = (u32 *)OSGetArenaLo();

    lbl_803CAB74 = t;
    OSSetArenaLo((void *)(t + 0x1000));
    fn_8025FA60();
}
