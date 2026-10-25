// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80195124-0x8019519C (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 ContainsFlag(CStruct *, void *);
s32 fn_80195124(Unk_C7387A53 *);
s32 fn_80195124(Unk_C7387A53 *arg0) {
    s32 sp8;
    s32 var_r30;

    sp8 = 0;
    GetInteger(arg0->unk0x20, QB_COMBO, &sp8, 0);
    var_r30 = 0;
    if ((sp8 != 0) || (ContainsFlag(arg0->unk0x20, QB_COMBO) != 0)) {
        var_r30 = 1;
    }
    return var_r30;
}
