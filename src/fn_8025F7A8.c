// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F7A8-0x8025F7D8 size=48B
// range 0x8025F7A8-0x8025F7D8 size=0x30 (48B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u8 *lbl_803CAB78;
void *OSGetArenaLo(void);
void OSSetArenaLo(void *);
void fn_8025F988(void);

void fn_8025F7A8(void) {
    u8 *t = (u8 *)OSGetArenaLo();

    lbl_803CAB78 = t;
    OSSetArenaLo(t + 0x1000);
    fn_8025F988();
}
