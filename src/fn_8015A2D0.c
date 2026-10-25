// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015A2D0-0x8015A344 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801A34B4(s32);
void AddChecksum(CStruct *, s32, s32);
extern s32 lbl_80305EAC;
bool ScriptGetCurrentSkaterCamAnimName(void *arg0, CScript *arg1) {
    s32 temp_r3;

    temp_r3 = fn_801A34B4(((Unk_40426380 *)lbl_80305EAC)->unk0x378);
    if (temp_r3 != 0) {
        AddChecksum(arg1->unk0x18, QB_CURRENTSKATERCAMANIMNAME, temp_r3);
        return true;
    }
    AddChecksum(arg1->unk0x18, QB_CURRENTSKATERCAMANIMNAME, QB_NONE);
    return false;
}
