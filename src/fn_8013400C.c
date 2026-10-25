// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013400C-0x80134080 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801323D4(CScript *, s32);
void fn_80126808(Unk_80577C09 *, Unk_5D1D68CC *, s32);
extern char lbl_8029EF18[];
void fn_8013400C(Unk_A7137CF0 *arg0, Unk_5D1D68CC *arg1) {
    s32 temp_r0;
    s32 temp_r11;

    temp_r11 = arg0->unk0x144;
    if ((temp_r11 != 0) || (arg0->unk0x4 & 0x7F0000)) {
        temp_r0 = temp_r11 + 1;
        arg0->unk0x144 = temp_r0;
        if (temp_r0 > 0x13) {
            fn_801323D4(arg0, (s32)lbl_8029EF18);
            return;
        }
    }
    fn_80126808((char *)arg0 + ((arg0->unk0x144 * 0x10) + 4), arg1, 0);
}
