// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5848-0x801A5880 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetText(CStruct *, void *, void *, s32);
s32 fn_801A5848(s32 arg0) {
    s32 sp8;

    GetText(arg0 + 0x6C, QB_DISPLAY_NAME, &sp8, 1);
    return sp8;
}
