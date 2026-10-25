// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80140010-0x80140068 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_80128C80(CStruct *, void *, void *, s32);
s32 fn_80140010(s32 arg0, s32 arg1, void *arg2) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    GetStructure_2(arg0 + 4, arg1, &sp8, 0);
    fn_80128C80(sp8, arg2, &spC, 1);
    return spC;
}
