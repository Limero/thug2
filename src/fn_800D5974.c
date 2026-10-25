// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D5974-0x800D5A38 (196B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80299B58;
extern f32 lbl_80299B5C;
extern f32 lbl_80299B60;
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 ContainsFlag(CStruct *, s32);
bool fn_800D5974(Unk_7A675EAB *arg0, CStruct *arg1) {
    volatile double _dummy;
    f32 temp_f31;

    temp_f31 = lbl_80299B58;
    *((f32 *)&arg0->unk0x38) = temp_f31;
    *((f32 *)&arg0->unk0x1B8) = temp_f31;
    if (arg0->unk0x1C0 == temp_f31) {
        arg0->unk0x1C0 = lbl_80299B5C;
    }
    GetFloat(arg1, 0, (f32 *)((char *)arg0 + 0x38), 0);
    if (ContainsFlag(arg1, QB_UNKNOWN_0xF915B4F3) == 0) {
        *((f32 *)&arg0->unk0x38) *= lbl_80299B60;
        *((f32 *)&arg0->unk0x1BC) = arg0->unk0x34;
    }
    if (*((f32 *)&arg0->unk0x38) == temp_f31) {
        arg0->unk0x34 = temp_f31;
    }
    arg0->unk0x20 |= 8;
    return true;
}
