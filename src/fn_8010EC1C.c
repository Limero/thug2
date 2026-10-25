// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010EC1C-0x8010ED3C (288B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A38;
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_800A398C(s32, s32);
void fn_80032088(s32);
s32 fn_8012ED98(void);
void fn_80131DC0(Unk_FFAD6788 *, s32, s32, s32, s32, CStruct *);

bool ScriptSetEventHandlerOnObject(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 temp_r31;
    Unk_C8FEE62D *temp_r3;

    sp8 = 0;
    fn_80128E34(pParams, QB_EX, &sp8, 1);
    spC = 0;
    fn_80128E34(pParams, QB_SCR, &spC, 1);
    sp10 = QB_DEFAULT;
    GetChecksum_2(pParams, QB_GROUP, &sp10, 0);
    temp_r31 = ContainsFlag(pParams, 0x80367192);
    sp14 = 0;
    GetStructure_2(pParams, QB_PARAMS, &sp14, 0);
    sp18 = 0;
    fn_80128E34(pParams, QB_OBJECT, &sp18, 1);
    temp_r3 = fn_800A398C(lbl_80301A38, sp18);
    if (temp_r3->unk0x14 == 0) {
        fn_80032088(0xF8);
        temp_r3->unk0x14 = fn_8012ED98();
    }
    fn_80131DC0(temp_r3->unk0x14, sp8, spC, sp10, temp_r31, sp14);
    return true;
}
