// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801789BC-0x801789F8 (60B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 lbl_80305F9C;
extern s32 fn_8021D2C4(s32 arg0, s32 arg1);
extern void fn_80229918(CScript * arg0);

bool fn_801789BC(CStruct *arg0) {
    s32 temp_r3;

    temp_r3 = fn_8021D2C4(lbl_80305F9C, arg0->unk0x10);
    if (temp_r3 != 0) {
        fn_80229918(temp_r3);
    }
    return true;
}
