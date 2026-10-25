// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F3C18-0x801F3CE0 (200B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_801F3A1C(Unk_7258DEBD *, CStruct *);
void fn_801F3C18(s32 arg0, CStruct *arg1) {
    GetInteger(arg1, QB_ACCELERATION_INTERVAL, arg0 + 0x2D8, 0);
    GetFloat(arg1, QB_ACCELERATION_PERCENT, arg0 + 0x2DC, 0);
    GetInteger(arg1, QB_TRICK_TIME, arg0 + 0x2E0, 0);
    GetInteger(arg1, QB_TIME_TO_STOP_ADDING_TRICKS, arg0 + 0x2E4, 0);
    GetInteger(arg1, QB_MAX_TRICKS, arg0 + 0x2E8, 0);
    GetInteger(arg1, QB_SPIN, arg0 + 0x2EC, 0);
    fn_801F3A1C(arg0, arg1);
}
