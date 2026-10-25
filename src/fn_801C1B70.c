// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C1B70-0x801C1BC4 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_801C218C(Unk_C7387A53 *, f32);
void fn_801C1B70(Unk_C7387A53 *arg0, CStruct *arg1) {
    f32 sp8;

    if (GetFloat(arg1, QB_VOLUME_MULT, &sp8, 0) != 0) {
        fn_801C218C((void *)arg0, sp8);
    }
}
