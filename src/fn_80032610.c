// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80032610-0x80032698 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80032610(Unk_C7387A53 *arg0) {
    s32 i;
    void *temp_r11;
    Unk_F5317C5D *temp_r9;
    for (i = 0; i < (s32) arg0->unk0x58; i++) {
        s32 *arr = (s32 *)((char *)arg0 + (s32)0x40);
        temp_r11 = (void *)arr[i];
        if (temp_r11 != NULL) {
            temp_r9 = ((Unk_C8FEE62D *)temp_r11)->unk0x14;
            ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
        }
        arr[i] = 0;
    }
    arg0->unk0x58 = 0;
}
