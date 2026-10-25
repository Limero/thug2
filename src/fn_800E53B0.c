// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E53B0-0x800E53FC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800E526C(Unk_C7387A53 *, CStruct *);
void GetArray(CStruct *, s32, s32 *, s32);
bool fn_800E53B0(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;

    GetArray(arg1, 0, &sp8, 1);
    fn_800E526C(arg0, sp8);
    return true;
}
