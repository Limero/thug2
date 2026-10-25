// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802214E0-0x80221550 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_80128294(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
extern s32 fn_80219B18(s32 arg0, s32 arg1);
extern void fn_801276E8(CStruct * arg0, void * arg1, s32 arg2);
extern char lbl_802AFE9C[];
extern char lbl_802AFEA4[];
extern char lbl_802AFEC8[];
extern s32 lbl_80305F9C;
bool ScriptGetNumPlayersOnTeam(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;
    s32 var_r3;

    temp_r30 = lbl_80305F9C;
    sp8 = 0;
    fn_80128294(pParams, (s32)lbl_802AFE9C, &sp8, 1);
    var_r3 = fn_80219B18(temp_r30, sp8);
    fn_801276E8(pScript->unk0x18, (s32)lbl_802AFEC8, var_r3);
    return true;
}
