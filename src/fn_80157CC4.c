// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80157CC4-0x80157E8C (456B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A80FC[];
extern char lbl_802A8108[];
extern char lbl_802A8114[];
extern char lbl_802A8128[];
extern char lbl_802A8130[];
extern s32 fn_80176EE0(CStruct * arg0, s32 arg1);
extern s32 GetText(CStruct * arg0, void * arg1, void * arg2, s32 arg3);
extern s32 CStruct_new(s32 arg0);
extern s32 CStruct_ctor(s32 arg0);
extern void AddComponent(CStruct * arg0, s32 arg1, s32 arg2, void * arg3);
extern s32 GetChecksum_4(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
extern void fn_80127E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 strcasecmp(void *arg0, void *arg1);
extern s32 fn_80128294(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 Script_GenerateCRC(void *arg0);
extern s32 fn_801400C0(s32 arg0, s32 arg1, CStruct * arg2);
extern s32 CStruct_delete(CStruct * arg0, s32 arg1);
bool ScriptSetPreferencesFromUI(CStruct *pParams, CScript *pScript) {
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r28;
    s32 temp_r30;

    temp_r28 = fn_80176EE0(pParams, 1);
    GetText(pParams, QB_STRING, &sp8, 1);
    GetText(pParams, QB_FIELD, &spC, 1);
    temp_r30 = CStruct_ctor(CStruct_new(8));
    AddComponent(temp_r30, QB_UI_STRING, 3, sp8);
    sp10 = 0;
    GetChecksum_4(pParams, (s32)lbl_802A80FC, &sp10, 0);
    fn_80127E70(temp_r30, QB_CHECKSUM, 0xD, sp10);
    if ((strcasecmp((void *)spC, (void *)lbl_802A8108) == 0) || (strcasecmp((void *)spC, (void *)lbl_802A8114) == 0)) {
        fn_80128294((void *)pParams, (s32)lbl_802A8128, &sp14, 0);
        fn_80127E70(temp_r30, QB_TIME, 1, sp14);
    }
    if (strcasecmp((void *)spC, (void *)lbl_802A8130) == 0) {
        if (GetInteger(pParams, QB_SCORE, &sp18, 0) == 0) {
            GetInteger(pParams, QB_TIME, &sp18, 1);
            sp18 *= 1000;
        }
        fn_80127E70(temp_r30, QB_SCORE, 1, sp18);
    }
    fn_801400C0(temp_r28, Script_GenerateCRC(spC), temp_r30);
    if (temp_r30 != 0) {
        CStruct_delete(temp_r30, 3);
    }
    return true;
}
