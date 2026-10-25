// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EFB60-0x800EFBB4 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80131BAC(Unk_15EF4A35 *, s32);
void fn_8011BEFC(s32);
void fn_800EFB60(Unk_C7387A53 *arg0) {
    if ((s32) arg0->unk0x20 != 0) {
        fn_80131BAC(arg0->unk0xC, QB_FAM_PLAY_STREAM);
        fn_8011BEFC(arg0->unk0x20);
        arg0->unk0x20 = 0;
    }
}
