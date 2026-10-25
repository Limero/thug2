// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EC620-0x801EC684 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 Tmr_GetTime(void);
extern s32 lbl_80303150;
void fn_801EC620(Unk_7258DEBD *arg0) {
    CStruct *temp_r31;

    temp_r31 = *((void * *)&arg0->unk0x15BC) + 0x24;
    if ((temp_r31->unk0x4 == 0) && (*(s32 *)(*((void * *)&arg0->unk0x15A0) + 0x200) != 0)) {
        temp_r31->unk0x4 = 1;
        temp_r31->unk0x8 = lbl_80303150 + Tmr_GetTime();
    }
}