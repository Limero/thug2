// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80240F28-0x80240F6C (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800546A0(s32);
void fn_80057FFC(Unk_C8FEE62D *, s32);
void fn_80240F28(CStruct *arg0, s32 arg1, s32 arg2) {
    arg0->unk0x28 = arg1;
    if (arg2 == 1) {
        fn_80057FFC(fn_800546A0(arg0->unk0x0), arg1);
    }
}
