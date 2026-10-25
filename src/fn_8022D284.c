// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D284-0x8022D334 (176B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_800F3610(Unk_C7387A53 *, s32);
void fn_8022CB00(void *, s32);
void fn_8022D284(Unk_C8FEE62D *arg0, s32 arg1) {
    Unk_9D99273B *temp_r11;
    Unk_F5317C5D *temp_r9;
    Unk_9D99273B *temp_r11_2;
    Unk_F5317C5D *temp_r9_2;

    temp_r11 = arg0->unk0x14;
    if (temp_r11 != NULL) {
        temp_r9 = temp_r11->unk0x284;
        ((void (*)(void *, s32))temp_r9->unk0xC)(
            (char *)temp_r11 + temp_r9->unk0x8, 3);
    }
    temp_r11_2 = arg0->unk0x10;
    if (temp_r11_2 != NULL) {
        temp_r9_2 = temp_r11_2->unk0x284;
        ((void (*)(void *, s32))temp_r9_2->unk0xC)(
            (char *)temp_r11_2 + temp_r9_2->unk0x8, 3);
    }
    fn_800F3610((char *)arg0 + 0x494, 2);
    fn_8022CB00((char *)arg0 + 0x5C, 2);
    fn_8022CB00((char *)arg0 + 0x24, 2);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
