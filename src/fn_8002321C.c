// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002321C-0x80023278 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_803CAF18[];
void fn_8002321C(s8 arg0) {
    s8 *temp_r9_2;
    Unk_9994C3F5 *temp_r11;
    CStruct *temp_r9;

    temp_r9 = *(void * *)&lbl_803CAF18;
    if ((u32) (*((u32 *)&temp_r9->unk0x8) + 1) > (u32) *((u32 *)&temp_r9->unk0xC)) {
        fn_8028D464();
    }
    temp_r11 = *(void * *)&lbl_803CAF18;
    temp_r9_2 = temp_r11->unk0x8;
    *temp_r9_2 = arg0;
    temp_r11->unk0x8 = (s8 *) (temp_r9_2 + 1);
}
