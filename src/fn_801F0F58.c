// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F0F58-0x801F0FC4 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80303150;
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern s32 Tmr_GetTime(void);
extern void fn_801F0FC4(Unk_C7387A53 *);
void fn_801F0F58(void *arg0) {
    s32 temp_r0;
    s32 temp_r9;
    Unk_C7387A53 *temp_r30;
    CStruct *temp_r31;

    temp_r30 = arg0;
    temp_r31 = GetChecksum_3(temp_r30->unk0xC, QB_SKATERSTATE) + 0x30;
    temp_r0 = temp_r31->unk0x4;
    temp_r9 = temp_r0 ^ 1;
    if (temp_r0 != temp_r9) {
        temp_r31->unk0x4 = temp_r9;
        temp_r31->unk0x8 = lbl_80303150 + Tmr_GetTime();
    }
    fn_801F0FC4(temp_r30);
}
