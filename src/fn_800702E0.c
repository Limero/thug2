// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800702E0-0x80070324 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_80294D64;
s32 GetFloat(CStruct *, s32, f32 *, s32);
bool fn_800702E0(f32 *arg0, CStruct *arg1) {
    *arg0 = lbl_80294D64;
    GetFloat(arg1, 0, arg0, 0);
    return true;
}
