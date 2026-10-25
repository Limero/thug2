// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AB38-0x8018AB7C (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Game_GetGoalManager(void);
void AddChecksum(CStruct *, s32, s32);
bool ScriptGoalManager_GetSponsor(s32 arg0, CScript *arg1) {
    s32 sp8;

    sp8 = *(s32 *)((char *)Game_GetGoalManager() + (s32)0x58);
    AddChecksum(arg1->unk0x18, QB_SPONSOR, sp8);
    return true;
}
