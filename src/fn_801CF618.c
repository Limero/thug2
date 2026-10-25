// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CF618-0x801CF6B4 (156B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern f32 lbl_802AD34C;
extern f32 lbl_802AD350;
extern f32 lbl_802AD354;
bool fn_801CF618(Unk_D63BF381 *arg0, CStruct *arg1) {
    f32 temp_f0;
    f32 temp_f13;
    f32 temp_f12;

    temp_f0 = lbl_802AD34C;
    temp_f13 = lbl_802AD350;
    temp_f12 = lbl_802AD354;
    *((f32 *)&arg0->unk0x304) = temp_f0;
    *((f32 *)&arg0->unk0x308) = temp_f13;
    *((f32 *)&arg0->unk0x30C) = temp_f12;
    GetFloat(arg1, QB_RADIUS, (char *)arg0 + 0x304, 0);
    GetFloat(arg1, QB_SPEED, (char *)arg0 + 0x308, 0);
    GetFloat(arg1, QB_TURN, (char *)arg0 + 0x30C, 0);
    return true;
}
