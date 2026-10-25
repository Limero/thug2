// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80253BF0-0x80253C60 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA340;
void fn_80257CC4(void *dst, s32 size);
void *fn_8024EAF4(void *heap, s32 size);

bool fn_80253BF0(s32 arg0, Unk_C7387A53 *arg1, s32 arg2) {
    fn_80257CC4(arg1, 0x58);
    arg1->unk0x2C = arg0;
    arg1->unk0x38 = 0;
    arg1->unk0x30 = 0;
    if (arg2 != 0) {
        s32 lblv;
        arg1->unk0x38 = arg2;
        lblv = lbl_803CA340;
        arg1->unk0x30 = (s32)fn_8024EAF4(lblv, arg2);
    }
    arg1->unk0x34 = 0;
    return false;
}
