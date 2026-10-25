// Promoted from src/wip 2026-10-09 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09. family=hand range=0x8025F340-0x8025F400 size=160B
// range 0x8025F340-0x8025F3E0 size=0xA0 (160B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *lbl_803CAB60;
void *OSGetArenaLo(void);
void OSSetArenaLo(void *addr);

void fn_8025F340(void) {
    u32 *lo;
    u32 i;

    lo = OSGetArenaLo();
    lbl_803CAB60 = lo;
    OSSetArenaLo((char *)lo + 0x4000);

    for (i = 0; i < 0x4000; i += 4) {
        *(u32 *)((u8 *)lbl_803CAB60 + i) = 0;
    }
}
