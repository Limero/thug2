// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019026C-0x801902BC (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_8019026C(Unk_C7387A53 *arg0) {
    s32 sp8;

    sp8 = arg0->unk0x5C;
    GetInteger(arg0->unk0x20, QB_NUM_FLAGS_TO_WIN, &sp8, 0);
    if (sp8 != 0) {
        return sp8;
    }
    return -1;
}
