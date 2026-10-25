// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E7A0-0x8009E82C (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_8009E574(Unk_C7387A53 *, s32);
void fn_80127CD4(CStruct *, s32, s32);
bool fn_8009E7A0(Unk_C7387A53 *arg0, CStruct *arg1, CScript *arg2) {
    s32 sp8;
    s32 temp_r3;

    if (GetChecksum_2(arg1, QB_STRUCTURE, &sp8, 0) != 0) {
        temp_r3 = CStruct_ctor(CStruct_new(8));
        fn_8009E574(arg0, temp_r3);
        fn_80127CD4(arg2->unk0x18, sp8, temp_r3);
    } else {
        fn_8009E574(arg0, arg2->unk0x18);
    }
    return true;
}
