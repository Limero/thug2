// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188CC8-0x80188D30 (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 GetStructure(s32, s32);
extern s32 GetString(CStruct *, s32 *, s32 *, s32);
extern s32 AddString(CStruct *, s32, void *);
bool ScriptGoalManager_GetLevelPrefix(void *arg0, CScript *arg1) {
    s32 sp8;

    GetString(GetStructure(((Unk_B668C38D *)lbl_80305EAC)->unk0x390, 1), QB_LEVEL, &sp8, 1);
    AddString(arg1->unk0x18, QB_LEVEL_PREFIX, sp8);
    return true;
}
