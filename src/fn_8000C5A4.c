// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000C5A4-0x8000C5CC (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000C5A4(Unk_7C9BF17E *arg0) {
    s32 temp_r9;

    temp_r9 = arg0->unk0xDC;
    if ((temp_r9 == 0) && ((s32) arg0->unk0x10 <= 3)) {
        arg0->unk0x18 = temp_r9;
        arg0->unk0xDC = 1;
    }
}
