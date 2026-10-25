// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F67D0-0x801F6838 (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801F5898(s32);
s32 GetInteger(s32, s32, s32, s32);
s32 fn_801F340C(s32, s32);
bool fn_801F67D0(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 temp_r3;

    temp_r3 = fn_801F5898(arg0);
    if (temp_r3 != 0) {
        sp8 = 0;
        GetInteger(arg1, QB_GAP_NUMBER, &sp8, 0);
        fn_801F340C(temp_r3, ((Unk_E01B0030 *)&sp8)->unk0x3);
    }
    return true;
}
