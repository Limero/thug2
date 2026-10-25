// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185A88-0x80185B4C (196B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void fn_8018568C(Unk_526DA6F2 *);
s32 fn_80127358(CStruct *, Unk_C7387A53 *);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);

s32 fn_80185A88(Unk_31DE137E *arg0, s32 arg1) {
    s32 spC;
    s32 sp8;
    s32 var_r27;
    s32 temp_r30;
    Unk_9994C3F5 *var_r31;

    var_r27 = 0;
    fn_8018568C((s32)arg0);
    var_r31 = fn_80127358(arg0->unk0x1C, 0);
    if (var_r31 != 0) {
        do {
            temp_r30 = fn_80127358(arg0->unk0x1C, var_r31);
            if (GetInteger(var_r31->unk0x8, QB_LEVELNUM, &sp8, (sp8 = 0, 0)) != 0) {
                GetInteger(var_r31->unk0x8, QB_HASBEATEN, &spC, (spC = 0, 0));
                if ((sp8 == arg1) && (spC != 0)) {
                    var_r27 += 1;
                }
            }
            var_r31 = temp_r30;
        } while (var_r31 != 0);
    }
    return var_r27;
}
