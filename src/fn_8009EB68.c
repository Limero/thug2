// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009EB68-0x8009EC68 (256B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8012EF68(Unk_FFAD6788 *, Unk_15EF4A35 *);
s32 fn_8009F27C(CStruct *, Unk_15EF4A35 *, s32, s32, s32);
s32 ContainsFlag(CStruct *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_801319F8(Unk_FFAD6788 *);
s32 fn_80127358(CStruct *, Unk_C7387A53 *);
bool fn_8009EB68(CStruct *arg0, CStruct *arg1, Unk_FFAD6788 *arg2) {
    s32 spC;
    s32 sp8;
    s32 temp_r28;
    s32 temp_r30;
    CStruct *temp_r3;

    temp_r3 = fn_80127358(arg1, 0);
    if ((temp_r3 != NULL) && ((s32) (temp_r3->unk0x0 & 0x7F0000) == 0xD0000)) {
        temp_r28 = temp_r3->unk0x8;
        sp8 = 0;
        sp8 = fn_801319F8(arg2);
        GetChecksum_2(arg1, QB_ID, &sp8, 0);
        spC = 0;
        GetStructure_2(arg1, QB_PARAMS, &spC, 0);
        temp_r30 = fn_8009F27C(arg0, temp_r28, spC, sp8, ContainsFlag(arg1, QB_PAUSEWITHOBJECT));
        if (ContainsFlag(arg1, QB_NOQBID) == 0) {
            fn_8012EF68(temp_r30, arg2);
        }
    }
    return true;
}
