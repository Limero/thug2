// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801527D8-0x8015293C (356B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 GetStructure_2(CStruct *, void *, s32 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 ContainsFlag(CStruct *, void *);
s32 fn_8012EF68(Unk_FFAD6788 *, Unk_15EF4A35 *);
s32 Script_SpawnScript(Unk_15EF4A35 *, void *, void *, Unk_80577C09 *, void *, void *, void *, void *, void *, void *);
bool ScriptSpawnScript(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;
    s32 var_r9;

    sp10 = 0;
    GetChecksum_2(arg0, 0, &sp10, NULL);
    sp14 = 0;
    GetStructure_2(arg0, QB_PARAMS, &sp14, 0);
    sp18 = 0;
    GetChecksum_2(arg0, QB_ID, &sp18, 0);
    sp1C = 0;
    GetChecksum_2(arg0, QB_CALLBACK, &sp1C, 0);
    sp20 = 0;
    GetStructure_2(arg0, QB_CALLBACKPARAMS, &sp20, 0);
    temp_r28 = ContainsFlag(arg0, QB_NETENABLED);
    temp_r29 = ContainsFlag(arg0, QB_PERMANENT);
    sp24 = 0;
    GetInteger(arg0, QB_NOTSESSIONSPECIFIC, &sp24, 0);
    temp_r30 = Script_SpawnScript(sp10, sp14, sp1C, sp20, arg1->unk0xB8, sp18, temp_r28, temp_r29, (sp24 == 0) ? 0 : 1, 0);
    if (ContainsFlag(arg0, QB_NOQBID) == 0) {
        fn_8012EF68(temp_r30, arg1);
    }
    return true;
}
