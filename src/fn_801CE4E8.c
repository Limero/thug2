// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CE4E8-0x801CE548 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80303150[];
bool fn_801CE4E8(Unk_C2F9BED0 *arg0) {
    CStruct *temp_r31;

    arg0->unk0x3D8 = 1;
    temp_r31 = arg0->unk0x15BC + 0x90;
    if ((s32) temp_r31->unk0x4 != 0) {
        temp_r31->unk0x4 = 0;
        temp_r31->unk0x8 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
    }
    return true;
}
