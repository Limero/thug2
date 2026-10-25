// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80023504-0x800235AC (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_803CAF18[];
void fn_8028D464(void);
void fn_80023504(f32 farg0) {
    f32 sp8;
    u32 v;
    u8 *temp_r9_2;
    u8 *temp_r9_3;
    u8 *temp_r9_4;
    u8 *temp_r9_5;
    Unk_9994C3F5 *temp_r10;
    Unk_9994C3F5 *temp_r10_2;
    Unk_9994C3F5 *temp_r11;
    Unk_9994C3F5 *temp_r11_2;
    register CStruct *temp_r9 __asm__("r11");

    sp8 = farg0;
    v = *(u32 *)&sp8;
    temp_r9 = *(void * *)&lbl_803CAF18;
    if ((u32) (*((u32 *)&temp_r9->unk0x8) + 4) > (u32) *((u32 *)&temp_r9->unk0xC)) {
        fn_8028D464();
    }
    temp_r10 = *(void * *)&lbl_803CAF18;
    temp_r9_2 = temp_r10->unk0x8;
    *temp_r9_2 = (v & QB_UNKNOWN_0xFF000000) >> 0x18;
    temp_r10->unk0x8 = (u8 *) (temp_r9_2 + 1);
    temp_r11 = *(void * *)&lbl_803CAF18;
    temp_r9_3 = temp_r11->unk0x8;
    *temp_r9_3 = (v & QB_MASK_BYTE2) >> 0x10;
    temp_r11->unk0x8 = (u8 *) (temp_r9_3 + 1);
    temp_r10_2 = *(void * *)&lbl_803CAF18;
    temp_r9_4 = temp_r10_2->unk0x8;
    *temp_r9_4 = (v & QB_MASK_BYTE1) >> 8;
    temp_r10_2->unk0x8 = (u8 *) (temp_r9_4 + 1);
    temp_r11_2 = *(void * *)&lbl_803CAF18;
    temp_r9_5 = temp_r11_2->unk0x8;
    *temp_r9_5 = v;
    temp_r11_2->unk0x8 = (u8 *) (temp_r9_5 + 1);
}
