// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EDEB4-0x800EDF3C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8011A6A8(s32, s32);
#include "structs.h"
s32 fn_8009F558(s32, s32);
extern char lbl_80302C34[];
extern char lbl_8029AED8[];
void fn_800EDEB4(CScript *arg0, s32 arg1) {
    s32 temp_r0;

    temp_r0 = arg0->unk0x24;
    arg0->unk0x18 = (s32)lbl_8029AED8;
    if (temp_r0 != 0) {
        fn_8011A6A8(*(s32 *)lbl_80302C34, temp_r0);
        arg0->unk0x24 = 0;
    }
    if ((s32) arg0->unk0x28 != 0) {
        fn_8011A6A8(*(s32 *)lbl_80302C34, (s32) arg0->unk0x28);
        arg0->unk0x28 = 0;
    }
    fn_8009F558(arg0, arg1);
}
