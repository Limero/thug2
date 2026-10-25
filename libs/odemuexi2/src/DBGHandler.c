// Dolphin db-module (OdemuExi2) - DBGHandler
// mwcc GC/1.2.5n, cflags_odemuexi2.
// PI interrupt handler: acks the DSP CPU mailbox poke, then dispatches the
// registered callback.
#include "dolphin/types.h"
#include "dolphin/hw_regs.h"
typedef void (*cb_t)(s32, void*);
extern cb_t lbl_803CAF24;

void DBGHandler(s16 interrupt, void* context) {
    *__PIRegs = 0x1000;
    if (lbl_803CAF24 != NULL) {
        lbl_803CAF24(interrupt, context);
    }
}