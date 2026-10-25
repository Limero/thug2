// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80154A24-0x80154A8C (104B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801403CC(void *);
s32 fn_801746A4(Unk_C7387A53 *, void *);
s32 fn_80182AA8(void *);
extern char lbl_80305EAC[];
bool ScriptSetScreenMode(CStruct *pParams, CScript *pScript) {
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r3_2;
    u32 var_r31;

    fn_8005E300();
    var_r31 = 0U;
    temp_r30 = *(s32 *)&lbl_80305EAC;
    do {
        temp_r3 = fn_801746A4(temp_r30, var_r31);
        if (temp_r3 != 0) {
            temp_r3_2 = fn_801403CC(temp_r3);
            if (temp_r3_2 != 0) {
                fn_80182AA8(temp_r3_2);
            }
        }
        var_r31 += 1;
    } while (var_r31 <= 7U);
    return true;
}
