// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80141BC8-0x80141C54 (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8000C868(Unk_A0A7249E *);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_80141BC8(Unk_4701C175 *arg0) {
    Unk_264DC741 *temp_r11;
    Unk_FFAD6788 *temp_r3;
    Unk_C7387A53 *temp_r9;

    if (((s32) arg0->unk0x354 != 0) && ((s32) arg0->unk0xC8 != 0)) {
        temp_r11 = *((s32 *)&arg0->unk0x290);
        arg0->unk0x354 = 0;
        arg0->unk0x114 = (s32) (arg0->unk0x114 & QB_UNKNOWN_0xFFFFFFFE);
        if (temp_r11 != NULL) {
            temp_r9 = temp_r11->unk0x51C;
            fn_8000C868(temp_r9->unk0x20);
        }
        temp_r3 = GetChecksum_3(arg0, QB_SKATERLOOPINGSOUND);
        if (temp_r3 != NULL) {
            temp_r3->unk0xE4 = 1;
        }
    }
}
