// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013E2EC-0x8013E364 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029F530[];
void *Mem_NewZero(s32 size);
void fn_8013E2EC(s32 arg0, Unk_C7387A53 *arg1) {
    CStruct *temp_r30;
    Unk_C8FEE62D *temp_r3;
    s32 temp_r11;

    temp_r3 = Mem_NewZero(0x1C);
    temp_r3->unk0xC = (s32)temp_r3;
    temp_r3->unk0x10 = (s32)temp_r3;
    temp_r30 = (void *)(arg0 + 0x2294);
    temp_r3->unk0x8 = 0;
    temp_r3->unk0x14 = (s32)lbl_8029F530;
    temp_r3->unk0x4 = (s32)temp_r3;
    temp_r3->unk0x18 = arg1->unk0x4C;
    temp_r11 = temp_r30->unk0x10;
    temp_r3->unk0xC = (s32)temp_r30;
    temp_r3->unk0x10 = temp_r11;
    *(s32 *)(temp_r30->unk0x10 + (s32)0xC) = (s32)temp_r3;
    temp_r30->unk0x10 = (s32)temp_r3;
}
