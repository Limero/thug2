// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128850-0x801288C4 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8000A778(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
bool fn_80128850(CStruct *arg0, void *arg1, s32 *arg2, s32 arg3) {
    s32 sp8;
    if (GetChecksum_2(arg0, arg1, arg2, arg3) == 0) {
        sp8 = 0;
        if (GetString(arg0, arg1, &sp8, arg3) != 0) {
            *arg2 = fn_8000A778(sp8);
            return true;
        }
        return false;
    }
    return true;
}