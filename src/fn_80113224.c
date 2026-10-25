// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113224-0x801132A8 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_8029D0E8;

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void PlayMusicStream(s32, f32);

bool ScriptPlayMusicStream(CStruct *arg0) {
    f32 spC;
    s32 sp8;

    sp8 = 0;
    if (GetChecksum_2(arg0, 0, &sp8, 0) != 0) {
        spC = lbl_8029D0E8;
        GetFloat(arg0, QB_VOL, &spC, 0);
        PlayMusicStream(sp8, spC);
        return true;
    }
    return false;
}
