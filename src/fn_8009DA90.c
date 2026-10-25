// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DA90-0x8009DABC (44B). Byte-identical.
#include "types.h"
extern s32 lbl_80301A0C;
s32 fn_8009DED4(void);
s32 fn_8009DA90(void) {
    s32 temp_r3;

    temp_r3 = fn_8009DED4();
    lbl_80301A0C = temp_r3 ^ 1;
    return temp_r3;
}
