// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013410-0x8001347C (108B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFF14[];
void fn_800139D4(void *, s32, s32);
void fn_8001347C(void);
void fn_80013410(CStruct *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r11;
    s32 temp_r0;
    u32 temp_r9;

    temp_r0 = arg0->unk0x4;
    arg0->unk0x0 = arg3;
    *(s32 *)&lbl_802FFF14 = (var_r11 = 1);
    if ((temp_r0 != 0) && (arg2 == 0)) {
        temp_r9 = *((u32 *)&arg0->unk0x10);
        if ((temp_r9 & (1U << arg1)) == 0) {
            var_r11 = 0;
        }
        if (var_r11 != 0) {
            fn_800139D4(arg0, arg1, arg3);
            return;
        }
    }
    fn_8001347C();
}
