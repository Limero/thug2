// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800100A4-0x80010124 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8000F9C4(s32, s32);
void fn_800100A4(Unk_C7387A53 *arg0) {
    void *temp_r11;
    CStruct *temp_r9;

    if ( arg0->unk0x14C != NULL) {
        fn_8000F9C4(arg0, arg0->unk0x154);
        arg0->unk0x154 = NULL;
        fn_8000F9C4(arg0, arg0->unk0x150);
        temp_r11 = arg0->unk0x14C;
        arg0->unk0x150 = 0;
        if (temp_r11 != NULL) {
            temp_r9 = ((CScript *)temp_r11)->unk0x18;
            ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + *(s16 *)((char *)temp_r9 + 0x8), 3);
        }
        arg0->unk0x14C = NULL;
    }
}