// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80159F94-0x8015A0D8 (324B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_801A326C(s32);
s32 fn_8009F498(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
void fn_801A2A58(s32);
void Script_RunScript(s32, s32, s32, s32, s32);
s32 fn_801A2FE4(Unk_C7387A53 *, CStruct *, s32, s32);
extern void* lbl_80305EAC;
bool ScriptPlaySkaterCamAnim(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r3;
    s32 temp_r3_2;
    Unk_FFAD6788 *var_r3;

    temp_r3 = ContainsFlag(pParams, QB_USE_LAST_CAMERA);
    if (temp_r3 != 0) {
        fn_801A326C(((Unk_40426380 *)lbl_80305EAC)->unk0x378);
    } else {
        spC = temp_r3;
        if (GetChecksum_2(pParams, QB_SKATERID, &sp8, 0) != 0) {
            var_r3 = fn_8009F498(sp8);
        } else {
            GetInteger(pParams, QB_SKATER, &spC, 0);
            var_r3 = fn_801746A4(lbl_80305EAC, spC);
        }
        if ((var_r3 != NULL) && (var_r3->unk0xC8 != 0)) {
            temp_r3_2 = ContainsFlag(pParams, QB_STOP);
            if (temp_r3_2 != 0) {
                fn_801A2A58(((Unk_40426380 *)lbl_80305EAC)->unk0x378);
            } else {
                sp10 = temp_r3_2;
                GetChecksum_2(pParams, QB_NAME, &sp10, 0);
                Script_RunScript(QB_DISABLE_SKATER_SCALING, 0, 0, 0, 0);
                fn_801A2FE4(((Unk_40426380 *)lbl_80305EAC)->unk0x378, sp10, pParams, QB_SKATERCAMANIM);
            }
        }
    }
    return true;
}
