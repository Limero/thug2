// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80153CC4-0x80153D28 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
void fn_8021F8E8(Unk_C7387A53 *);
s32 fn_8021F904(s32);
void Script_RunScript(s32, s32, s32, s32, s32);

bool ScriptTogglePlayerNames(CStruct *pParams, CScript *pScript) {
    s32 temp_r30;

    temp_r30 = lbl_80305F9C;
    fn_8021F8E8((void *)temp_r30);
    if (fn_8021F904(temp_r30) == 0) {
        Script_RunScript(QB_DESTROY_ALL_PLAYER_NAMES, 0, 0, 0, 0);
    }
    return true;
}
