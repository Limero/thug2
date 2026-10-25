// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F153C-0x801F1594 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_80128E34(CStruct *, void *, void *, s32);
extern s32 fn_801F128C(s32, s32);

bool fn_801F153C(s32 arg0, CStruct *arg1) {
    s32 sp8;

    fn_80128E34(arg1, 0, &sp8, 1);
    if (fn_801F128C(arg0, sp8) == 0) {
        return false;
    } else {
        return true;
    }
}
