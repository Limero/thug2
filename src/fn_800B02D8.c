// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B02D8-0x800B0374 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Script_GetInteger(s32, s32);
void fn_800B02D8(Unk_C8FEE62D *arg0) {
    Unk_2C7D9FAD *temp_r9;
    Unk_2C7D9FAD *temp_r9_2;

    if ((s32) arg0->unk0x70 != 0) {
        if ((s32) arg0->unk0x74 == -1) {
            temp_r9 = arg0->unk0x14;
            ((s32 (*)(void *, s32))temp_r9->unk0x6C)((char *)arg0 + temp_r9->unk0x68, 0);
        }
    } else if ((s32) arg0->unk0x74 == -1) {
        temp_r9_2 = arg0->unk0x14;
        ((s32 (*)(void *, s32))temp_r9_2->unk0x6C)((char *)arg0 + temp_r9_2->unk0x68, 1);
        arg0->unk0x74 = Script_GetInteger(QB_CUTSCENE_FRAME_ADVANCE_DELAY, 1);
    }
}
