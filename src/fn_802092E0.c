// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802092E0-0x80209334 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802092E0(Unk_CF8B1206 *arg0) {
    s32 temp_r0;
    s32 temp_r9;

    temp_r9 = arg0->unk0xA70;
    if (temp_r9 != -1) {
        if (temp_r9 == (s32) arg0->unk0xA74) {
            fn_80209268();
            return;
        }
        temp_r0 = temp_r9 + 1;
        arg0->unk0xA70 = temp_r0;
        if (temp_r0 > 0x63) {
            arg0->unk0xA70 = 0;
        }
    }
}
