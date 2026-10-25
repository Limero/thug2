// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80175994-0x80175A60 (204B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;
extern char lbl_802A8DE8[];
extern s32 fn_80128E34(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
extern s32 GetString(CStruct * arg0, s32 * arg1, s32 * arg2, s32 arg3);
extern s32 Script_GenerateCRC(void *arg0);
extern s32 fn_8021F748(s32 arg0);
extern void fn_8021F5C8(Unk_C7387A53 * arg0, s32 arg1);

bool ScriptRequestLevel(CStruct *pParams, CScript *pScript) {
    char sp8[128];
    s32 sp88;
    s32 sp8C;
    s32 temp_r30;
    s32 temp_r3;
    Unk_7258DEBD *temp_r29;

    temp_r30 = lbl_80305F9C;
    temp_r29 = (s32 *)lbl_80305EAC;
    if ((fn_80128E34(pParams, 0, &sp88, 0) == 0) && (GetString(pParams, 0, &sp8C, 1) != 0)) {
        sprintf(sp8, lbl_802A8DE8, sp8C);
        sp88 = Script_GenerateCRC(sp8);
    }
    if (sp88 == QB_USE_PREFERENCES) {
        temp_r3 = fn_8021F748(temp_r30);
        sp88 = temp_r3;
        fn_8021F5C8(temp_r30, temp_r3);
    }
    temp_r29->unk0x384 = sp88;
    return true;
}
