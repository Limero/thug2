// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D6444-0x800D6490 (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800D8484(Unk_C7387A53 *, CStruct *, void *);
s32 fn_800D6444(Unk_C7387A53 *arg0, s32 arg1, CStruct *arg2, s32 arg3) {
    s32 var_r3;

    var_r3 = 2;
    if (arg1 == QB_OBJ_MOVETONODE) {
        fn_800D8484(arg0, arg2, arg3);
        var_r3 = 1;
    }
    return var_r3;
}
