// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800705F4-0x80070638 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetFloat(CStruct *, s32, f32 *, s32);
extern f32 lbl_80294D80;
bool fn_800705F4(Unk_C7387A53 *arg0, CStruct *arg1) {
    *((f32 *)&arg0->unk0x20) = lbl_80294D80;
    GetFloat(arg1, 0, (char *)arg0 + 0x20, 0);
    return true;
}
