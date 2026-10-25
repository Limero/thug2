// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070570-0x800705B4 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_80294D7C;
void GetFloat(CStruct *, s32, f32 *, s32);
bool fn_80070570(CScript *arg0, CStruct *arg1) {
    *((f32 *)&arg0->unk0x18) = lbl_80294D7C;
    GetFloat(arg1, 0, (char *)arg0 + 0x18, 0);
    return true;
}
