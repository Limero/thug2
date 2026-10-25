// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80209DE4-0x80209E50 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80303150[];
void fn_80209DE4(Unk_8D6DF6EE *arg0) {
    s32 temp_r30;

    if (((s32) arg0->unk0x12AC != 0) && ((s32) arg0->unk0x12BC != -1)) {
        temp_r30 = arg0->unk0x12B8;
        if ((u32) ((*(s32 *)&lbl_80303150 + Tmr_GetTime()) - temp_r30) > (u32) arg0->unk0x12BC) {
            arg0->unk0x12AC = 0;
        }
    }
}
