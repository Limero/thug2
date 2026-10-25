// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D01C0-0x801D0214 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_801403CC(void *);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801D01C0(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 temp_r3;
    s32 var_r3;

    temp_r3 = fn_801403CC(arg0->unk0xC);
    var_r3 = 0;
    if (temp_r3 != 0) {
        GetInteger(arg1, 0, temp_r3 + 8, 0);
        var_r3 = 1;
    }
    return var_r3;
}
