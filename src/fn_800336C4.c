// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800336C4-0x8003374C (136B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80291DA0[];
void fn_80026C44(Unk_C7387A53 *, s32);
void fn_80033560(Unk_C8FEE62D *, s32);
void fn_80034C70(void *);
void fn_8005527C(s32);
void fn_800336C4(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 temp_r3;
    s32 temp_r3_2;
    arg0->unk0x14 = (s32)lbl_80291DA0;
    temp_r3 = arg0->unk0x1C;
    if (temp_r3 != 0) {
        fn_80026C44(temp_r3, arg0->unk0x28);
    }
    temp_r3_2 = arg0->unk0x20;
    if (temp_r3_2 != 0) {
        fn_8005527C(temp_r3_2);
        arg0->unk0x20 = 0;
    }
    arg0->unk0x1C = 0;
    fn_80033560(arg0, 0);
    if (arg1 & 1) {
        fn_80034C70(arg0);
    }
}
