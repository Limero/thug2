// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801400C0-0x80140120 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetStructure_2(s32, s32, s32 *, s32);
s32 fn_80126FF4(s32, CStruct *);
bool fn_801400C0(s32 arg0, s32 arg1, CStruct *arg2) {
    s32 sp8;

    sp8 = 0;
    if (GetStructure_2(arg0 + 4, arg1, &sp8, 0) == 0) {
        return false;
    }
    fn_80126FF4(sp8, arg2);
    return true;
}
