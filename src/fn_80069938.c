// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80069938-0x80069980 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80069938(Unk_E80761A5 *arg0, s32 arg1) {
    Unk_89391A04 *temp_r9;

    if ((s32) arg0->unk0x178 != arg1) {
        arg0->unk0x178 = arg1;
        temp_r9 = arg0->unk0x1B8;
        temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20);
    }
}
