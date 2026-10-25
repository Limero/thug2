// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016C6FC-0x8016C77C (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
void CStruct_delete(CStruct *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void AddComponent(CStruct *, s32, s32, void *);
s32 CStruct_ctor(s32);
bool fn_8016C6FC(s32 *arg0) {
    s32 temp_r30;
    s32 temp_r31;

    temp_r30 = *arg0;
    temp_r31 = CStruct_ctor(CStruct_new(8));
    AddComponent(temp_r31, QB_SCENE, 3, temp_r30);
    Script_RunScript(QB_RELOADSCENE, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return true;
}
