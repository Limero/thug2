// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A19C-0x8000A1FC (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80009D30(void *, s32);
void fn_8000A19C(Unk_C7387A53 *arg0, s32 arg1) {
    Unk_F5317C5D *temp_r9;
    Unk_C8FEE62D *temp_r11;

    temp_r11 = (Unk_C8FEE62D *)arg0->unk0x28;
    if (temp_r11 != NULL) {
        temp_r9 = (Unk_F5317C5D *)temp_r11->unk0x14;
        ((s32 (*)(void *, s16))temp_r9->unk0xC)((char *)temp_r11 + temp_r9->unk0x8, 3);
    }
    fn_80009D30(arg0, arg1);
}
