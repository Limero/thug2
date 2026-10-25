// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FB248-0x801FB2A8 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801FC2F4(s32 arg0);
void *fn_801F9540(CStruct * arg0);
void *fn_801FB248(Unk_C7387A53 *arg0) {
    CStruct *temp_r3;
    Unk_9994C3F5 *temp_r11;

    temp_r3 = fn_801F9540(fn_801FC2F4(0x14));
    temp_r11 = arg0->unk0x24;
    temp_r3->unk0x8 = 0;
    temp_r3->unk0x4 = temp_r11;
    if (temp_r11 != NULL) {
        temp_r11->unk0x8 = temp_r3;
    }
    arg0->unk0x24 = temp_r3;
    arg0->unk0x28 = temp_r3;
    return temp_r3;
}
