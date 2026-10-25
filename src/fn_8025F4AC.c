// Promoted from src/wip 2026-10-09 (mwcc region). family=hand range=0x8025F4AC-0x8025F540 size=148B
// range 0x8025F4AC-0x8025F540 size=0x94 (148B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *fn_8025FB84(u32 arg0);
extern void fn_8025F6D4(u32 arg0);
extern void fn_8025F720(s32 arg0, u32 arg1);
extern s32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(s32 level);
extern void DCStoreRange(void *addr, u32 len);

void fn_8025F4AC(u32 addr, u32 bits, u32 idx) {
    u32 *e;
    s32 level;

    e = fn_8025FB84(addr);
    level = OSDisableInterrupts();
    e[0] = 0x80000000 | ((addr >> 22) & 0x3F);
    e[1] = bits & 0x0FFFF000;
    DCStoreRange(e, 8);
    fn_8025F6D4(addr);
    fn_8025F720((s32)idx, addr);
    OSRestoreInterrupts(level);
}
