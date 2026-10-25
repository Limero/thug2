// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018A0A4-0x8018A194 (240B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 Game_GetGoalManager(void);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 GetString(CStruct *, s32 *, s32 *, s32);
extern s32 fn_801869EC(s32, s32);
extern void fn_80186B90(Unk_9994C3F5 *);
extern s32 fn_80186A14(s32, s32, void *, void *, s32);
extern void fn_801270B4(CStruct *, s32);
extern void AddString(CStruct *, s32, void *);

s32 ScriptGoalManager_ReplaceTrickText(CStruct *pParams, CScript *pScript) {
    char sp8[0x200];
    s32 sp208;
    s32 sp20C;
    s32 temp_r30;

    temp_r30 = Game_GetGoalManager();
    if (ContainsFlag(pParams, QB_ALL) != 0) {
        fn_80186B90(temp_r30);
        goto block_7;
    }
    if (GetChecksum_2(pParams, QB_NAME, &sp208, 0) != 0) {
        if (GetString(pParams, QB_TEXT, &sp20C, 0) == 0) {
            return fn_801869EC(temp_r30, sp208);
        }
        if (fn_80186A14(temp_r30, sp208, sp20C, sp8, 0x200) != 0) {
            fn_801270B4(pScript->unk0x18, QB_TRICKTEXT);
            AddString(pScript->unk0x18, QB_TRICKTEXT, sp8);
        }
        goto block_7;
    }
block_7:
    return 1;
}
