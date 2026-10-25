// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80136EB8-0x80136F1C (100B). Byte-identical.
#include "types.h"
extern char lbl_80303448[];
extern char lbl_8030344C[];
extern void fn_801376A4(void *arg0, s32 arg1);

void fn_80136EB8(void) {
    u32 temp_r9;

    temp_r9 = *(u32 *)&lbl_8030344C;
    if (temp_r9 > 1U) {
        *(u32 *)&lbl_8030344C = temp_r9 - 1;
        return;
    }
    if (*(s32 *)&lbl_80303448 != 0) {
        fn_801376A4((void *)*(s32 *)&lbl_80303448, 3);
    }
    *(u32 *)&lbl_80303448 = 0U;
    *(u32 *)&lbl_8030344C = 0U;
}
