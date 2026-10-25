// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FCE60-0x801FCF20 (192B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AE6B0;
extern f32 lbl_802AE6B4;
extern f32 lbl_802AE6B8;
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern s32 ContainsFlag(CStruct *, s32);

void fn_801FCE60(Unk_C7387A53 *arg0, CStruct *arg1) {
    *((f32 *)&arg0->unk0x90) = lbl_802AE6B0;
    GetFloat(arg1, QB_MIN_HEIGHT, (char *)arg0 + 0x90, 0);
    *((f32 *)&arg0->unk0x74) = lbl_802AE6B4;
    GetFloat(arg1, QB_MIN_RADIUS, (char *)arg0 + 0x74, 0);
    *((f32 *)&arg0->unk0x78) = lbl_802AE6B8;
    GetFloat(arg1, QB_MAX_RADIUS, (char *)arg0 + 0x78, 0);
    arg0->unk0x94 = ContainsFlag(arg1, QB_SIMPLECOLLISION);
    arg0->unk0x98 = ContainsFlag(arg1, QB_ALLOWMOVEMENTTHROUGHWALLS);
}
