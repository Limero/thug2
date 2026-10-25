// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802052C4-0x8020531C (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80302C34[];
extern s32 fn_8011A6A8(s32 arg0, s32 arg1);
void fn_802052C4(Unk_C7387A53 *arg0) {
    if (arg0->unk0x30 != 0) {
        fn_8011A6A8(*(s32 *)&lbl_80302C34, arg0->unk0x30);
    }
    arg0->unk0x30 = 0;
    arg0->unk0x3C = 0;
    arg0->unk0x40 = 0;
    arg0->unk0x44 = 0;
    arg0->unk0x38 = 0;
}
