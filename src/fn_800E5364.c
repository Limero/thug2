// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E5364-0x800E53B0 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void GetFloat(CStruct *, s32, f32 *, s32);
extern void fn_800E5264(Unk_C7387A53 *, f32);
bool fn_800E5364(Unk_C7387A53 *arg0, CStruct *arg1) {
    f32 sp8;

    GetFloat(arg1, 0, &sp8, 1);
    fn_800E5264(arg0, sp8);
    return true;
}
