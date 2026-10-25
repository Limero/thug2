// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D016C-0x801D01C0 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void AddInteger(CStruct *, s32, s32);
s32 fn_801403CC(void *);
s32 fn_801D016C(Unk_C7387A53 *arg0, void *arg1, CScript *arg2) {
    s32 var_r3;
    Unk_9994C3F5 *temp_r3;

    temp_r3 = fn_801403CC(arg0->unk0xC);
    var_r3 = 0;
    if (temp_r3 != NULL) {
        AddInteger(arg2->unk0x18, QB_FOCUS_ALLOWED, temp_r3->unk0x8);
        var_r3 = 1;
    }
    return var_r3;
}
