// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009C00-0x80009C84 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000A014(Unk_C7387A53 *);
void fn_80009C00(CStruct *arg0) {
    s32 temp_r9;
    CStruct *temp_r11;
    CStruct *temp_r11_2;
    CStruct *temp_r9_2;

    temp_r11 = arg0->unk0xC;
    if (temp_r11 != NULL) {
        temp_r9 = temp_r11->unk0x4 + 1;
        temp_r11->unk0x4 = temp_r9;
        fn_8000A014(arg0->unk0xC);
        temp_r9_2 = arg0->unk0x8;
        *(s32 *)(*(s32 *)((char *)((char *)temp_r9_2) + 0x10) + 0xC) =  temp_r9_2->unk0xC;
        *(s32 *)(*(s32 *)((char *)((char *)temp_r9_2) + 0xC) + 0x10) =  temp_r9_2->unk0x10;
        temp_r9_2->unk0xC = temp_r9_2;
        temp_r9_2->unk0x10 = temp_r9_2;
        temp_r11_2 = arg0->unk0xC;
        temp_r11_2->unk0x4 = (s32) (temp_r11_2->unk0x4 - 1);
        arg0->unk0xC = NULL;
    }
}
