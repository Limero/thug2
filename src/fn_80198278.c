// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80198278-0x801982D4 (92B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 fn_801289A8(void *, void *);
s32 Script_GenerateCRC(s32);
s32 fn_801270B4(CStruct *, s32);

bool fn_80198278(s32 arg0, void *arg1, void *arg2) {
    if (fn_801289A8(arg2, arg1) != 0) {
        fn_801270B4(arg0 + 4, Script_GenerateCRC(arg1));
        return true;
    }
    return false;
}
