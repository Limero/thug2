// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801282E0-0x8012834C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80127F60(CStruct *, s32, s32, f32 *);
s32 fn_80129570(s32, s32);
// GetFloat @ 0x801282E0
bool GetFloat(CStruct *arg0, s32 arg1, f32 * arg2, s32 arg3) {
    f32 sp8;
    if (fn_80127F60(arg0, arg1, 2, &sp8) != 0) {
        *arg2 = sp8;
        return true;
    }
    if (arg3 != 0) {
        fn_80129570(arg0, 0);
    }
    return false;
}
