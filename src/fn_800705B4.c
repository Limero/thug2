// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800705B4-0x800705F4 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
bool fn_800705B4(Unk_31DE137E *arg0, CStruct *arg1) {
    arg0->unk0x1C = 8;
    GetInteger(arg1, 0, (char *)arg0 + 0x1C, 0);
    return true;
}
