// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010AC0-0x80010B1C (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *fn_80010AC0(void) {
    void *temp_r30;
    CStruct *temp_r3;
    Unk_EFE13F4E *temp_r9;

    temp_r3 = fn_80010B38();
    temp_r30 = temp_r3->unk0x0;
    temp_r9 = ((Unk_C7387A53 *)temp_r30)->unk0x80;
    ((s32 (*)(void *, void *))temp_r9->unk0x4C)(temp_r30 + temp_r9->unk0x48, temp_r3);
    temp_r3->unk0x4 = QB_MAGIC_DEADDEAD;
    return temp_r30;
}
