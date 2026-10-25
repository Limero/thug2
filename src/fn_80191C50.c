// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80191C50-0x80191CC0 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_801270B4(void *, void *);
#include "qb_constants.h"
s32 GetChecksum_2(s32, s32, s32, s32);
void fn_80191C50(void * arg0) {
    s32 sp8;
    s32 temp_r31;
    register s32 t8 __asm__("r3");

    temp_r31 = fn_80191FD4();
    sp8 = 0;
    if (GetChecksum_2(temp_r31, QB_CURRENT_VO_STREAM, &sp8, 0) != 0) {
        fn_801270B4(temp_r31, QB_CURRENT_VO_STREAM);
        t8 = sp8;
        if (t8 != 0) {
            fn_8011BEFC();
        }
    }
}
