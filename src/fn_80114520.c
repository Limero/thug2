// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114520-0x80114638 (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029D16C;

s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80109798(s32, f32, f32, f32, f32, s32, s32);

bool ScriptInitSun(CStruct *arg0) {
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f0;

    temp_f0 = lbl_8029D16C;
    sp20 = 0;
    sp14 = temp_f0;
    sp8 = temp_f0;
    spC = temp_f0;
    sp10 = temp_f0;
    sp18 = 0;
    sp1C = 0;
    GetFloat(arg0, QB_THETA, &sp8, 1);
    GetFloat(arg0, QB_PHI, &spC, 1);
    GetFloat(arg0, QB_RADIUS, &sp10, 1);
    GetFloat(arg0, QB_SIZE, &sp14, 1);
    GetChecksum_2(arg0, QB_TEXTURE, &sp18, 1);
    GetChecksum_2(arg0, QB_CORONA_TEXTURE, &sp1C, 1);
    GetChecksum_2(arg0, QB_LENS_FLARE_DATA, &sp20, 1);
    fn_80109798(sp18, sp8, spC, sp10, sp14, sp1C, sp20);
    return true;
}
