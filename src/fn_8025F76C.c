// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F76C-0x8025F7A8 size=60B
// range 0x8025F76C-0x8025F7A8 size=0x3C (60B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 lbl_803CAB70;
void *OSGetArenaLo(void);
void OSSetArenaLo(void *);
void fn_8025F830(void);

void fn_8025F76C(void) {
    u32 lo = (u32)OSGetArenaLo();
    u32 low = lo & 0xFFFF;
    u32 base = (lo + 0x10000) - low;

    lbl_803CAB70 = base;
    OSSetArenaLo((void *)(base + 0x10000));
    fn_8025F830();
}
