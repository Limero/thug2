// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FAD6C-0x801FAEA0 (308B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801FB15C(Unk_C7387A53 * arg0);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 fn_80129528(CStruct *, s32);
void fn_801FB248(Unk_C7387A53 * arg0);
s32 fn_801F9820(Unk_C7387A53 * arg0);
void GetVector(CStruct *, s32, CStruct *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_801FAD6C(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 temp_r30;
    s32 temp_r31;
    u32 var_r29;
    u32 var_r31;

    fn_801FB15C(arg0);
    sp8 = 0;
    GetArray(arg1, QB_CREATEDRAILS, &sp8, 0);
    if (sp8 != 0) {
        var_r31 = 0;
        if (var_r31 < *((u32 *)&((CStruct *)sp8)->unk0x4)) {
            do {
                temp_r30 = fn_80129528(sp8, var_r31);
                fn_801FB248(arg0);
                spC = 0;
                GetArray(temp_r30, QB_POINTS, &spC, 1);
                var_r29 = 0;
                if (var_r29 < *((u32 *)&((CStruct *)spC)->unk0x4)) {
                    do {
                        temp_r31 = fn_801F9820(arg0->unk0x28);
                        temp_r30 = fn_80129528(spC, var_r29);
                        GetVector(temp_r30, QB_POS, (void *)(temp_r31 + 8), 0);
                        if (ContainsFlag(temp_r30, QB_HASPOST) != 0) {
                            ((CScript *)temp_r31)->unk0x18 = 1;
                        }
                        var_r29++;
                    } while (var_r29 < *((u32 *)&((CStruct *)spC)->unk0x4));
                }
                var_r31++;
            } while (var_r31 < *((u32 *)&((CStruct *)sp8)->unk0x4));
        }
    }
}
