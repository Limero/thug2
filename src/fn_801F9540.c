// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9540-0x801F9594 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F74;
void fn_801F95D4(Unk_C7387A53 *);
void *fn_801F9540(CStruct *arg0) {
    s32 temp_r9;
    s32 temp_r9_2;

    temp_r9 = lbl_80305F74;
    arg0->unk0x10 = temp_r9;
    temp_r9 = temp_r9 + 1;
    lbl_80305F74 = temp_r9;
    arg0->unk0xC = 0;
    arg0->unk0x4 = 0;
    arg0->unk0x8 = 0;
    fn_801F95D4(arg0);
    return arg0;
}
