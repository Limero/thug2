// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EF220-0x801EF2B4 (148B). Byte-identical.
#include "types.h"
#include "structs.h"

extern f64 lbl_802ADC78;
extern f32 lbl_802ADC80;
extern s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);
extern s32 ContainsFlag(CStruct * arg0, u32 arg1);

bool fn_801EF220(Unk_C7387A53 *arg0, CStruct *arg1) {
    f32 temp_f0;

    if (ContainsFlag(arg1, 0xFD2EACADu) != 0) {
        if (*((f32 *)&arg0->unk0x2C) != lbl_802ADC78) {
            return true;
        }
    }
    if (GetFloat(arg1, 0, (char *)arg0 + 0x2C, 0) != 0) {
        temp_f0 = *((f32 *)&arg0->unk0x2C) * lbl_802ADC80;
        *((f32 *)&arg0->unk0x2C) = temp_f0 * temp_f0;
    }
    return true;
}
