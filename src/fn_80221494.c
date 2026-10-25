// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221494-0x802214E0 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801276E8(CStruct *, void *, void *);
s32 fn_80198B68(void *);
extern char lbl_80305EC0[];
extern char lbl_802AFEBC[];
bool ScriptGetNumTeams(void *arg0, CScript *arg1) {
    s32 temp_r5;
    temp_r5 = fn_80198B68(*(s32 *)&lbl_80305EC0);
    fn_801276E8(arg1->unk0x18, (s32)lbl_802AFEBC, temp_r5);
    return true;
}
