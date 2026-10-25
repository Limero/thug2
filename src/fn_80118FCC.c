// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118FCC-0x80119018 (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80303150[];
s32 Tmr_GetTime(void);
void AddInteger(CStruct *, s32, s32);
bool ScriptGetStartTime(void *arg0, CScript *arg1) {
    s32 temp_r30;

    temp_r30 = arg1->unk0x18;
    AddInteger(temp_r30, QB_STARTTIME, *(s32 *)&lbl_80303150 + Tmr_GetTime());
    return true;
}
