// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E1F0-0x8009E274 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80297F18;
void SetChecksumTag(void *, s32, s32);
void fn_8009E1F0(Unk_C8FEE62D *arg0, s32 arg1) {
    void *temp_r11;
    Unk_C7387A53 *temp_r9;

    if ((s32) arg0->unk0x18 != lbl_80297F18) {
        temp_r11 = (void *)arg0->unk0x10;
        if (temp_r11 != NULL) {
            temp_r9 = (Unk_C7387A53 *)((Unk_C7387A53 *)temp_r11)->unk0x2C;
            ((void (*)(void *, void *, void *))temp_r9->unk0x24)((char *)temp_r11 + *(s16 *)((char *)temp_r9 + 0x20), arg0, (void *)arg1);
        }
    }
    arg0->unk0x18 = arg1;
    SetChecksumTag(arg0, QB_ID, arg1);
}