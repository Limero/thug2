// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006374C-0x800637C0 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8006374C(Unk_7517F73F *arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r9;

    if ((((s32) arg0->unk0x158 != 0) && ((s32) arg0->unk0x15C != 0)) || (arg1 != 0)) {
        temp_r9 = arg0->unk0x8;
        ((s32 (*)(void *))temp_r9->unk0x14)((char *)arg0 + *(s16 *)&temp_r9->unk0x10);
        arg0->unk0x158 = 0;
        arg0->unk0x128 = (s32) (arg0->unk0x128 & QB_UNKNOWN_0xFFFFFFFE);
    }
}