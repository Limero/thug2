// Dolphin db-module (OdemuExi2) - DBInitComm
// mwcc GC/1.2.5n, cflags_odemuexi2. g6-verified EXACT 2026-08-26; wired as
// lib objects (the ngccc game route cannot emit the SDK prologue order).
#include "dolphin/types.h"
typedef void (*cb_t)(s32);
extern u8 lbl_803CAF34;
extern void *lbl_803CAF30;
extern cb_t lbl_803CAF20;
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32 level);
void __OSMaskInterrupts(u32 mask);
extern char lbl_CC006828[];
void DBInitComm(void *arg0, void *arg1) {
    s32 en = OSDisableInterrupts();
    lbl_803CAF30 = &lbl_803CAF34;
    *(void **)arg0 = lbl_803CAF30;
    lbl_803CAF20 = (cb_t)arg1;
    __OSMaskInterrupts(0x18000);
    *(volatile u32 *)&lbl_CC006828 = 0;
    OSRestoreInterrupts(en);
}
