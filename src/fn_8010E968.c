// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010E968-0x8010EA28 (192B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_8030044C;
extern s32 lbl_80301A38;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_800689D4(CStruct *, s32);
s32 fn_800A200C(Unk_C7387A53 *, s32);

bool ScriptDestroyParticlesByGroupID(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    CStruct *temp_r10;
    Unk_C6B642AC *temp_r9;
    Unk_C8FEE62D *var_r31;

    sp8 = 0;
    GetChecksum_2(pParams, QB_GROUPID, &sp8, 1);
    if (lbl_8030044C != 0) {
        fn_800689D4((void *)lbl_8030044C, sp8);
    }
    var_r31 = fn_800A200C((void *)lbl_80301A38, QB_PARTICLE);
    if (var_r31 != NULL) {
        do {
            temp_r10 = *((void * *)&var_r31->unk0xC);
            if (!(temp_r10->unk0xC & 1) && (*(s32 *)((char *)(*((void * *)&var_r31->unk0x20)) + 0x14) == sp8)) {
                temp_r9 = *((void * *)&temp_r10->unk0x8);
                ((s32 (*)(void *)) temp_r9->unk0x3C)((char *)temp_r10 + (s32)temp_r9->unk0x38);
            }
            var_r31 = var_r31->unk0x14;
        } while (var_r31 != NULL);
    }
    return true;
}
