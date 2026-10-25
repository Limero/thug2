// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C12A4-0x801C12F4 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetFloat(CStruct * entry, s32 hash, f32 * out, s32 flag);
extern f32 lbl_802AC7B0;
extern f32 lbl_802AC7B4;
void fn_801C12A4(Unk_C7387A53 *arg0, CStruct *arg1) {
    f32 temp_f0 = lbl_802AC7B0;
    f32 temp_f13 = lbl_802AC7B4;

    *((f32 *)&arg0->unk0x48) = temp_f0;
    *((f32 *)&arg0->unk0x44) = temp_f13;
    GetFloat((void *)arg1, QB_VOLUME_MULT, (char *)arg0 + 0xF4, 0);
}
