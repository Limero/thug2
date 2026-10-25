// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CF7A0-0x801CF7F8 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80303150[];
bool fn_801CF7A0(Unk_71062261 *arg0) {
    CStruct *temp_r31;

    temp_r31 = arg0->unk0x15BC + 0x3C;
    if ((s32) temp_r31->unk0x4 != 1) {
        temp_r31->unk0x4 = 1;
        temp_r31->unk0x8 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
    }
    return true;
}
