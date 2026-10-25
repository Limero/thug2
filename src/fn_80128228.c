// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128228-0x80128294 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80127F60(CStruct *, s32, s32, f32 *);
s32 fn_80129570(s32, s32);
// GetInteger @ 0x80128228
bool GetInteger(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    s32 sp8;
    if (fn_80127F60(arg0, arg1, 1, &sp8) != 0) {
        *arg2 = sp8;
        return true;
    }
    if (arg3 != 0) {
        fn_80129570(arg0, 0);
    }
    return false;
}
