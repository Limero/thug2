// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9820-0x801F9890 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801FC284(void);
void *fn_801FC2A4(s32);
void *fn_801F839C(void *);
void *fn_801F9820(Unk_C7387A53 *arg0) {
    Unk_C7387A53 *temp_r3;
    Unk_C7387A53 *temp_r11;
    Unk_C7387A53 *var_r3;

    if (fn_801FC284() == 0x190) {
        return NULL;
    }
    temp_r3 = fn_801F839C(fn_801FC2A4(0x38));
    var_r3 = temp_r3;
    temp_r3->unk0x24 = arg0->unk0xC;
    temp_r11 = arg0->unk0xC;
    if (temp_r11 != NULL) {
        temp_r11->unk0x28 = var_r3;
    }
    var_r3->unk0x28 = 0;
    arg0->unk0xC = var_r3;
    return var_r3;
}
