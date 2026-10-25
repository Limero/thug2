// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80215B28-0x80215BA8 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: timed property setter — converts (now - field) * lbl_802AF750
// via the (f32)(u32) cast (2^52-magic pool) and pushes it through fn_8012772C.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AF750;
extern s32 lbl_80303150;
extern s32 Tmr_GetTime();
extern s32 fn_8012772C(CStruct *, s32, f32);
bool fn_80215B28(Unk_C7387A53 *arg0, s32 arg1, CScript *arg2) {
    s32 temp_r29;
    s32 temp_r30;

    temp_r29 = arg2->unk0x18;
    temp_r30 = arg0->unk0x20;
    fn_8012772C(temp_r29, QB_STATEDURATION,
                (f32)(u32)((lbl_80303150 + Tmr_GetTime()) - temp_r30) * lbl_802AF750);
    return true;
}
