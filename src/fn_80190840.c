// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80190840-0x801908E8 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(s32, s32, s32 *, s32);
s32 GetArray(s32, s32, s32 *, s32);
s32 Game_GetGoalManager(void);
s32 fn_80187934(Unk_6BF95B44 *, s32);
s32 fn_801293FC(CStruct *, s32);
s32 fn_80190840(Unk_C7387A53 *arg0) {
    CStruct *spC;
    s32 sp8;
    s32 temp_r3;

    spC = 0;
    if (GetInteger(arg0->unk0x20, QB_REWARD_POINTS, &sp8, 0) != 0) {
        return sp8;
    }
    if (GetArray(arg0->unk0x20, QB_REWARD_POINTS, (s32 *)&spC, 0) != 0) {
        temp_r3 = fn_80187934((Unk_6BF95B44 *)Game_GetGoalManager(), 0);
        if ((temp_r3 >= 0) && (temp_r3 < spC->unk0x4)) {
            return fn_801293FC(spC, temp_r3);
        }
    }
    return 0;
}
