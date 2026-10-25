// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80172910-0x801729B0 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800121D8(s32 idx);
extern s32 fn_80172710(s32 entry);
bool fn_80172910(CStruct *arg0, s32 *arg1, s32 arg2) {
    s32 temp_r10;
    s32 temp_r11;
    s32 temp_r9;
    CStruct *temp_r31;
    CStruct *temp_r3;

    temp_r11 = *arg1;
    temp_r10 = arg0->unk0x4;
    temp_r9 = (temp_r11 & ((1 << arg0->unk0x0) - 1)) * 0xC;
    temp_r31 = temp_r10 + temp_r9;
    if ((s32) temp_r31->unk0x4 != 0) {
        temp_r3 = fn_80172710(fn_800121D8(0));
        temp_r3->unk0x0 = (s32) *arg1;
        temp_r3->unk0x4 = arg2;
        temp_r3->unk0x8 = (s32)temp_r31->unk0x8;
        temp_r31->unk0x8 = temp_r3;
    } else {
        *(s32 *)((char *)temp_r10 + temp_r9) = temp_r11;
        temp_r31->unk0x4 = arg2;
    }
    arg0->unk0x8 = (s32) (arg0->unk0x8 + 1);
    return true;
}
