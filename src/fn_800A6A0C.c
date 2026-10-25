// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A6A0C-0x800A6AAC (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800121D8(s32);
CStruct *fn_800A69DC(s32);
bool fn_800A6A0C(CStruct *arg0, s32 *arg1, s32 arg2) {
    s32 temp_r11;
    s32 key;
    CStruct *temp_r31;
    CStruct *temp_r3;
    temp_r11 = *arg1;
    temp_r31 = (CStruct *)(arg0->unk0x4 + ((temp_r11 & ((1 << arg0->unk0x0) - 1)) * 0xC));
    if ((s32) temp_r31->unk0x4 != 0) {
        temp_r3 = fn_800A69DC(fn_800121D8(0));
        key = *arg1;
        temp_r3->unk0x4 = arg2;
        temp_r3->unk0x0 = key;
        temp_r3->unk0x8 =  temp_r31->unk0x8;
        temp_r31->unk0x8 = (s32) temp_r3;
    } else {
        *(s32 *)((char *)arg0->unk0x4 + ((temp_r11 & ((1 << arg0->unk0x0) - 1)) * 0xC)) = temp_r11;
        temp_r31->unk0x4 = arg2;
    }
    arg0->unk0x8 = (s32) (arg0->unk0x8 + 1);
    return true;
}