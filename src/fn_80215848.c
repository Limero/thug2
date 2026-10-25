// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80215848-0x8021589C (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80303150[];
void AddInteger(CStruct *, s32, s32);
s32 Tmr_GetTime(void);
bool fn_80215848(Unk_C7387A53 *arg0, void *arg1, CScript *arg2) {
    s32 temp_r29;
    s32 temp_r30;

    temp_r29 = arg2->unk0x18;
    temp_r30 = arg0->unk0x20;
    AddInteger(temp_r29, QB_STATETIME, (*(s32 *)&lbl_80303150 + Tmr_GetTime()) - temp_r30);
    return true;
}
