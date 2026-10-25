// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9600-0x801A9638 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801A9600(CScript *arg0, Unk_43D5C83F *arg1) {
    if ((s32) arg1->unk0x8 == 0) {
        if ((s32) arg1->unk0x0 == (s32) arg0->unk0x18) {
            arg1->unk0x8 = 1;
            return;
        }
        arg1->unk0x4 = (u8) (arg1->unk0x4 + 1);
    }
}
