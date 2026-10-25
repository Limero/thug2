// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155CD4-0x80155D20 (76B). Byte-identical.
#include "types.h"
extern char lbl_80305EC0[];
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
s32 fn_80198FBC(void *);
bool ScriptGetGoalsMode(void *arg0, CScript *arg1) {
    s32 temp_r5;
    temp_r5 = fn_80198FBC(*(s32 *)&lbl_80305EC0);
    AddChecksum(arg1->unk0x18, QB_GOALS,  temp_r5);
    return true;
}
