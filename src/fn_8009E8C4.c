// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E8C4-0x8009E940 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009E4B0(Unk_C7387A53 *, CStruct *);
s32 GetArray(CStruct *, s32, s32 *, s32);
bool fn_8009E8C4(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;

    sp8 = 0;
    if (GetArray(arg1, QB_TAGS, &sp8, 0) == 0) {
        GetArray(arg1, 0, &sp8, 0);
    }
    fn_8009E4B0(arg0, sp8);
    return true;
}
