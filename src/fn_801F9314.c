// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9314-0x801F93B0 (156B). Byte-identical.
#include "types.h"
#include "structs.h"

void fn_801F9314(Unk_C7387A53 *arg0, s32 *arg1) {
    s32 sp8;
    CStruct *temp_r3;
    Unk_C8FEE62D *temp_r11;
    Unk_C6B642AC *temp_r9;
    s32 temp_r30;

    temp_r30 = *arg1;
    temp_r3 = *((void * *)&arg0->unk0x30);
    if (temp_r3 != NULL) {
        temp_r11 = *((void * *)&temp_r3->unk0x10);
        if (temp_r11 != NULL) {
            sp8 = temp_r30;
            temp_r9 = *((void * *)&temp_r11->unk0x14);
            ((void (*)(void *, void *))*((void * *)&temp_r9->unk0x3C))(
                (char *)temp_r11 + temp_r9->unk0x38, &sp8);
        }
    }
    temp_r3 = *((void * *)&arg0->unk0x2C);
    if (temp_r3 != NULL) {
        temp_r11 = *((void * *)&temp_r3->unk0x10);
        if (temp_r11 != NULL) {
            sp8 = temp_r30;
            temp_r9 = *((void * *)&temp_r11->unk0x14);
            ((void (*)(void *, void *))*((void * *)&temp_r9->unk0x3C))(
                (char *)temp_r11 + temp_r9->unk0x38, &sp8);
        }
    }
}
