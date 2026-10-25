// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013FFB8-0x80140010 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetText(CStruct *, void *, void *, s32);
s32 fn_8013FFB8(s32 arg0, s32 arg1, void *arg2) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    GetStructure_2(arg0 + 4, arg1, &sp8, 0);
    GetText(sp8, arg2, &spC, 1);
    return spC;
}
