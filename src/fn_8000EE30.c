// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000EE30-0x8000EE70 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000EE30(CStruct *, void *);
s32 fn_8000A778(s32);
void fn_8000ED78(CStruct *, s32 *);
void fn_8000EE30(CStruct *arg0, void *arg1) {
    s32 sp8;

    sp8 = fn_8000A778(arg1);
    fn_8000ED78(arg0, &sp8);
}
