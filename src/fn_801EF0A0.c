// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EF0A0-0x801EF100 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);
extern f32 lbl_802ADC68;
bool fn_801EF0A0(Unk_31DE137E *arg0, CStruct *arg1) {
    f32 temp_f0;

    if (GetFloat(arg1, 0, (char *)arg0 + 0x1C, 0) != 0) {
        temp_f0 = *((f32 *)&arg0->unk0x1C) * lbl_802ADC68;
        *((f32 *)&arg0->unk0x1C) = temp_f0 * temp_f0;
    }
    return true;
}
