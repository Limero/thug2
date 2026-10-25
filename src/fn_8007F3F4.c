// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F3F4-0x8007F434 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80099A64(Unk_13E912CF *, s32, void *, s32);
bool fn_8007F3F4(Unk_C7387A53 *arg0, s32 arg1) {
    Unk_FFAD6788 *temp_r11;
    Unk_C7387A53 *temp_r9;

    temp_r11 = arg0->unk0x34;
    if (temp_r11 != NULL) {
        temp_r9 = arg0->unk0x30;
        fn_80099A64(temp_r9->unk0x54, arg1, temp_r11->unk0xC0, temp_r11->unk0xC4);
    }
    return true;
}
