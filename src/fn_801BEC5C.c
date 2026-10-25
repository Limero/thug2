// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BEC5C-0x801BECA0 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801BEC5C(Unk_C7387A53 *arg0) {
    s32 temp_r0;
    s32 temp_r9;

    temp_r9 = arg0->unk0x2C;
    if (temp_r9 <= 4) {
        temp_r0 = temp_r9 + 1;
        arg0->unk0x2C = temp_r0;
        if (temp_r0 > 4) {
            arg0->unk0x2C = 1;
        }
        fn_801BE7F4();
    }
}
