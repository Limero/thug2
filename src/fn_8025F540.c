// Promoted from src/wip 2026-10-09 (mwcc region). family=hand range=0x8025F540-0x8025F5CC size=140B
// range 0x8025F540-0x8025F5CC size=0x8C (140B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *fn_8025FB84(u32 arg0);
extern void fn_8025F6D4(u32 arg0);
extern void fn_8025F720(s32 arg0, u32 arg1);
extern void fn_8025F73C(s32 arg0, s32 arg1);
extern s32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(s32 level);
extern void DCStoreRange(void *addr, u32 len);

void fn_8025F540(u32 arg0, u32 arg1) {
    u32 *e;
    s32 level;

    level = OSDisableInterrupts();
    e = fn_8025FB84(arg0);
    e[0] = 0;
    e[1] = 0;
    DCStoreRange(e, 8);
    fn_8025F6D4(arg0);
    fn_8025F720((s32)arg1, 0);
    fn_8025F73C((s32)arg1, 0);
    OSRestoreInterrupts(level);
}
