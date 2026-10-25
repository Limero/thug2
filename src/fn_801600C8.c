// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801600C8-0x801601F0 (296B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_801259C8(s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80129528(CStruct *, s32);
s32 fn_80128978(s32, s32);
s32 AddInteger(CStruct *, s32, s32);

bool ScriptGetIndexOfItemContaining(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    register s32 t __asm__("r4");
    CStruct *temp_r29;
    s32 temp_r30;
    s32 temp_r31;

    GetChecksum_2(pParams, QB_ARRAY, &sp8, 1);
    temp_r29 = (s32 *)fn_801259C8(sp8, 1);
    GetChecksum_2(pParams, QB_NAME, &spC, 1);
    sp10 = 0;
    GetInteger(pParams, QB_INDEX, &sp10, 0);
    GetChecksum_2(pParams, QB_VALUE, &sp14, 1);
    temp_r31 = temp_r29->unk0x4;
    t = sp10;
    if (t < temp_r31) {
        do {
            temp_r30 = fn_80129528(temp_r29, t);
            if (fn_80128978(temp_r30, spC) != 0) {
                GetChecksum_2(temp_r30, spC, &sp18, 1);
                if (sp18 == sp14) {
                    AddInteger(pScript->unk0x18, QB_INDEX, sp10);
                    return true;
                }
            }
            t = (sp10 = sp10 + 1);
        } while (t < temp_r31);
    }
    return false;
}
