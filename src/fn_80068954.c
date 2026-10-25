// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80068954-0x80068998 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80068954(void) {
    void *temp_r3;
    Unk_F5317C5D *temp_r9;

    temp_r3 = fn_80068760();
    if (temp_r3 != NULL) {
        temp_r9 = ((Unk_9994C3F5 *)temp_r3)->unk0x8;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r3 + temp_r9->unk0x8, 3);
    }
}
