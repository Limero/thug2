// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000E774-0x8000E7BC (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000E774(CStruct *, void *, s32);
s32 fn_8000A778(s32);
void fn_8000E6D4(CStruct *, s32 *, s32);
void fn_8000E774(CStruct *arg0, void *arg1, s32 arg2) {
    s32 sp8;

    sp8 = fn_8000A778(arg1);
    fn_8000E6D4(arg0, &sp8, arg2);
}
