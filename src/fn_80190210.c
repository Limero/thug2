// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80190210-0x8019026C (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80190210(Unk_C8FEE62D *arg0) {
    s32 sp8;

    sp8 = 0;
    if (GetInteger(arg0->unk0x20, QB_NUMBER_COLLECTED, &sp8, 0) != 0) {
        return sp8;
    }
    return arg0->unk0x60;
}
