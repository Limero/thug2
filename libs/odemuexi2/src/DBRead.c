// Dolphin db-module (OdemuExi2) - DBRead
// mwcc GC/1.2.5n, cflags_odemuexi2. g6-verified EXACT 2026-08-26; wired as
// lib objects (the ngccc game route cannot emit the SDK prologue order).
#include "dolphin/types.h"
extern u32 lbl_803CAF28;
extern s32 lbl_803CAF2C;
extern u8 lbl_803CAF34;
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32 level);
s32 DBGRead(s32 addr, void *buf, s32 len);
s32 DBRead(void *arg0, s32 arg1) {
    s32 en;
    s32 v;
    en = OSDisableInterrupts();
    if (*(volatile u32 *)&lbl_803CAF28 & 0x10000) {
        v = 0x1000;
    } else {
        v = 0;
    }
    DBGRead(v + 0x1E000, arg0, (arg1 + 3) & ~3);
    lbl_803CAF2C = 0;
    lbl_803CAF34 = 0;
    OSRestoreInterrupts(en);
    return 0;
}
