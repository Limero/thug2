// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800685A4-0x80068618 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "structs.h"
extern char lbl_802FFE98[];
void fn_8000F9C4(void *, s32);
typedef struct { char pad0x0[8]; s16 unk0x8; s32 unk0xC; } View685A4;
void fn_800685A4(CStruct *arg0) {
    void *temp_r11;
    View685A4 *temp_r9;

    if ((s32) arg0->unk0xC != 0) {
        fn_8000F9C4(*(void * *)&lbl_802FFE98, (s32) arg0->unk0xC);
        temp_r11 = arg0->unk0x8;
        if (temp_r11 != NULL) {
            temp_r9 = (View685A4 *)((CScript *)temp_r11)->unk0x18;
            ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
        }
        arg0->unk0xC = 0;
        arg0->unk0x8 = NULL;
    }
}
