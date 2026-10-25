// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80173CFC-0x80173D30 (52B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_800DB484(void);
s32 fn_80173CFC(Unk_6A70655D *arg0) {
    s32 var_r3;

    var_r3 = GetChecksum_3(arg0, QB_SUSPEND);
    if (var_r3 != 0) {
        var_r3 = fn_800DB484();
    }
    return var_r3;
}
