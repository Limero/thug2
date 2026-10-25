// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137364-0x801373EC (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80137424(CStruct *, void *);
void fn_8013742C(Unk_9994C3F5 *, void *);
void fn_80137364(Unk_1624B368 *arg0, s32 arg1, s32 arg2) {
    s32 temp_r9;
    s32 var_r30;
    void *temp_r30;

    temp_r9 = arg0->unk0xC04;
    var_r30 = temp_r9;
    if (temp_r9 < 0) {
        var_r30 = temp_r9 + 0xFF;
    }
    temp_r30 = (char *)arg0 + (((temp_r9 - (var_r30 & QB_UNKNOWN_0xFFFFFF00)) * 0xC) + 4);
    fn_80137424(temp_r30, arg1);
    fn_8013742C(temp_r30, arg2);
    arg0->unk0x1408 = (s32) (arg0->unk0x1408 + arg1);
    arg0->unk0xC04 = (s32) (arg0->unk0xC04 + 1);
}
