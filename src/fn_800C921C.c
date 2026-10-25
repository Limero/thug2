// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C921C-0x800C9290 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80299218;
s32 GetFloat(CStruct *, s32, f32 *, s32);
bool fn_800C921C(Unk_C7387A53 *arg0, CStruct *arg1) {
    GetFloat(arg1, QB_PERCENT, (char *)arg0 + 0x132C, 1);
    arg0->unk0x132C = (f32) (arg0->unk0x132C * lbl_80299218);
    GetFloat(arg1, QB_DURATION, (char *)arg0 + 0x1330, 1);
    return true;
}
