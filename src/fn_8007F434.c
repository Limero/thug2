// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F434-0x8007F494 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8007F434(Unk_C7387A53 *arg0, s32 arg1) {
    s32 var_r10;
    s32 var_r8;
    CStruct *temp_r9;
    CStruct *temp_r11;

    arg1 = arg1 & 0xFF;
    temp_r9 = (CStruct *)arg0->unk0x30;
    arg0->unk0x28 = (s32)arg1;
    if (temp_r9 != NULL) {
        temp_r9->unk0x58 = (s32)arg1;
        return;
    }
    if ((s32)arg0->unk0x20 != 0) {
        var_r10 = 0;
        if ((u32)var_r10 >= (u32)arg0->unk0x24) {
            return;
        }
        var_r8 = 0;
        do {
            temp_r11 = *(CStruct **)(char *)(var_r8 + (s32)arg0->unk0x20);
            var_r10 += 1;
            var_r8 += 4;
            temp_r11->unk0x8 = (s32)arg1;
        } while ((u32)var_r10 < (u32)arg0->unk0x24);
    }
}
