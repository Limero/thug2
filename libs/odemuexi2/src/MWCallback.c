// Dolphin db-module (OdemuExi2) - MWCallback
// mwcc GC/1.2.5n, cflags_odemuexi2. g6-verified EXACT 2026-08-26; wired as
// lib objects (the ngccc game route cannot emit the SDK prologue order).
#include "dolphin/types.h"
typedef void (*cb_t)(s32);
extern cb_t lbl_803CAF20;
extern u8 lbl_803CAF34;
void MWCallback(void) {
    lbl_803CAF34 = 1;
    if (lbl_803CAF20 != NULL) lbl_803CAF20(0);
}
