// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2D38-0x800F2DAC (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800F28E4(Unk_C7387A53 *arg0, Unk_C7387A53 *arg1);
void fn_800F2D38(Unk_C7387A53 *arg0, Unk_C7387A53 *arg1, s32 arg2) {
    Unk_C7387A53 *temp_r31;
    Unk_C7387A53 *var_r30;

    if (arg1 != NULL) {
        var_r30 = (Unk_C7387A53 *)arg1->unk0x2C;
        do {
            temp_r31 = var_r30;
            var_r30 = (Unk_C7387A53 *)temp_r31->unk0x2C;
            if (arg2 != 0 || (s32)temp_r31->unk0xC == 0) {
                fn_800F28E4(arg0, temp_r31);
            }
        } while (temp_r31 != arg1);
    }
}
