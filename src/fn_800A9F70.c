// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A9F70-0x800A9FF0 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80303150[];
s32 Tmr_GetTime(void);
void fn_800A9F70(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 temp_r3;
    s32 newval;

    if (arg1 != 0) {
        if ((s32) arg0->unk0x4 == 0) {
            temp_r3 = Tmr_GetTime();
            newval = (s32) (*(s32 *)&lbl_80303150 + temp_r3);
            arg0->unk0x14 = 1;
            arg0->unk0x8 = newval;
        }
        arg0->unk0x4 = 1;
    } else {
        if ((s32) arg0->unk0x4 != 0) {
            arg0->unk0x18 = 1;
        }
        arg0->unk0x4 = arg1;
    }
    arg0->unk0x4 = arg1;
}
