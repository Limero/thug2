// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F6838-0x801F68AC (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_801F5898(s32 arg0, s32 arg1);
extern s32 GetInteger(s32 arg0, s32 arg1, void *arg2, s32 arg3);
extern s32 fn_801F34F4(s32 arg0, s32 arg1);

s32 fn_801F6838(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 mgr;
    s32 var_r3;

    mgr = fn_801F5898(arg0, arg1);
    if (mgr != 0) {
        sp8 = 0;
        GetInteger(arg1, QB_GAP_NUMBER, &sp8, 0);
        var_r3 = fn_801F34F4(mgr, ((Unk_E01B0030 *)&sp8)->unk0x3) != 0;
    } else {
        var_r3 = 0;
    }
    return var_r3;
}
