// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C5780-0x801C5800 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802ACBD0;
extern s32 lbl_80303150;
extern s32 Tmr_GetTime();
extern s32 fn_8012772C(CStruct *, s32, f32);
bool fn_801C5780(Unk_C7387A53 *arg0, s32 arg1, CScript *arg2) {
    s32 temp_r29;
    s32 temp_r30;

    temp_r29 = arg2->unk0x18;
    temp_r30 = arg0->unk0x20;
    fn_8012772C(temp_r29, QB_TIMESINCEPHYSICSSWITCH,
                (f32)(u32)((lbl_80303150 + Tmr_GetTime()) - temp_r30) * lbl_802ACBD0);
    return true;
}
