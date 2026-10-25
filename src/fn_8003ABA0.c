// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003ABA0-0x8003ABD8 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_8003ABA0(s32 arg0, s32 arg1) {
    s32 sp8;
    sp8 = 0;
    GetStructure_2(arg0 + 0x58, arg1, &sp8, 0);
    return sp8;
}
