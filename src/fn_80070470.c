// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070470-0x800704B4 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetFloat(CStruct *, s32, f32 *, s32);
extern f32 lbl_80294D6C;
bool fn_80070470(Unk_C7387A53 *arg0, CStruct *arg1) {
    *((f32 *)&arg0->unk0xC) = lbl_80294D6C;
    GetFloat(arg1, 0, (char *)arg0 + 0xC, 0);
    return true;
}
