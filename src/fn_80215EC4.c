// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80215EC4-0x80215F28 (100B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
extern char lbl_80305FA0[];
void fn_80216980(Unk_C5BAE83F *, s32);
void fn_80215EC4(void) {
    u32 temp_r9;

    temp_r9 = *(u32 *)&lbl_80305FA0;
    if (temp_r9 > 1U) {
        *(u32 *)&lbl_80305FA0 = temp_r9 - 1;
    } else {
        if ((s32) *(s32 *)&lbl_80305F9C != 0) {
            fn_80216980(*(s32 *)&lbl_80305F9C, 3);
        }
        *(u32 *)&lbl_80305FA0 = 0U;
        *(s32 *)&lbl_80305F9C = 0;
    }
}
