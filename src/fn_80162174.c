// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80162174-0x80162244 (208B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8005C0D8(s32, s32, s32);
s32 fn_8005CF80(Unk_9994C3F5 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern Unk_9994C3F5 * lbl_80366474;
bool ScriptGenerate32BitImage(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 *pC;
    s32 temp_r3;
    s32 var_r29;
    s32 var_r28;

    GetChecksum_2(pParams, 0, &sp8, 0);
    if ((temp_r3 = fn_8005CF80(lbl_80366474, sp8)) != 0) {
        pC = &spC;
        var_r29 = 0;
        var_r28 = 0;
        if (GetInteger(pParams, QB_RENDERABLE, pC, 0) != 0) {
            var_r29 = (spC ^ 1) == 0;
        }
        if (GetInteger(pParams, QB_STORE_ORIGINAL, pC, 0) != 0) {
            if (spC == 1) {
                var_r28 = 1;
            }
        }
        fn_8005C0D8(temp_r3, var_r29, var_r28);
    }
    return true;
}
