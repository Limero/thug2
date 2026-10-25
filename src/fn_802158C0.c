// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802158C0-0x802159C4 (260B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetStructure(s32, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern void AddChecksum(CStruct *, s32, s32);
bool fn_802158C0(Unk_5ECDC062 *arg0, s32 arg1, CScript *arg2) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    s32 var_r5;
    f32 temp_f13_2;
    f32 temp_f13_3;

    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_MAX_SLOW_WALK_SPEED, &sp8, 1);
    temp_f13_2 = sp8;
    if (arg0->unk0x7BC < temp_f13_2) {
        var_r5 = QB_WALK_SLOW;
    } else {
        GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_MAX_FAST_WALK_SPEED, &spC, 1);
        temp_f13_3 = spC;
        if (arg0->unk0x7BC < temp_f13_3) {
            var_r5 = QB_WALK_FAST;
        } else {
            GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_MAX_SLOW_RUN_SPEED, &sp10, 1);
            var_r5 = QB_RUN_FAST;
            if (arg0->unk0x7BC < sp10) {
                var_r5 = QB_RUN_SLOW;
            }
        }
    }
    AddChecksum(arg2->unk0x18, QB_SPEEDSCALE, var_r5);
    return true;
}
