// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5240-0x801A5278 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void AddInteger(CStruct *, s32, s32);
bool fn_801A5240(s32 arg0, s32 arg1, u32 arg2) {
    if (arg2 <= 0xAu) {
        AddInteger(arg0 + 0x6C, arg1, arg2);
        return true;
    }
    return false;
}
