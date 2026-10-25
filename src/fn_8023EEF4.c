// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023EEF4-0x8023EF44 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_8023EEF4(Unk_5A2FF52D *arg0, Unk_F96D0DC8 *arg1) {
    Unk_1D62F22E *temp_r3;

    if (((s32) arg0->unk0xC0 == 1) && ((temp_r3 = (char *)arg0 + 0x78, (((arg1->unk0x0) == (arg0->unk0x78)) == 0)) || ((arg1->unk0x1) != (temp_r3->unk0x1)) || ((arg1->unk0x2) != (temp_r3->unk0x2)))) {
        return false;
    }
    return true;
}
