// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D4B04-0x800D4B64 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
bool fn_800D4B04(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 var_r9;

    sp8 = 0;
    GetInteger(arg1, 0, &sp8, 0);
    var_r9 = 1;
    if (sp8 == 0) {
        var_r9 = 0;
    }
    arg0->unk0x48 = var_r9;
    return true;
}
