// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801774E4-0x8017755C (120B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801774E4(CScript *arg0) {
    void *temp_r11;
    void *temp_r11_2;
    Unk_4E705049 *temp_r9;
    Unk_4E705049 *temp_r9_2;

    temp_r11 = arg0->unk0x1C;
    if (temp_r11 != NULL) {
        temp_r9 = ((CScript *)temp_r11)->unk0x18;
        ((s32 (*)(void *, s32))temp_r9->unk0x1C)(temp_r11 + temp_r9->unk0x18, 3);
    }
    temp_r11_2 = arg0->unk0x20;
    if (temp_r11_2 != NULL) {
        temp_r9_2 = ((CScript *)temp_r11_2)->unk0x18;
        ((s32 (*)(void *, s32))temp_r9_2->unk0x1C)(temp_r11_2 + temp_r9_2->unk0x18, 3);
    }
}
