// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BDD7C-0x800BDE04 (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80298E74;
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 ContainsFlag(CStruct *, s32);
bool fn_800BDD7C(Unk_31DE137E *arg0, CStruct *arg1) {
    GetFloat(arg1, 0, (char *)arg0 + 0x19C, 1);
    if ((ContainsFlag(arg1, QB_FRAMES) != 0) || (ContainsFlag(arg1, QB_FRAME) != 0)) {
        *((f32 *)&arg0->unk0x19C) = (f32) (*((f32 *)&arg0->unk0x19C) * lbl_80298E74);
    }
    return true;
}
