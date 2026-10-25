// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80188BBC-0x80188CC8 (268B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 lbl_80305EC0;
extern char lbl_802A9580[];
extern char lbl_802A958C[];
extern s32 GetText(CStruct *, void *, void *, s32);
extern s32 GetStructure(s32, s32);
extern s32 GetString(CStruct *, s32 *, s32 *, s32);
extern void strcpy(void *, void *);
extern void strcat(char *, char *);
extern s32 IsTrue(s32, void *);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 Script_GenerateCRC(char *);
void AddChecksum(CStruct *, s32, s32);
extern s32 AddString(CStruct *, s32, void *);
bool ScriptGoalManager_CreateGoalName(CStruct *pParams, CScript *pScript) {
    char sp8[0x80];
    s32 sp88;
    s32 sp8C;
    s32 temp_r30;

    GetText(pParams, QB_GOAL_TYPE, &sp88, 1);
    GetString(GetStructure(((Unk_B668C38D *)lbl_80305EAC)->unk0x390, 1), QB_LEVEL, &sp8C, 1);
    strcpy(sp8, (void *)sp8C);
    if ((IsTrue(lbl_80305EC0, QB_IS_CLASSIC) != 0) || (ContainsFlag(pParams, QB_CLASSIC_MODE_GOAL) != 0)) {
        strcat(sp8, lbl_802A9580);
    }
    strcat(sp8, lbl_802A958C);
    strcat(sp8, (char *)sp88);
    temp_r30 = pScript->unk0x18;
    AddChecksum(temp_r30, QB_GOAL_ID, Script_GenerateCRC(sp8));
    AddString(pScript->unk0x18, QB_GOAL_NAME, sp8);
    return true;
}
