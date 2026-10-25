// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D0118-0x801D016C (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8012772C(CStruct *, s32, f32);
s32 fn_801403CC(void *);
s32 fn_801D0118(Unk_C7387A53 *arg0, void *arg1, CScript *arg2) {
    s32 var_r3;
    CStruct *temp_r3;

    temp_r3 = fn_801403CC(arg0->unk0xC);
    var_r3 = 0;
    if (temp_r3 != NULL) {
        fn_8012772C(arg2->unk0x18, QB_FOCUS_TIME, *((f32 *)&temp_r3->unk0x4));
        var_r3 = 1;
    }
    return var_r3;
}
