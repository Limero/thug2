// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801568B8-0x801568F4 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801568B8(CStruct *arg0) {
    s32 sp8;

    if (GetInteger(arg0, 0, &sp8, 0) == 0) {
        return 0;
    }
    return sp8;
}
