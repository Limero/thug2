// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80219F9C-0x80219FE0 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8021E024(void);
s32 fn_8013FF5C(s32, s32);
s32 GetText(CStruct *, void *, void *, s32);
s32 fn_80219F9C(void * arg0) {
    s32 sp8;

    GetText(fn_8013FF5C(fn_8021E024(), QB_PASSWORD), QB_UI_STRING, &sp8, 1);
    return sp8;
}
