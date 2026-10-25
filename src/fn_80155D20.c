// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80155D20-0x80155D6C (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
s32 fn_80198FBC(void *);
extern char lbl_80305EC0[];
bool ScriptGetTeamGraffitiMode(void *arg0, CScript *arg1) {
    s32 temp_r5;
    temp_r5 = fn_80198FBC(*(s32 *)&lbl_80305EC0);
    AddChecksum(arg1->unk0x18, QB_MODE,  temp_r5);
    return true;
}
