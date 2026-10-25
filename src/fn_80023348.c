// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80023348-0x800233BC (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_803CAF18[];
void fn_8028D464(void);
void fn_80023348(s32 arg0) {
    u8 *temp_r9_2;
    u8 *temp_r9_3;
    Unk_9994C3F5 *temp_r10;
    Unk_9994C3F5 *temp_r11;
    CStruct *temp_r9;
    u16 v;

    v = arg0;
    temp_r9 = *(void * *)&lbl_803CAF18;
    if ((u32) (*((u32 *)&temp_r9->unk0x8) + 2) > (u32) *((u32 *)&temp_r9->unk0xC)) {
        fn_8028D464();
    }
    temp_r10 = *(void * *)&lbl_803CAF18;
    temp_r9_2 = temp_r10->unk0x8;
    *temp_r9_2 = v >> 8;
    temp_r10->unk0x8 = (u8 *) (temp_r9_2 + 1);
    temp_r11 = *(void * *)&lbl_803CAF18;
    temp_r9_3 = temp_r11->unk0x8;
    *temp_r9_3 = v;
    temp_r11->unk0x8 = (u8 *) (temp_r9_3 + 1);
}
