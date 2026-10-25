// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F3B4C-0x801F3C18 (204B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void AddInteger(CStruct *, s32, s32);
void fn_8012772C(CStruct *, s32, f32);
void fn_801F36B0(Unk_5FCDF30E *, CStruct *);
void fn_801F3910(Unk_7258DEBD *, CStruct *);
void fn_801F3B4C(Unk_5FCDF30E *arg0, CStruct *arg1, s32 arg2) {
    AddInteger(arg1, QB_ACCELERATION_INTERVAL, arg0->unk0x2D8);
    fn_8012772C(arg1, QB_ACCELERATION_PERCENT, arg0->unk0x2DC);
    AddInteger(arg1, QB_TRICK_TIME, arg0->unk0x2E0);
    AddInteger(arg1, QB_TIME_TO_STOP_ADDING_TRICKS, arg0->unk0x2E4);
    AddInteger(arg1, QB_MAX_TRICKS, arg0->unk0x2E8);
    if (arg2 == 1) {
        fn_801F36B0(arg0, arg1);
        return;
    }
    AddInteger(arg1, QB_SPIN, arg0->unk0x2EC);
    fn_801F3910(arg0, arg1);
}