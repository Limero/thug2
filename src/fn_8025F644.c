// Promoted from src/wip 2026-10-09 (mwcc region). family=hand range=0x8025F644-0x8025F6D4 size=144B
// range 0x8025F644-0x8025F6D4 size=0x90 (144B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *fn_8025FB84(u32 arg0);
extern void fn_8025F6D4(u32 arg0);
extern s32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(s32 level);
extern void DCStoreRange(void *addr, u32 len);

void fn_8025F644(u32 addr, s32 flag) {
    u32 *e;
    s32 level;

    level = OSDisableInterrupts();
    e = fn_8025FB84(addr);
    if (flag != 0) {
        e[1] |= 0x100;
    } else {
        e[1] &= ~0x100;
    }
    DCStoreRange(e + 1, 4);
    fn_8025F6D4(addr);
    OSRestoreInterrupts(level);
}
