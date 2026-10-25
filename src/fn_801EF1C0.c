// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EF1C0-0x801EF220 (96B). Byte-identical.
#include "types.h"
#include "structs.h"

extern f32 lbl_802ADC74;
extern s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);

bool fn_801EF1C0(Unk_C7387A53 *arg0, CStruct *arg1) {
    f32 temp_f0;

    if (GetFloat(arg1, 0, (char *)arg0 + 0x28, 0) != 0) {
        temp_f0 = *((f32 *)&arg0->unk0x28) * lbl_802ADC74;
        *((f32 *)&arg0->unk0x28) = temp_f0 * temp_f0;
    }
    return true;
}
