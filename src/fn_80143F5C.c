// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80143F5C-0x801440DC (384B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
bool fn_80143F5C(Unk_7B36180C *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 var_r9;

    if ((ContainsFlag(arg1, QB_IS_PRO) != 0) && (arg0->unk0x124 == 0)) {
        return false;
    }
    if ((ContainsFlag(arg1, QB_IS_CUSTOM) != 0) && (arg0->unk0x124 != 0)) {
        return false;
    }
    if ((ContainsFlag(arg1, QB_IS_MALE) != 0) && (arg0->unk0x128 == 0)) {
        return false;
    }
    if ((ContainsFlag(arg1, QB_IS_FEMALE) != 0) && (arg0->unk0x128 != 0)) {
        return false;
    }
    if ((GetChecksum_2(arg1, QB_IS_NAMED, &sp8, 0) != 0) && (sp8 != arg0->unk0x16C)) {
        return false;
    }
    if (GetChecksum_2(arg1, QB_STANCE, &spC, 0) != 0) {
        var_r9 = QB_REGULAR;
        if (arg0->unk0x120 != 0) {
            var_r9 = QB_GOOFY;
        }
        if (spC != var_r9) {
            return false;
        }
    }
    if (GetChecksum_2(arg1, QB_STYLE, &sp10, 0) != 0) {
        if (sp10 != arg0->unk0x11C) {
            return false;
        }
    }
    return true;
}
