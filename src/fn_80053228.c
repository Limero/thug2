// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80053228-0x80053270 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800533A8(CStruct *, s32 *);
extern char lbl_80364620[];
void fn_80053228(s32 arg0) {
    s32 sp8;
    s32 temp_r9;
    Unk_9994C3F5 *temp_r3;

    sp8 = arg0;
    temp_r3 = fn_800531F4();
    temp_r9 = temp_r3->unk0x8 - 1;
    temp_r3->unk0x8 = temp_r9;
    if (temp_r9 == 0) {
        fn_800533A8(lbl_80364620, &sp8);
    }
}
