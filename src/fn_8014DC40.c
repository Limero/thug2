// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014DC40-0x8014DC98 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 fn_80174A58(void * arg0, CStruct * arg1);
extern s32 fn_801A57D4(s32 arg0);
extern s32 AddString(CStruct * arg0, s32 arg1, void * arg2);
bool ScriptGetCustomSkaterFilename(s32 arg0, CScript *arg1) {
    s32 temp_r29;
    s32 temp_r3;

    temp_r3 = fn_80174A58(*(s32 *)&lbl_80305EAC, 0);
    temp_r29 = arg1->unk0x18;
    AddString(temp_r29, QB_CASFILENAME, fn_801A57D4(temp_r3));
    return true;
}
