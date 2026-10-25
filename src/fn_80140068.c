// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80140068-0x801400C0 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80128E04(CStruct *, void *, void *, s32);
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_80140068(s32 arg0, void *arg1, void *arg2) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    fn_80128E04(arg0 + 4, arg1, &sp8, 1);
    fn_80128E34(sp8, arg2, &spC, 1);
    return spC;
}
