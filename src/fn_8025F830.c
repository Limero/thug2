// Promoted from src/wip 2026-10-09 (mwcc region). family=hand range=0x8025F830-0x8025F988 size=344B
// range 0x8025F830-0x8025F988 size=0x158 (344B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u8 *lbl_803CAB70;
extern void fn_8025FBB8(void);
extern s32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(s32 level);
extern void DCStoreRange(void *addr, u32 len);

void fn_8025F830(void) {
    s32 level;
    u32 i;

    level = OSDisableInterrupts();
    for (i = 0; i < 0x10000; i += 8) {
        *(u32 *)((u8 *)lbl_803CAB70 + i) = 0;
        *(u32 *)((u8 *)lbl_803CAB70 + i + 4) = 0;
    }
    DCStoreRange(lbl_803CAB70, 0x10000);
    fn_8025FBB8();
    OSRestoreInterrupts(level);
}
