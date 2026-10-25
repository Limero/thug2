// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015AC70-0x8015AD28 (184B). Byte-identical.
#include "types.h"
extern void *lbl_80305EAC;
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_801A2FE4(Unk_C7387A53 *, CStruct *, s32, s32);
bool ScriptPlayCutscene(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    ContainsFlag(pParams, QB_STOP);
    if (ContainsFlag(pParams, QB_OBJECTANIM) != 0) {
        sp8 = 0;
        GetChecksum_2(pParams, QB_NAME, &sp8, 1);
        fn_801A2FE4(((Unk_40426380 *)lbl_80305EAC)->unk0x37C, sp8, pParams, QB_EXTENDEDOBJECTANIM);
    } else {
        fn_801A2FE4(((Unk_40426380 *)lbl_80305EAC)->unk0x378, QB_CUTSCENE, pParams, QB_CUTSCENE);
    }
    return true;
}
