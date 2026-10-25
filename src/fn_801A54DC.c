// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A54DC-0x801A5610 (308B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305EAC;
s32 fn_801A56BC(s32 arg0);
s32 fn_80128E94(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
s32 fn_801A7EC0(CStruct * arg0);
s32 fn_80129528(CStruct * arg0, s32 arg1);
s32 fn_80127E70(s32 arg0, u32 arg1, s32 arg2, u32 arg3);
s32 AddInteger(CStruct * arg0, u32 arg1, s32 arg2);
s32 fn_801270B4(CStruct * arg0, u32 arg1);
s32 fn_801745B4(s32 arg0);
s32 GetChecksum_3(Unk_6A70655D * arg0, u32 arg1);
void fn_80206EA4(Unk_59E38960 * arg0, void * arg1);

bool fn_801A54DC(void *arg0, s32 arg1, CStruct *arg2, s32 arg3) {
    void *sp8;
    s32 temp_r29;
    s32 temp_r3;
    s32 var_r30;
    s32 var_r31;

    fn_80128E94(fn_801A56BC(arg0), 0, &sp8, 1);
    if (arg1 >= 0 && arg1 < ((CStruct *)sp8)->unk0x4) {
        goto ok;
    }
    return false;
ok:
    {
        var_r31 = arg2->unk0x4;
        var_r30 = arg2->unk0x8;
        if (fn_801A7EC0(arg2) != 0) {
            var_r31 = QB_UNASSIGNED;
            var_r30 = QB_UNASSIGNED;
        }
        temp_r29 = fn_80129528(sp8, arg1);
        fn_80127E70(temp_r29, QB_TRICKNAME, 13, var_r31);
        fn_80127E70(temp_r29, QB_TRICKSLOT, 13, var_r30);
        if (arg2->unk0xC != 0) {
            AddInteger(temp_r29, QB_ISCAT, 1);
        } else {
            fn_801270B4(temp_r29, QB_ISCAT);
        }
        if (arg3 != 0) {
            temp_r3 = fn_801745B4(lbl_80305EAC);
            if (temp_r3 != 0) {
                fn_80206EA4(GetChecksum_3(temp_r3, QB_TRICK), arg0);
            }
        }
        return true;
    }
}
