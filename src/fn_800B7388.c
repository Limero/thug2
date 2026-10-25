// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B7388-0x800B7430 (168B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80303150;
extern s32 fn_8009F498(void *arg0);
void fn_800B7388(Unk_DB0E2BAB *arg0) {
    s32 temp_r11;
    s32 temp_r30;
    u32 temp_r9;
    void *temp_r3;
    void *temp_r3_2;
    Unk_C6B642AC *temp_r9_2;
    Unk_C6B642AC *temp_r9_3;

    temp_r30 = arg0->unk0x1C;
    temp_r9 = (lbl_80303150 + Tmr_GetTime()) - temp_r30;
    arg0->unk0x20 = temp_r9;
    temp_r11 = arg0->unk0x28;
    if (temp_r11 != 0) {
        if (fn_8009F498(temp_r11) == 0) {
            temp_r3 = arg0->unk0xC;
            temp_r9_2 = ((Unk_9994C3F5 *)temp_r3)->unk0x8;
            ((s32 (*)(void *))temp_r9_2->unk0x3C)(temp_r3 + temp_r9_2->unk0x38);
        }
    } else if (temp_r9 > (u32)*((u32 *)&arg0->unk0x24)) {
        temp_r3_2 = arg0->unk0xC;
        temp_r9_3 = ((Unk_9994C3F5 *)temp_r3_2)->unk0x8;
        ((s32 (*)(void *))temp_r9_3->unk0x3C)(temp_r3_2 + temp_r9_3->unk0x38);
    }
}
