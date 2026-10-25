// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80166C18-0x80166C7C (100B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EFC;
s32 fn_801A5CE8(Unk_C7387A53 *);
void fn_801A6070(void *, s32, s32);
void s_read_custom_skater_info(s32 arg0) {
    s32 temp_r30;
    s32 temp_r31;

    temp_r30 = arg0;
    temp_r31 = lbl_80305EFC;
    if (fn_801A5CE8(temp_r31) == 0) {
        fn_801A6070(temp_r31, temp_r30, 0);
    } else {
        fn_801A6070(temp_r31, temp_r30, 1);
    }
}
