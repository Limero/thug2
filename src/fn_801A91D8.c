// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A91D8-0x801A920C (52B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801A91D8(Unk_C8FEE62D *arg0, Unk_C7387A53 *arg1) {
    u32 temp_r9;

    temp_r9 = arg1->unk0x80;
    if ((temp_r9 <= 0x1FU) && ((s32) arg0->unk0x44 == 0)) {
        *((s32 *)arg1 + temp_r9) = arg0->unk0x18;
        arg1->unk0x80 = (u32) (arg1->unk0x80 + 1);
    }
}
