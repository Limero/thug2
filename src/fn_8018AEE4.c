// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018AEE4-0x8018AF38 (84B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 Game_GetGoalManager(void);
extern s32 fn_80183A94(Unk_C7387A53 *);
extern s32 fn_8018D118(Unk_C7387A53 *);
void fn_801276E8(CStruct *, void *, s32);

extern char lbl_802A959C[];

bool ScriptGoalManager_GetTimeLeftInNetGame(void *arg0, CScript *arg1) {
    s32 temp_r3;
    s32 temp_r5;

    temp_r3 = fn_80183A94(Game_GetGoalManager());
    if (temp_r3 != 0) {
        temp_r5 = fn_8018D118(temp_r3);
        fn_801276E8(arg1->unk0x18, (s32)lbl_802A959C, temp_r5);
    }
    return true;
}
