// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9E14-0x801B9EC8 (180B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AC270;
extern f32 lbl_802AC274;
extern f32 lbl_802AC278;
extern f32 lbl_802AC27C;
extern s32 GetFloat(CStruct * arg0, u32 arg1, f32 * arg2, s32 arg3);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, u32 arg1);
bool fn_801B9E14(Unk_C7387A53 *arg0, CStruct *arg1) {
    f32 sp8;
    Unk_C7387A53 *temp_r3;
    f32 temp_f0;
    f32 v0;
    f32 vv;
    f32 mm;
    sp8 = lbl_802AC270;
    if (GetFloat(arg1, QB_PERCENT, &sp8, 0) != 0) {
        sp8 = (sp8 / lbl_802AC274) + lbl_802AC278;
    }
    temp_r3 = (void *)GetChecksum_3(arg0->unk0xC, QB_MOTION);
    if (temp_r3 != NULL) {
        v0 = *((f32 *)&temp_r3->unk0x30);
        vv = sp8;
        mm = lbl_802AC27C;
        temp_f0 = v0 * vv;
        *((f32 *)&temp_r3->unk0x30) = temp_f0;
        if (temp_f0 > mm) {
            *((f32 *)&temp_r3->unk0x30) = mm;
        }
    }
    return true;
}
