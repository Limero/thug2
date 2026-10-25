// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80205278-0x802052C4 (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetStructure(s32, s32);
void GetFloat(CStruct *, s32, f32 *, s32);
f32 fn_80205278(s32 arg0, s32 arg1) {
    f32 sp8;

    GetFloat(GetStructure(QB_PLAYERVEHICLESOUNDGLOBALPARAMETERS, 1), arg1, &sp8, 1);
    return sp8;
}
