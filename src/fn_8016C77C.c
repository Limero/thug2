// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016C77C-0x8016C814 (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void AddComponent(CStruct *, s32, s32, void *);
extern void Script_RunScript(s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
bool fn_8016C77C(s32 *arg0) {
    s32 temp_r30;
    s32 temp_r31;

    temp_r30 = *arg0;
    temp_r31 = CStruct_ctor(CStruct_new(8));
    AddComponent(temp_r31, QB_SCENE, 3, temp_r30);
    AddComponent(temp_r31, QB_ADD, 3, temp_r30 + 0x80);
    Script_RunScript(QB_ADDTOSCENE, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return true;
}
