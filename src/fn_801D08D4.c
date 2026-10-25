// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D08D4-0x801D0900 (44B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802AD3AC;
s32 fn_801D08D4(Unk_65DFDA7E *arg0) {
    s32 var_r3;

    if (arg0->unk0x328 == 0) {
        return 0;
    }
    var_r3 = 1;
    __asm__("" : "+r"(var_r3));
    if (*((f32 *)&arg0->unk0x330) > lbl_802AD3AC) {
        return var_r3;
    }
    var_r3 = 0;
    return var_r3;
}
