// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070394-0x800703D8 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetFloat(CStruct *, s32, f32 *, s32);
extern f32 lbl_80294D68;
bool fn_80070394(Unk_9994C3F5 *arg0, CStruct *arg1) {
    *((f32 *)&arg0->unk0x8) = lbl_80294D68;
    GetFloat(arg1, 0, (char *)arg0 + 8, 0);
    return true;
}
