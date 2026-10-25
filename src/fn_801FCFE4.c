// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FCFE4-0x801FD03C (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801FCFE4(Unk_C7387A53 *arg0) {
    Unk_9994C3F5 *temp_r11;
    Unk_F5317C5D *temp_r9;

    temp_r11 = *((void * *)&arg0->unk0xA0);
    if (temp_r11 != NULL) {
        temp_r9 = *((void * *)&temp_r11->unk0x8);
        ((s32 (*)(void *, s32))temp_r9->unk0xC)(
            (char *)temp_r11 + (s32)temp_r9->unk0x8, 3);
        arg0->unk0xA0 = NULL;
    }
}
