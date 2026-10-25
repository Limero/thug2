// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134D7C-0x80134E1C (160B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800121D8(s32 arg0);
extern s32 fn_80134984(s32 arg0);

bool fn_80134D7C(CStruct *arg0, s32 *arg1, s32 arg2) {
    s32 temp_r10;
    s32 temp_r9;
    CStruct *temp_r31;
    CStruct *temp_r3;
    s32 var_v = arg2;

    temp_r9 = ((*arg1 & ((1 << arg0->unk0x0) - 1)) * 12);
    temp_r10 = arg0->unk0x4;
    temp_r31 = (char *)temp_r10 + temp_r9;
    if (temp_r31->unk0x4 != 0) {
        temp_r3 = fn_80134984(fn_800121D8(0));
        temp_r3->unk0x0 = *arg1;
        temp_r3->unk0x4 = var_v;
        temp_r3->unk0x8 = temp_r31->unk0x8;
        temp_r31->unk0x8 = temp_r3;
    } else {
        *(s32 *)((char *)temp_r10 + temp_r9) = *arg1;
        temp_r31->unk0x4 = var_v;
    }
    arg0->unk0x8 = (arg0->unk0x8 + 1);
    return true;
}
