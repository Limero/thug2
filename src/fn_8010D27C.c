// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010D27C-0x8010D340 (196B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80301A38;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_800A200C(Unk_C7387A53 *, s32);

bool ScriptRunScriptOnComponentType(CStruct *arg0, s32 arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    Unk_E71E4713 *temp_r9;
    Unk_C8FEE62D *var_r30;

    GetChecksum_2(arg0, QB_COMPONENT, &sp8, 1);
    GetChecksum_2(arg0, QB_TARGET, &spC, 1);
    sp10 = 0;
    GetStructure_2(arg0, QB_PARAMS, &sp10, 0);
    var_r30 = (void *)fn_800A200C(*(s32 *)&lbl_80301A38, sp8);
    if (var_r30 != NULL) {
        do {
            temp_r9 = *((void * *)&var_r30->unk0x18);
            ((s32 (*)(void *, void *, void *, void *)) * (void **)((char *)temp_r9 + (s32)0x64))(
                (char *)var_r30 + temp_r9->unk0x60,
                (void *)spC,
                (void *)sp10,
                (void *)arg1);
            var_r30 = *((void * *)&var_r30->unk0x14);
        } while (var_r30 != NULL);
    }
    return true;
}
