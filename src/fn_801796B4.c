// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801796B4-0x8017977C (200B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(void);
extern void AddChecksum(CStruct *, s32, s32);
extern void Script_RunScript(s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
extern void ScriptClearOmnigons(s32, s32);
bool fn_801796B4(s32 **arg0) {
    s32 *temp_r28;
    s32 *var_r30;
    s32 temp_r31;
    s32 var_r29;

    var_r29 = 0;
    ScriptClearOmnigons(0, 0);
    temp_r28 = *arg0;
    if (var_r29 < (s32) *temp_r28) {
        var_r30 = temp_r28 + 1;
        do {
            CStruct_new(8);
            temp_r31 = CStruct_ctor();
            AddChecksum(temp_r31, QB_ON, 0);
            AddChecksum(temp_r31, QB_CHEAT_FLAG, *var_r30);
            var_r30 += 1;
            Script_RunScript(QB_CLIENT_TOGGLE_CHEAT, temp_r31, 0, 0, 0);
            if (temp_r31 != 0) {
                CStruct_delete(temp_r31, 3);
            }
        } while (++var_r29 < *(s32 *)temp_r28);
    }
    return true;
}
