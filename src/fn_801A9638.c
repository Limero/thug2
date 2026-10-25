// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9638-0x801A9670 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801A9638(CScript *arg0, Unk_43D5C83F *arg1) {
    u8 temp_r9;

    if ((s32) arg1->unk0x8 == 0) {
        temp_r9 = arg1->unk0x4;
        if ((s32) temp_r9 == 0) {
            arg1->unk0x8 = 1;
            arg1->unk0x0 = (s32) arg0->unk0x18;
            return;
        }
        arg1->unk0x4 = (u8) (temp_r9 - 1);
    }
}
