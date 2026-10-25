// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019EAD0-0x8019EB40 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301B48;
s32 fn_80125A3C(void *, s32);
s32 Script_GenerateCRC(s32);
s32 fn_800F2A48(s32, s32, s32);
void fn_800F28E4(Unk_C7387A53 *, CStruct *);
void fn_8019EAD0(s32 arg0) {
    s32 temp_r31;
    s32 ret;

    if (fn_80125A3C(QB_CAS_ARTIST, 0) != 0) {
        temp_r31 = lbl_80301B48;
        ret = fn_800F2A48(temp_r31, Script_GenerateCRC(arg0), 0);
        if (ret != 0) {
            fn_800F28E4(temp_r31, ret);
        }
    }
}

