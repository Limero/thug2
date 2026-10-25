// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A750-0x8018A7AC (92B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 Game_GetGoalManager(void);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_801875CC(Unk_526DA6F2 *, s32);

register s32 g31 __asm__("r31");

// ScriptGoalManager_ResetCareer @ 0x8018A750
bool ScriptGoalManager_ResetCareer(s32 arg0) {
    register s32 a0 __asm__("r29");
    register s32 a1 __asm__("r30");
    s32 sp8;

    a1 = arg0;
    a0 = Game_GetGoalManager();
    sp8 = 0;
    GetChecksum_2(a1, 0, &sp8, 0);
    fn_801875CC(a0, sp8);
    return true;
}
