// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FB1C4-0x801FB248 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801F9594(Unk_C7387A53 * arg0, s32 arg1);

void fn_801FB1C4(Unk_C7387A53 *arg0, CStruct *arg1) {
    Unk_9994C3F5 *temp_r9;
    CStruct *temp_r9_2;

    if (arg0->unk0x24 == arg1) {
        arg0->unk0x24 = arg1->unk0x4;
    }
    if (arg0->unk0x28 == arg1) {
        arg0->unk0x28 = arg1->unk0x4;
    }
    temp_r9 = arg1->unk0x4;
    if (temp_r9 != NULL) {
        temp_r9->unk0x8 = arg1->unk0x8;
    }
    temp_r9_2 = arg1->unk0x8;
    if (temp_r9_2 != NULL) {
        temp_r9_2->unk0x4 = arg1->unk0x4;
    }
    if (arg1 != NULL) {
        fn_801F9594(arg1, 3);
    }
}
