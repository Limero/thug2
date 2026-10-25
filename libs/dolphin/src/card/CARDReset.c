#include <dolphin/card.h>
#include <dolphin/exi.h>

#include "__card.h"

/* thug2 places these three functions at 0x8027B610..0x8027B6F8, separate from
 * the rest of CARDBios.c (0x8027A3BC..0x8027B588) because a CARDStat function
 * is interleaved in between. Splitting them out (instead of two .text ranges
 * on one object) avoids a cyclic link-order dependency in dtk. CARDGetResultCode
 * stays here so it is inlined into __CARDSync and dead-stripped, exactly as in
 * the retail build (docs/dolphin-sdk.md §9.3). OnReset is non-static here so
 * CARDBios.c's ResetFunctionInfo can take its address. */

s32 CARDGetResultCode(s32 chan) {
    CARDControl* card;

    ASSERTLINE(1292, 0 <= chan && chan < 2);

    if (chan < 0 || chan >= 2) {
        return CARD_RESULT_FATAL_ERROR;
    }
    card = &__CARDBlock[chan];
    return card->result;
}

s32 __CARDSync(s32 chan) {
    CARDControl* block;
    s32 result;
    s32 enabled;

    block = &__CARDBlock[chan];
    enabled = OSDisableInterrupts();
    while ((result = CARDGetResultCode(chan)) == CARD_RESULT_BUSY) {
        OSSleepThread(&block->threadQueue);
    }

    OSRestoreInterrupts(enabled);
    return result;
}

BOOL OnReset(BOOL final) {
    if (!final) {
        if (CARDUnmount(0) == CARD_RESULT_BUSY || CARDUnmount(1) == CARD_RESULT_BUSY) {
            return FALSE;
        }
    }

    return TRUE;
}
