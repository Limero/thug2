// Dolphin db-module (OdemuExi2) - DBInitInterrupts
// mwcc GC/1.2.5n, cflags_odemuexi2. g6-verified EXACT 2026-08-26; wired as
// lib objects (the ngccc game route cannot emit the SDK prologue order).
#include "dolphin/types.h"
typedef void (*int_handler)(s32, void *);
void __OSMaskInterrupts(u32 mask);
void __OSUnmaskInterrupts(u32 mask);
void __OSSetInterruptHandler(u32 interrupt, int_handler handler);
void MWCallback(s32, void *);
void DBGHandler(s32 msg, void *ctx);
extern void (*lbl_803CAF24)(s32, void *);
void DBInitInterrupts(void) {
    __OSMaskInterrupts(0x18000);
    __OSMaskInterrupts(0x40);
    lbl_803CAF24 = MWCallback;
    __OSSetInterruptHandler(0x19, DBGHandler);
    __OSUnmaskInterrupts(0x40);
}
