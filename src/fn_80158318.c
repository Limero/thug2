// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80158318-0x80158404 (236B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EFC[];

s32 GetChecksum_2(CStruct * arg0, s32 hash, s32 * out, s32 defval);
s32 GetStructure_2(CStruct * arg0, s32 hash, s32 * out, s32 defval);
s32 fn_801A5C04(Unk_9994C3F5 * a);
s32 fn_801A5C40(s32 a, s32 b);
s32 CStruct_new(s32 size);
s32 CStruct_ctor(s32 a);
void fn_80126FF4(Unk_80577C09 * a, CStruct * b);
s32 Script_RunScript(s32 a, s32 b, s32 c, s32 d, s32 e);
void CStruct_delete(CStruct * a, s32 b);

bool ScriptForEachSkaterProfile(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 lblval;
    s32 cnt;
    s32 entry;
    s32 temp_r31;
    s32 i;

    GetChecksum_2(pParams, QB_DO, &sp8, 1);
    spC = 0;
    i = 0;
    GetStructure_2(pParams, QB_PARAMS, &spC, 0);
    lblval = *(s32 *)&lbl_80305EFC;
    cnt = fn_801A5C04(lblval);
    while (i < cnt) {
        entry = fn_801A5C40(lblval, i) + 0x6C;
        temp_r31 = CStruct_ctor(CStruct_new(8));
        fn_80126FF4(temp_r31, spC);
        fn_80126FF4(temp_r31, entry);
        Script_RunScript(sp8, temp_r31, 0, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
        i++;
    }
    return true;
}
